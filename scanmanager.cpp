#include "scanmanager.h"
#include <QStandardPaths>
#include <QDateTime>
#include <QDebug>
#include <QFileInfo>
#include <QRegularExpression> // Added for JSON parsing

ScanManager::ScanManager(QObject *parent)
    : QObject(parent),
      m_batchTimer(new QTimer(this)),
      m_uploadServer("http://117.72.74.246:18000"),
      m_simulationMode(false)
{
    // 批量扫描定时器
    connect(m_batchTimer, &QTimer::timeout, this, &ScanManager::onBatchScanTimer);
}

ScanManager::~ScanManager()
{
    // 清理所有扫描进程
    for (auto process : m_scanProcesses.values()) {
        if (process) {
            process->terminate();
            process->waitForFinished();
            delete process;
        }
    }
    m_scanProcesses.clear();
    
    // 清理所有上传进程
    for (auto process : m_uploadProcesses.values()) {
        if (process) {
            process->terminate();
            process->waitForFinished();
            delete process;
        }
    }
    m_uploadProcesses.clear();
}





void ScanManager::setScanSettings(const QString &deviceName, int dpi, const QString &format, const QString &mode, bool duplex)
{
    m_scanDpi[deviceName] = dpi;
    m_scanFormat[deviceName] = format;
    m_scanMode[deviceName] = mode;
    m_scanDuplex[deviceName] = duplex;
    
    qDebug() << "扫描设置已更新，设备:" << deviceName 
             << "DPI:" << dpi << "格式:" << format << "模式:" << mode << "双面:" << duplex;
}



QString ScanManager::buildScanCommand(const QString &deviceName, const QString &outputPath)
{
    QStringList args;
    
    // 基本命令
    args << "scanimage";
    
    // 设备选择
    if (!deviceName.isEmpty()) {
        args << "--device-name=" + deviceName;
    }
    
    // 获取该设备的扫描设置
    int dpi = m_scanDpi.value(deviceName, 300);
    QString format = m_scanFormat.value(deviceName, "jpeg");
    QString mode = m_scanMode.value(deviceName, "Color");
    bool duplex = m_scanDuplex.value(deviceName, false);
    
    // 扫描参数
    args << "--mode" << mode;
    args << "-x" << "297.11" << "-y" << "420";  // A4纸张尺寸
    args << "--resolution" << QString::number(dpi);
    args << "--format" << format;
    
    // 扫描源选择 - 支持ADF和双面扫描
    if (duplex) {
        args << "--source=ADF Duplex";
    } else {
        args << "--source=ADF";
    }
    
    // 输出文件
    args << "-o" << outputPath;
    
    return args.join(" ");
}

QString ScanManager::getScanOutputPath(const QString &deviceName, int pageNumber)
{
    QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");
    QString format = m_scanFormat.value(deviceName, "jpeg");
    QString filename;
    
    if (pageNumber >= 0) {
        filename = QString("scan_%1_page%2.%3")
                  .arg(timestamp)
                  .arg(pageNumber, 3, 10, QChar('0'))
                  .arg(format);
    } else {
        filename = QString("scan_%1.%2")
                  .arg(timestamp)
                  .arg(format);
    }
    
    QString outputDir = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) 
                       + "/AIReview/Scans/" + deviceName;
    return outputDir + "/" + filename;
}

void ScanManager::createOutputDirectory(const QString &deviceName)
{
    QString outputDir = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) 
                       + "/AIReview/Scans/" + deviceName;
    QDir dir;
    if (!dir.exists(outputDir)) {
        dir.mkpath(outputDir);
    }
}

QProcess* ScanManager::getOrCreateScanProcess(const QString &deviceName)
{
    if (!m_scanProcesses.contains(deviceName)) {
        QProcess *process = new QProcess(this);
        connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
                this, &ScanManager::onScanProcessFinished);
        connect(process, &QProcess::errorOccurred,
                this, &ScanManager::onScanProcessError);
        m_scanProcesses[deviceName] = process;
    }
    return m_scanProcesses[deviceName];
}

QProcess* ScanManager::getOrCreateUploadProcess(const QString &deviceName)
{
    if (!m_uploadProcesses.contains(deviceName)) {
        QProcess *process = new QProcess(this);
        connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
                this, &ScanManager::onUploadProcessFinished);
        connect(process, &QProcess::errorOccurred,
                this, &ScanManager::onUploadProcessError);
        m_uploadProcesses[deviceName] = process;
    }
    return m_uploadProcesses[deviceName];
}

void ScanManager::cleanupProcess(const QString &deviceName, const QString &processType)
{
    if (processType == "scan") {
        if (m_scanProcesses.contains(deviceName)) {
            QProcess *process = m_scanProcesses[deviceName];
            if (process) {
                process->terminate();
                process->waitForFinished(5000);
                if (process->state() == QProcess::Running) {
                    process->kill();
                }
                delete process;
            }
            m_scanProcesses.remove(deviceName);
        }
    } else if (processType == "upload") {
        if (m_uploadProcesses.contains(deviceName)) {
            QProcess *process = m_uploadProcesses[deviceName];
            if (process) {
                process->terminate();
                process->waitForFinished(5000);
                if (process->state() == QProcess::Running) {
                    process->kill();
                }
                delete process;
            }
            m_uploadProcesses.remove(deviceName);
        }
    }
}

bool ScanManager::startScan(const QString &deviceName, const QString &outputPath)
{
    QProcess *process = getOrCreateScanProcess(deviceName);
    
    if (process->state() == QProcess::Running) {
        qDebug() << "Scan process is already running for device:" << deviceName;
        return false;
    }
    
    // 直接构建参数列表，避免字符串分割问题
    QStringList args;
    
    // 设备选择
    if (!deviceName.isEmpty()) {
        args << "--device-name=" + deviceName;
    }
    
    // 获取该设备的扫描设置
    int dpi = m_scanDpi.value(deviceName, 300);
    QString format = m_scanFormat.value(deviceName, "jpeg");
    QString mode = m_scanMode.value(deviceName, "Color");
    bool duplex = m_scanDuplex.value(deviceName, false);
    
    // 扫描参数
    args << "--mode" << mode;
    args << "-x" << "297.11" << "-y" << "420";  // A4纸张尺寸
    args << "--resolution" << QString::number(dpi);
    args << "--format" << format;
    
    // 扫描源选择 - 支持ADF和双面扫描
    if (duplex) {
        args << "--source=ADF Duplex";
    } else {
        args << "--source=ADF";
    }
    
    // 输出文件
    args << "-o" << outputPath;
    
    qDebug() << "Starting scan with command:" << args;
    
    process->start("scanimage", args);
    
    if (process->waitForStarted()) {
        emit scanStarted(deviceName);
        return true;
    } else {
        emit scanError(deviceName, "Failed to start scan process");
        return false;
    }
}

void ScanManager::stopScan(const QString &deviceName)
{
    if (m_scanProcesses.contains(deviceName)) {
        QProcess *process = m_scanProcesses[deviceName];
        if (process && process->state() == QProcess::Running) {
            process->terminate();
            process->waitForFinished(5000);
            if (process->state() == QProcess::Running) {
                process->kill();
            }
        }
    }
}



void ScanManager::onScanProcessFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    QProcess *process = qobject_cast<QProcess*>(sender());
    if (!process) return;
    
    // 找到对应的设备名称
    QString deviceName;
    for (auto it = m_scanProcesses.begin(); it != m_scanProcesses.end(); ++it) {
        if (it.value() == process) {
            deviceName = it.key();
            break;
        }
    }
    
    if (exitCode == 0) {
        QString outputPath = getScanOutputPath(deviceName, -1);
        emit scanCompleted(deviceName, outputPath);
    } else {
        QString error = process->readAllStandardError();
        emit scanError(deviceName, "Scan failed: " + error);
    }
}

void ScanManager::onScanProcessError(QProcess::ProcessError error)
{
    QProcess *process = qobject_cast<QProcess*>(sender());
    if (!process) return;
    
    // 找到对应的设备名称
    QString deviceName;
    for (auto it = m_scanProcesses.begin(); it != m_scanProcesses.end(); ++it) {
        if (it.value() == process) {
            deviceName = it.key();
            break;
        }
    }
    
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
    
    emit scanError(deviceName, errorMsg);
}

 

void ScanManager::enableSimulationMode(bool enable)
{
    m_simulationMode = enable;
    qDebug() << "扫描模拟模式:" << (enable ? "启用" : "禁用");
}

// 新增：设置上传服务器
void ScanManager::setUploadServer(const QString &serverUrl)
{
    m_uploadServer = serverUrl;
    qDebug() << "设置上传服务器:" << serverUrl;
}

// 新增：上传文件
void ScanManager::uploadFile(const QString &deviceName, const QString &filePath, const QString &parentPath)
{
    if (!QFile::exists(filePath)) {
        emit uploadError(deviceName, "文件不存在: " + filePath);
        return;
    }
    
    QProcess *process = getOrCreateUploadProcess(deviceName);
    if (!process) {
        emit uploadError(deviceName, "无法创建上传进程");
        return;
    }
    
    QStringList args;
    args << "-X" << "POST";
    args << m_uploadServer + "/system/file/upload";
    args << "-F" << "parentPath=" + parentPath;
    args << "-F" << "file=@" + filePath;
    
    qDebug() << "开始上传文件:" << filePath;
    emit uploadStarted(deviceName, filePath);
    
    process->start("curl", args);
}

void ScanManager::onUploadProcessFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    QProcess *process = qobject_cast<QProcess*>(sender());
    if (!process) return;
    
    // 找到对应的设备名称
    QString deviceName;
    for (auto it = m_uploadProcesses.begin(); it != m_uploadProcesses.end(); ++it) {
        if (it.value() == process) {
            deviceName = it.key();
            break;
        }
    }
    
    if (exitCode == 0) {
        QString output = process->readAllStandardOutput();
        // 解析JSON响应获取文件URL
        QRegularExpression regex("\"url\":\"([^\"]+)\"");
        QRegularExpressionMatch match = regex.match(output);
        
        if (match.hasMatch()) {
            QString fileUrl = match.captured(1);
            emit uploadCompleted(deviceName, fileUrl);
            qDebug() << "文件上传成功:" << fileUrl;
        } else {
            emit uploadError(deviceName, "无法解析上传响应");
        }
    } else {
        QString error = process->readAllStandardError();
        emit uploadError(deviceName, "上传失败: " + error);
    }
}

void ScanManager::onUploadProcessError(QProcess::ProcessError error)
{
    QProcess *process = qobject_cast<QProcess*>(sender());
    if (!process) return;
    
    // 找到对应的设备名称
    QString deviceName;
    for (auto it = m_uploadProcesses.begin(); it != m_uploadProcesses.end(); ++it) {
        if (it.value() == process) {
            deviceName = it.key();
            break;
        }
    }
    
    QString errorMsg;
    switch (error) {
        case QProcess::FailedToStart:
            errorMsg = "无法启动上传进程";
            break;
        case QProcess::Crashed:
            errorMsg = "上传进程崩溃";
            break;
        case QProcess::Timedout:
            errorMsg = "上传进程超时";
            break;
        default:
            errorMsg = "未知上传错误";
            break;
    }
    
    emit uploadError(deviceName, errorMsg);
} 

void ScanManager::simulateScan(const QString &deviceName)
{
    if (!m_simulationMode) {
        qDebug() << "模拟模式未启用";
        return;
    }
    
    qDebug() << "开始模拟扫描，设备:" << deviceName;
    emit scanStarted(deviceName);
    
    // 模拟扫描进度
    for (int i = 1; i <= 5; ++i) {
        QTimer::singleShot(i * 500, [this, deviceName, i]() {
            emit scanProgress(deviceName, i, 5);
            if (i == 5) {
                QString fileName = QString("simulated_scan_%1.png").arg(QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss"));
                emit scanCompleted(deviceName, fileName);
                qDebug() << "模拟扫描完成:" << fileName;
            }
        });
    }
}

bool ScanManager::startBatchScan(const QString &deviceName, const QString &examType, 
                               const QString &className, const QString &subject, int pageCount)
{
    qDebug() << "开始批量扫描，设备:" << deviceName 
             << "考试类型:" << examType 
             << "班级:" << className 
             << "学科:" << subject 
             << "页数:" << pageCount;
    
    // 初始化批量扫描状态
    m_batchPageCounts[deviceName] = pageCount;
    m_currentPages[deviceName] = 0;
    m_batchFiles[deviceName].clear();
    
    // 创建输出目录
    createOutputDirectory(deviceName);
    
    // 启动批量扫描定时器
    m_batchTimer->start(2000); // 每2秒扫描一页
    
    emit scanStarted(deviceName);
    return true;
}

void ScanManager::onBatchScanTimer()
{
    // 遍历所有进行批量扫描的设备
    for (auto it = m_batchPageCounts.begin(); it != m_batchPageCounts.end(); ++it) {
        QString deviceName = it.key();
        int totalPages = it.value();
        int currentPage = m_currentPages.value(deviceName, 0);
        
        if (currentPage < totalPages) {
            // 扫描当前页
            QString outputPath = getScanOutputPath(deviceName, currentPage + 1);
            
            if (startScan(deviceName, outputPath)) {
                m_batchFiles[deviceName].append(outputPath);
                m_currentPages[deviceName] = currentPage + 1;
                
                emit scanProgress(deviceName, currentPage + 1, totalPages);
                
                qDebug() << "批量扫描进度:" << deviceName 
                         << "当前页:" << (currentPage + 1) 
                         << "总页数:" << totalPages;
            }
        } else {
            // 批量扫描完成
            QStringList filePaths = m_batchFiles.value(deviceName);
            emit batchScanCompleted(deviceName, filePaths);
            
            qDebug() << "批量扫描完成:" << deviceName 
                     << "文件数量:" << filePaths.size();
            
            // 清理状态
            m_batchPageCounts.remove(deviceName);
            m_currentPages.remove(deviceName);
            m_batchFiles.remove(deviceName);
        }
    }
    
    // 如果没有设备在进行批量扫描，停止定时器
    if (m_batchPageCounts.isEmpty()) {
        m_batchTimer->stop();
    }
} 