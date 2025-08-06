#ifndef SCANMANAGER_H
#define SCANMANAGER_H

#include <QObject>
#include <QProcess>
#include <QStringList>
#include <QDir>
#include <QTimer>
#include <QMap> // Added for QMap

class ScanManager : public QObject
{
    Q_OBJECT

public:
    explicit ScanManager(QObject *parent = nullptr);
    ~ScanManager();

    // ===== 扫描功能 =====
    bool startScan(const QString &deviceName, const QString &outputPath);
    void stopScan(const QString &deviceName);
    
    // 批量扫描
    bool startBatchScan(const QString &deviceName, const QString &examType, 
                       const QString &className, const QString &subject, int pageCount);
    
    // 扫描设置
    void setScanSettings(const QString &deviceName, int dpi = 300, const QString &format = "jpeg", 
                        const QString &mode = "Color", bool duplex = false);
    
    // 网络上传功能
    void uploadFile(const QString &deviceName, const QString &filePath, 
                   const QString &parentPath = "/exam/");
    void setUploadServer(const QString &serverUrl = "http://117.72.74.246:18000");
    
    // 模拟扫描功能（用于测试）
    void enableSimulationMode(bool enable = true);
    bool isSimulationMode() const { return m_simulationMode; }
    void simulateScan(const QString &deviceName);
    void simulateUpload(const QString &deviceName, const QString &filePath);

signals:
    // 扫描信号
    void scanStarted(const QString &deviceName);
    void scanProgress(const QString &deviceName, int current, int total);
    void scanCompleted(const QString &deviceName, const QString &filePath);
    void scanError(const QString &deviceName, const QString &error);
    void batchScanCompleted(const QString &deviceName, const QStringList &filePaths);
    
    // 上传信号
    void uploadStarted(const QString &deviceName, const QString &filePath);
    void uploadProgress(const QString &deviceName, int percentage);
    void uploadCompleted(const QString &deviceName, const QString &fileUrl);
    void uploadError(const QString &deviceName, const QString &error);

private slots:
    void onScanProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void onScanProcessError(QProcess::ProcessError error);
    void onBatchScanTimer();
    
    // 上传进程相关
    void onUploadProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void onUploadProcessError(QProcess::ProcessError error);

private:
    // 进程管理
    QMap<QString, QProcess*> m_scanProcesses;
    QMap<QString, QProcess*> m_uploadProcesses;
    
    // 批量扫描相关
    QTimer *m_batchTimer;
    QMap<QString, QStringList> m_batchFiles;
    QMap<QString, int> m_batchPageCounts;
    QMap<QString, int> m_currentPages;
    
    // 扫描设置
    QMap<QString, int> m_scanDpi;
    QMap<QString, QString> m_scanFormat;
    QMap<QString, QString> m_scanMode;
    QMap<QString, bool> m_scanDuplex;
    
    // 网络设置
    QString m_uploadServer;
    
    // 模拟模式
    bool m_simulationMode;
    
    // 辅助方法
    QString buildScanCommand(const QString &deviceName, const QString &outputPath);
    QString getScanOutputPath(const QString &deviceName, int pageNumber = -1);
    void createOutputDirectory(const QString &deviceName);
    
    // 进程管理
    QProcess* getOrCreateScanProcess(const QString &deviceName);
    QProcess* getOrCreateUploadProcess(const QString &deviceName);
    void cleanupProcess(const QString &deviceName, const QString &processType);
};

#endif // SCANMANAGER_H 