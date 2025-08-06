#include "printmanager.h"
#include <QDebug>
#include <QFileInfo>
#include <QRegularExpression>
#include <QProcess>
#include <QTimer>
#include <QRandomGenerator>

PrintManager::PrintManager(QObject *parent)
    : QObject(parent),
      m_simulationMode(false)
{
}

PrintManager::~PrintManager()
{
}



void PrintManager::setPrintSettings(const QString &deviceName, int copies, const QString &media, const QString &sides)
{
    m_printCopies[deviceName] = copies;
    m_printMedia[deviceName] = media;
    m_printSides[deviceName] = sides;
    
    qDebug() << "设置打印参数，设备:" << deviceName 
             << "份数:" << copies 
             << "纸张:" << media 
             << "双面:" << sides;
}

QStringList PrintManager::buildPrintOptions(const QString &deviceName)
{
    QStringList options;
    
    // 打印机选择
    options << "-d" << deviceName;
    
    // 获取该设备的打印设置
    int copies = m_printCopies.value(deviceName, 1);
    QString media = m_printMedia.value(deviceName, "A4");
    QString sides = m_printSides.value(deviceName, "two-sided-long-edge");
    
    // 打印份数
    if (copies > 1) {
        options << "-n" << QString::number(copies);
    }
    
    // 纸张大小设置
    options << "-o" << "media=" + media;
    
    // 双面打印设置
    if (sides == "two-sided-long-edge") {
        options << "-o" << "sides=two-sided-long-edge";
    } else if (sides == "two-sided-short-edge") {
        options << "-o" << "sides=two-sided-short-edge";
    } else {
        options << "-o" << "sides=one-sided";
    }
    
    // 特殊纸张设置
    if (media == "A3") {
        // A3纸张的特殊设置
        options << "-o" << "fit-to-page";
        options << "-o" << "scaling=100";
    }
    
    return options;
}

bool PrintManager::printFile(const QString &deviceName, const QString &filePath, const QString &jobName)
{
    if (!QFile::exists(filePath)) {
        emit printError(deviceName, "File does not exist: " + filePath);
        return false;
    }
    
    QStringList args = buildPrintOptions(deviceName);
    
    // 添加文件名
    args << filePath;
    
    qDebug() << "Starting print with command: lp" << args;
    
    QProcess *process = getOrCreatePrintProcess(deviceName);
    process->start("lp", args);
    
    if (process->waitForStarted()) {
        QString actualJobName = jobName.isEmpty() ? QFileInfo(filePath).fileName() : jobName;
        emit printStarted(deviceName, actualJobName);
        return true;
    } else {
        emit printError(deviceName, "Failed to start print process");
        return false;
    }
}

bool PrintManager::printFileWithOptions(const QString &deviceName, const QString &filePath, const QStringList &options)
{
    if (!QFile::exists(filePath)) {
        emit printError(deviceName, "File does not exist: " + filePath);
        return false;
    }
    
    QStringList args = buildPrintOptions(deviceName);
    args.append(options);
    args << filePath;
    
    qDebug() << "Starting print with custom options: lp" << args;
    
    QProcess *process = getOrCreatePrintProcess(deviceName);
    process->start("lp", args);
    
    if (process->waitForStarted()) {
        emit printStarted(deviceName, QFileInfo(filePath).fileName());
        return true;
    } else {
        emit printError(deviceName, "Failed to start print process");
        return false;
    }
}



void PrintManager::onPrintProcessFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    QProcess *process = qobject_cast<QProcess*>(sender());
    if (!process) return;
    
    // 找到对应的设备名称
    QString deviceName;
    for (auto it = m_printProcesses.begin(); it != m_printProcesses.end(); ++it) {
        if (it.value() == process) {
            deviceName = it.key();
            break;
        }
    }
    
    if (exitCode == 0) {
        QString output = process->readAllStandardOutput();
        int jobId = extractJobId(output);
        
        if (jobId > 0) {
            emit printCompleted(deviceName, "Print Job", jobId);
        } else {
            emit printCompleted(deviceName, "Print Job", -1);
        }
    } else {
        QString error = process->readAllStandardError();
        emit printError(deviceName, "Print failed: " + error);
    }
}

void PrintManager::onPrintProcessError(QProcess::ProcessError error)
{
    QProcess *process = qobject_cast<QProcess*>(sender());
    if (!process) return;
    
    // 找到对应的设备名称
    QString deviceName;
    for (auto it = m_printProcesses.begin(); it != m_printProcesses.end(); ++it) {
        if (it.value() == process) {
            deviceName = it.key();
            break;
        }
    }
    
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
    
    emit printError(deviceName, errorMsg);
}

QProcess* PrintManager::getOrCreatePrintProcess(const QString &deviceName)
{
    if (!m_printProcesses.contains(deviceName)) {
        QProcess *process = new QProcess(this);
        connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
                this, &PrintManager::onPrintProcessFinished);
        connect(process, &QProcess::errorOccurred,
                this, &PrintManager::onPrintProcessError);
        m_printProcesses[deviceName] = process;
    }
    return m_printProcesses[deviceName];
}

void PrintManager::cleanupProcess(const QString &deviceName)
{
    if (m_printProcesses.contains(deviceName)) {
        QProcess *process = m_printProcesses[deviceName];
        if (process) {
            process->terminate();
            process->waitForFinished(5000);
            if (process->state() == QProcess::Running) {
                process->kill();
            }
            delete process;
        }
        m_printProcesses.remove(deviceName);
    }
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
    emit printStarted(printerName, fileName);
    
    // 模拟打印进度
    QTimer::singleShot(2000, [this, fileName, printerName]() {
        int jobId = QRandomGenerator::global()->bounded(1000, 9999);
        emit printCompleted(printerName, fileName, jobId);
        qDebug() << "模拟打印完成，任务ID:" << jobId;
    });
} 