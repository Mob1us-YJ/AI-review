#ifndef SCANMANAGER_H
#define SCANMANAGER_H

#include <QObject>
#include <QProcess>
#include <QStringList>
#include <QDir>
#include <QTimer>

class ScanManager : public QObject
{
    Q_OBJECT

public:
    explicit ScanManager(QObject *parent = nullptr);
    ~ScanManager();

    // 扫描设备管理
    QStringList getAvailableDevices();
    bool selectDevice(const QString &deviceName);
    
    // 扫描设置
    void setScanSettings(int dpi = 300, const QString &format = "pdf", 
                        const QString &mode = "color");
    
    // 扫描操作
    bool startScan(const QString &outputPath);
    void stopScan();
    
    // 批量扫描
    bool startBatchScan(const QString &examType, const QString &className, 
                       const QString &subject, int pageCount);

    // 模拟扫描功能（用于测试）
    void enableSimulationMode(bool enable = true);
    bool isSimulationMode() const { return m_simulationMode; }
    void simulateScan(const QString &deviceName = "test-scanner");

signals:
    void scanStarted();
    void scanProgress(int current, int total);
    void scanCompleted(const QString &filePath);
    void scanError(const QString &error);
    void batchScanCompleted(const QStringList &filePaths);

private slots:
    void onScanProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void onScanProcessError(QProcess::ProcessError error);
    void onBatchScanTimer();

private:
    QProcess *m_scanProcess;
    QString m_currentDevice;
    QString m_outputDir;
    int m_dpi;
    QString m_format;
    QString m_mode;
    
    // 批量扫描相关
    QTimer *m_batchTimer;
    QString m_batchExamType;
    QString m_batchClassName;
    QString m_batchSubject;
    int m_batchPageCount;
    int m_currentPage;
    QStringList m_batchFiles;
    
    // 模拟扫描模式
    bool m_simulationMode;
    
    // 辅助方法
    QString buildScanCommand(const QString &outputPath);
    QString getScanOutputPath(int pageNumber = -1);
    void createOutputDirectory();
};

#endif // SCANMANAGER_H 