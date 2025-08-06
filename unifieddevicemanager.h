#ifndef UNIFIEDDEVICEMANAGER_H
#define UNIFIEDDEVICEMANAGER_H

#include <QObject>
#include <QProcess>
#include <QStringList>
#include <QMap>
#include <QTimer>

class UnifiedDeviceManager : public QObject
{
    Q_OBJECT

public:
    explicit UnifiedDeviceManager(QObject *parent = nullptr);
    ~UnifiedDeviceManager();

    // ===== 设备管理 =====
    QStringList discoverDevices();
    QStringList getMultifunctionDevices();
    bool selectDevice(const QString &deviceName);
    QString getCurrentDevice() const { return m_currentDevice; }
    
    // 设备信息
    QString getDeviceType(const QString &deviceName);
    QString getDeviceModel(const QString &deviceName);
    QString getDeviceCapabilities(const QString &deviceName);
    QString getDeviceStatus(const QString &deviceName);
    
    // 功能检测
    bool isMultifunctionDevice(const QString &deviceName);
    bool canScan(const QString &deviceName);
    bool canPrint(const QString &deviceName);
    bool canCopy(const QString &deviceName);
    bool canFax(const QString &deviceName);

    // ===== 扫描功能 =====
    bool startScan(const QString &deviceName, const QString &outputPath);
    bool startBatchScan(const QString &deviceName, const QString &examType, 
                       const QString &className, const QString &subject, int pageCount);
    void stopScan(const QString &deviceName);
    void setScanSettings(const QString &deviceName, int dpi = 300, const QString &format = "jpeg", 
                        const QString &mode = "Color", bool duplex = false);
    
    // ===== 打印功能 =====
    bool printFile(const QString &deviceName, const QString &filePath, const QString &jobName = "");
    void setPrintSettings(const QString &deviceName, int copies = 1, const QString &media = "A4", 
                         const QString &sides = "two-sided-long-edge");
    void getPrintJobs(const QString &deviceName);
    void cancelPrintJob(const QString &deviceName, int jobId);
    void pausePrinter(const QString &deviceName);
    void resumePrinter(const QString &deviceName);
    
    // ===== 网络上传功能 =====
    void uploadFile(const QString &deviceName, const QString &filePath, 
                   const QString &parentPath = "/exam/");
    void setUploadServer(const QString &serverUrl = "http://117.72.74.246:18000");
    
    // ===== 模拟模式 =====
    void enableSimulationMode(bool enable = true);
    bool isSimulationMode() const { return m_simulationMode; }
    void simulateScan(const QString &deviceName);
    void simulatePrint(const QString &deviceName, const QString &fileName);
    void simulateUpload(const QString &deviceName, const QString &filePath);

signals:
    // 设备管理信号
    void deviceDiscovered(const QString &deviceName, const QString &deviceType);
    void deviceSelected(const QString &deviceName);
    void deviceStatusChanged(const QString &deviceName, const QString &status);
    void deviceError(const QString &deviceName, const QString &error);
    
    // 扫描信号
    void scanStarted(const QString &deviceName);
    void scanProgress(const QString &deviceName, int current, int total);
    void scanCompleted(const QString &deviceName, const QString &filePath);
    void scanError(const QString &deviceName, const QString &error);
    void batchScanCompleted(const QString &deviceName, const QStringList &filePaths);
    
    // 打印信号
    void printStarted(const QString &deviceName, const QString &jobName);
    void printCompleted(const QString &deviceName, const QString &jobName, int jobId);
    void printError(const QString &deviceName, const QString &error);
    void printJobsReceived(const QString &deviceName, const QMap<int, QString> &jobs);
    
    // 上传信号
    void uploadStarted(const QString &deviceName, const QString &filePath);
    void uploadProgress(const QString &deviceName, int percentage);
    void uploadCompleted(const QString &deviceName, const QString &fileUrl);
    void uploadError(const QString &deviceName, const QString &error);

private slots:
    // 扫描进程相关
    void onScanProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void onScanProcessError(QProcess::ProcessError error);
    void onBatchScanTimer();
    
    // 打印进程相关
    void onPrintProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void onPrintProcessError(QProcess::ProcessError error);
    
    // 上传进程相关
    void onUploadProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void onUploadProcessError(QProcess::ProcessError error);

private:
    QString m_currentDevice;
    bool m_simulationMode;
    
    // 设备数据库
    QMap<QString, QString> m_deviceTypes;
    QMap<QString, QString> m_deviceModels;
    QMap<QString, QStringList> m_deviceCapabilities;
    QMap<QString, QMap<QString, QString>> m_deviceConfigs;
    
    // 进程管理
    QMap<QString, QProcess*> m_scanProcesses;
    QMap<QString, QProcess*> m_printProcesses;
    QMap<QString, QProcess*> m_uploadProcesses;
    
    // 批量扫描相关
    QTimer *m_batchTimer;
    QMap<QString, QStringList> m_batchFiles;
    QMap<QString, int> m_batchPageCounts;
    QMap<QString, int> m_currentPages;
    
    // 网络设置
    QString m_uploadServer;
    
    // 辅助方法
    void initializeDeviceDatabase();
    void detectBrotherMFCJ3940DW();
    QStringList parseDeviceCapabilities(const QString &deviceName);
    
    // 命令构建
    QString buildScanCommand(const QString &deviceName, const QString &outputPath);
    QStringList buildPrintOptions(const QString &deviceName);
    QStringList buildUploadCommand(const QString &filePath, const QString &parentPath);
    
    // 文件管理
    QString getScanOutputPath(const QString &deviceName, int pageNumber = -1);
    void createOutputDirectory(const QString &deviceName);
    
    // 进程管理
    QProcess* getOrCreateProcess(const QString &deviceName, const QString &processType);
    void cleanupProcess(const QString &deviceName, const QString &processType);
};

#endif // UNIFIEDDEVICEMANAGER_H 