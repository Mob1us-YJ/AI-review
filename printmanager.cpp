#include "printmanager.h"
#include <QDebug>
#include <QFileInfo>
#include <QRegularExpression>
#include <QProcess>
#include <QTimer>
#include <QRandomGenerator>

PrintManager::PrintManager(QObject *parent)
    : QObject(parent),
      m_printProcess(nullptr),
      m_copies(1),
      m_media("A4"),
      m_sides("two-sided-long-edge"),
      m_simulationMode(false)
{
    // 获取默认打印机
    m_currentPrinter = getDefaultPrinter();
    
    // 连接信号
    connect(m_printProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, &PrintManager::onPrintProcessFinished);
    connect(m_printProcess, &QProcess::errorOccurred,
            this, &PrintManager::onPrintProcessError);
}

PrintManager::~PrintManager()
{
}

QStringList PrintManager::getAvailablePrinters()
{
    QStringList printers;
    
    // 使用lpstat -p 列出可用打印机
    QProcess process;
    process.start("lpstat", QStringList() << "-p");
    process.waitForFinished();
    
    QString output = process.readAllStandardOutput();
    QStringList lines = output.split('\n', QString::SkipEmptyParts);
    
    for (const QString &line : lines) {
        if (line.startsWith("printer")) {
            // 解析打印机名称，格式通常是 "printer printer_name is ..."
            QStringList parts = line.split(' ');
            if (parts.size() >= 2) {
                QString printerName = parts[1];
                printers.append(printerName);
            }
        }
    }
    
    return printers;
}

QString PrintManager::getDefaultPrinter()
{
    // 使用lpstat -d 获取默认打印机
    QProcess process;
    process.start("lpstat", QStringList() << "-d");
    process.waitForFinished();
    
    QString output = process.readAllStandardOutput();
    QRegularExpression regex("system default destination: (.+)");
    QRegularExpressionMatch match = regex.match(output);
    
    if (match.hasMatch()) {
        return match.captured(1);
    }
    
    return "";
}

bool PrintManager::selectPrinter(const QString &printerName)
{
    QStringList printers = getAvailablePrinters();
    if (printers.contains(printerName)) {
        m_currentPrinter = printerName;
        return true;
    }
    return false;
}

void PrintManager::setPrintSettings(int copies, const QString &media, const QString &sides)
{
    m_copies = copies;
    m_media = media;
    m_sides = sides;
}

QStringList PrintManager::buildPrintOptions()
{
    QStringList options;
    
    // 打印机选择
    if (!m_currentPrinter.isEmpty()) {
        options << "-d" << m_currentPrinter;
    }
    
    // 打印份数
    if (m_copies > 1) {
        options << "-n" << QString::number(m_copies);
    }
    
    // 纸张大小
    options << "-o" << "media=" + m_media;
    
    // 双面打印
    options << "-o" << "sides=" + m_sides;
    
    return options;
}

bool PrintManager::printFile(const QString &filePath, const QString &jobName)
{
    if (!QFile::exists(filePath)) {
        emit printError("File does not exist: " + filePath);
        return false;
    }
    
    QStringList args = buildPrintOptions();
    
    // 添加文件名
    args << filePath;
    
    qDebug() << "Starting print with command: lp" << args;
    
    m_printProcess->start("lp", args);
    
    if (m_printProcess->waitForStarted()) {
        QString actualJobName = jobName.isEmpty() ? QFileInfo(filePath).fileName() : jobName;
        emit printStarted(actualJobName);
        return true;
    } else {
        emit printError("Failed to start print process");
        return false;
    }
}

bool PrintManager::printFileWithOptions(const QString &filePath, const QStringList &options)
{
    if (!QFile::exists(filePath)) {
        emit printError("File does not exist: " + filePath);
        return false;
    }
    
    QStringList args = buildPrintOptions();
    args.append(options);
    args << filePath;
    
    qDebug() << "Starting print with custom options: lp" << args;
    
    m_printProcess->start("lp", args);
    
    if (m_printProcess->waitForStarted()) {
        emit printStarted(QFileInfo(filePath).fileName());
        return true;
    } else {
        emit printError("Failed to start print process");
        return false;
    }
}

void PrintManager::getPrintJobs()
{
    QProcess process;
    process.start("lpstat", QStringList() << "-o");
    process.waitForFinished();
    
    QString output = process.readAllStandardOutput();
    QStringList lines = output.split('\n', QString::SkipEmptyParts);
    
    QMap<int, QString> jobs;
    
    for (const QString &line : lines) {
        // 解析打印任务，格式通常是 "printer_name-123 username ..."
        QRegularExpression regex("(.+)-(\\d+)\\s+(.+)\\s+(.+)");
        QRegularExpressionMatch match = regex.match(line);
        
        if (match.hasMatch()) {
            int jobId = match.captured(2).toInt();
            QString jobInfo = match.captured(3) + " - " + match.captured(4);
            jobs[jobId] = jobInfo;
        }
    }
    
    emit printJobsReceived(jobs);
}

void PrintManager::cancelPrintJob(int jobId)
{
    QProcess process;
    process.start("cancel", QStringList() << QString::number(jobId));
    process.waitForFinished();
    
    if (process.exitCode() == 0) {
        qDebug() << "Print job" << jobId << "cancelled successfully";
    } else {
        QString error = process.readAllStandardError();
        qDebug() << "Failed to cancel print job" << jobId << ":" << error;
    }
}

void PrintManager::pausePrinter()
{
    if (!m_currentPrinter.isEmpty()) {
        QProcess process;
        process.start("cupsdisable", QStringList() << m_currentPrinter);
        process.waitForFinished();
    }
}

void PrintManager::resumePrinter()
{
    if (!m_currentPrinter.isEmpty()) {
        QProcess process;
        process.start("cupsenable", QStringList() << m_currentPrinter);
        process.waitForFinished();
    }
}

void PrintManager::onPrintProcessFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    if (exitCode == 0) {
        QString output = m_printProcess->readAllStandardOutput();
        int jobId = extractJobId(output);
        
        if (jobId > 0) {
            emit printCompleted("Print Job", jobId);
        } else {
            emit printCompleted("Print Job", -1);
        }
    } else {
        QString error = m_printProcess->readAllStandardError();
        emit printError("Print failed: " + error);
    }
}

void PrintManager::onPrintProcessError(QProcess::ProcessError error)
{
    QString errorMsg;
    switch (error) {
        case QProcess::FailedToStart:
            errorMsg = "Failed to start print process";
            break;
        case QProcess::Crashed:
            errorMsg = "Print process crashed";
            break;
        case QProcess::Timedout:
            errorMsg = "Print process timed out";
            break;
        default:
            errorMsg = "Unknown print process error";
            break;
    }
    
    emit printError(errorMsg);
}

int PrintManager::extractJobId(const QString &output)
{
    // 从lp命令输出中提取任务ID
    // 输出格式通常是 "request id is printer_name-123 (1 file(s))"
    QRegularExpression regex("request id is .+-(\\d+)");
    QRegularExpressionMatch match = regex.match(output);
    
    if (match.hasMatch()) {
        return match.captured(1).toInt();
    }
    
    return -1;
} 

void PrintManager::enableSimulationMode(bool enable)
{
    m_simulationMode = enable;
    qDebug() << "打印模拟模式:" << (enable ? "启用" : "禁用");
}

void PrintManager::simulatePrint(const QString &fileName, const QString &printerName)
{
    if (!m_simulationMode) {
        qDebug() << "模拟模式未启用";
        return;
    }
    
    qDebug() << "开始模拟打印，文件:" << fileName << "打印机:" << printerName;
    emit printStarted(fileName);
    
    // 模拟打印进度
    QTimer::singleShot(2000, [this, fileName]() {
        int jobId = QRandomGenerator::global()->bounded(1000, 9999);
        emit printCompleted(fileName, jobId);
        qDebug() << "模拟打印完成，任务ID:" << jobId;
    });
} 