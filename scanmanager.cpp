#include "scanmanager.h"
#include <QStandardPaths>
#include <QDateTime>
#include <QDebug>
#include <QFileInfo>

ScanManager::ScanManager(QObject *parent)
    : QObject(parent),
      m_scanProcess(nullptr),
      m_batchTimer(new QTimer(this)),
      m_dpi(300),
      m_format("A4"),
      m_mode("Color"),
      m_currentPage(0),
      m_simulationMode(false)
{
    // 设置输出目录
    m_outputDir = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) 
                  + "/AIReview/Scans";
    createOutputDirectory();
    
    // 连接信号
    connect(m_scanProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, &ScanManager::onScanProcessFinished);
    connect(m_scanProcess, &QProcess::errorOccurred,
            this, &ScanManager::onScanProcessError);
    
    // 批量扫描定时器
    connect(m_batchTimer, &QTimer::timeout, this, &ScanManager::onBatchScanTimer);
}

ScanManager::~ScanManager()
{
    stopScan();
}

QStringList ScanManager::getAvailableDevices()
{
    QStringList devices;
    
    // 使用scanimage -L 列出可用设备
    QProcess process;
    process.start("scanimage", QStringList() << "-L");
    process.waitForFinished();
    
    QString output = process.readAllStandardOutput();
    QStringList lines = output.split('\n', QString::SkipEmptyParts);
    
    for (const QString &line : lines) {
        if (line.contains("device")) {
            // 解析设备名称，格式通常是 "device `device_name' is a ..."
            int start = line.indexOf("`") + 1;
            int end = line.indexOf("'", start);
            if (start > 0 && end > start) {
                QString deviceName = line.mid(start, end - start);
                devices.append(deviceName);
            }
        }
    }
    
    return devices;
}

bool ScanManager::selectDevice(const QString &deviceName)
{
    QStringList devices = getAvailableDevices();
    if (devices.contains(deviceName)) {
        m_currentDevice = deviceName;
        return true;
    }
    return false;
}

void ScanManager::setScanSettings(int dpi, const QString &format, const QString &mode)
{
    m_dpi = dpi;
    m_format = format;
    m_mode = mode;
}

QString ScanManager::buildScanCommand(const QString &outputPath)
{
    QStringList args;
    
    // 基本命令
    args << "scanimage";
    
    // 设备选择
    if (!m_currentDevice.isEmpty()) {
        args << "-d" << m_currentDevice;
    }
    
    // 扫描参数
    args << "--resolution" << QString::number(m_dpi);
    args << "--mode" << m_mode;
    args << "--format" << m_format;
    
    // 输出文件
    args << "-o" << outputPath;
    
    return args.join(" ");
}

QString ScanManager::getScanOutputPath(int pageNumber)
{
    QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");
    QString filename;
    
    if (pageNumber >= 0) {
        filename = QString("scan_%1_page%2.%3")
                  .arg(timestamp)
                  .arg(pageNumber, 3, 10, QChar('0'))
                  .arg(m_format);
    } else {
        filename = QString("scan_%1.%2")
                  .arg(timestamp)
                  .arg(m_format);
    }
    
    return m_outputDir + "/" + filename;
}

void ScanManager::createOutputDirectory()
{
    QDir dir;
    if (!dir.exists(m_outputDir)) {
        dir.mkpath(m_outputDir);
    }
}

bool ScanManager::startScan(const QString &outputPath)
{
    if (m_scanProcess->state() == QProcess::Running) {
        qDebug() << "Scan process is already running";
        return false;
    }
    
    QString command = buildScanCommand(outputPath);
    QStringList args = command.split(" ", QString::SkipEmptyParts);
    
    // 移除第一个元素（scanimage命令）
    args.removeFirst();
    
    qDebug() << "Starting scan with command:" << args;
    
    m_scanProcess->start("scanimage", args);
    
    if (m_scanProcess->waitForStarted()) {
        emit scanStarted();
        return true;
    } else {
        emit scanError("Failed to start scan process");
        return false;
    }
}

void ScanManager::stopScan()
{
    if (m_scanProcess->state() == QProcess::Running) {
        m_scanProcess->terminate();
        m_scanProcess->waitForFinished(5000);
        if (m_scanProcess->state() == QProcess::Running) {
            m_scanProcess->kill();
        }
    }
}

bool ScanManager::startBatchScan(const QString &examType, const QString &className, 
                                const QString &subject, int pageCount)
{
    m_batchExamType = examType;
    m_batchClassName = className;
    m_batchSubject = subject;
    m_batchPageCount = pageCount;
    m_currentPage = 1;
    m_batchFiles.clear();
    
    // 创建子目录
    QString batchDir = QString("%1/%2_%3_%4")
                      .arg(m_outputDir)
                      .arg(examType)
                      .arg(className)
                      .arg(subject);
    
    QDir dir;
    if (!dir.exists(batchDir)) {
        dir.mkpath(batchDir);
    }
    
    m_outputDir = batchDir;
    
    // 开始第一页扫描
    QString outputPath = getScanOutputPath(m_currentPage);
    if (startScan(outputPath)) {
        return true;
    } else {
        emit scanError("Failed to start batch scan");
        return false;
    }
}

void ScanManager::onScanProcessFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    if (exitCode == 0) {
        QString outputPath = getScanOutputPath(m_currentPage);
        
        if (m_batchPageCount > 0) {
            // 批量扫描模式
            m_batchFiles.append(outputPath);
            
            if (m_currentPage < m_batchPageCount) {
                // 继续下一页
                m_currentPage++;
                emit scanProgress(m_currentPage, m_batchPageCount);
                
                // 延迟1秒后开始下一页
                m_batchTimer->singleShot(1000, this, &ScanManager::onBatchScanTimer);
            } else {
                // 批量扫描完成
                emit batchScanCompleted(m_batchFiles);
                m_batchPageCount = 0;
            }
        } else {
            // 单页扫描模式
            emit scanCompleted(outputPath);
        }
    } else {
        QString error = m_scanProcess->readAllStandardError();
        emit scanError("Scan failed: " + error);
    }
}

void ScanManager::onScanProcessError(QProcess::ProcessError error)
{
    QString errorMsg;
    switch (error) {
        case QProcess::FailedToStart:
            errorMsg = "Failed to start scan process";
            break;
        case QProcess::Crashed:
            errorMsg = "Scan process crashed";
            break;
        case QProcess::Timedout:
            errorMsg = "Scan process timed out";
            break;
        default:
            errorMsg = "Unknown scan process error";
            break;
    }
    
    emit scanError(errorMsg);
}

void ScanManager::onBatchScanTimer()
{
    QString outputPath = getScanOutputPath(m_currentPage);
    startScan(outputPath);
} 

void ScanManager::enableSimulationMode(bool enable)
{
    m_simulationMode = enable;
    qDebug() << "扫描模拟模式:" << (enable ? "启用" : "禁用");
}

void ScanManager::simulateScan(const QString &deviceName)
{
    if (!m_simulationMode) {
        qDebug() << "模拟模式未启用";
        return;
    }
    
    qDebug() << "开始模拟扫描，设备:" << deviceName;
    emit scanStarted();
    
    // 模拟扫描进度
    for (int i = 1; i <= 5; ++i) {
        QTimer::singleShot(i * 500, [this, i]() {
            emit scanProgress(i, 5);
            if (i == 5) {
                QString fileName = QString("simulated_scan_%1.png").arg(QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss"));
                emit scanCompleted(fileName);
                qDebug() << "模拟扫描完成:" << fileName;
            }
        });
    }
} 