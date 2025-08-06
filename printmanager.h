#ifndef PRINTMANAGER_H
#define PRINTMANAGER_H

#include <QObject>
#include <QProcess>
#include <QStringList>
#include <QMap>
#include <QTimer>

class PrintManager : public QObject
{
    Q_OBJECT

public:
    explicit PrintManager(QObject *parent = nullptr);
    ~PrintManager();

    // ===== 打印功能 =====
    bool printFile(const QString &deviceName, const QString &filePath, const QString &jobName = "");
    bool printFileWithOptions(const QString &deviceName, const QString &filePath, const QStringList &options);
    
    // 新增：高级打印功能
    bool printFileAdvanced(const QString &deviceName, const QString &filePath, 
                          const QString &media = "A4", 
                          const QString &sides = "two-sided-long-edge",
                          int resolution = 300, 
                          int printQuality = 5,
                          int copies = 1,
                          const QString &jobName = "");
    
    // 打印设置
    void setPrintSettings(const QString &deviceName, int copies = 1, const QString &media = "A4", 
                         const QString &sides = "two-sided-long-edge");
    
    // 打印任务管理
    void getPrintJobs(const QString &deviceName);
    void cancelPrintJob(const QString &deviceName, int jobId);
    void pausePrinter(const QString &deviceName);
    void resumePrinter(const QString &deviceName);

    // 模拟打印功能（用于测试）
    void enableSimulationMode(bool enable = true);
    bool isSimulationMode() const { return m_simulationMode; }
    void simulatePrint(const QString &deviceName, const QString &fileName);

signals:
    // 打印信号
    void printStarted(const QString &deviceName, const QString &jobName);
    void printCompleted(const QString &deviceName, const QString &jobName, int jobId);
    void printError(const QString &deviceName, const QString &error);
    void printJobsReceived(const QString &deviceName, const QMap<int, QString> &jobs);

private slots:
    void onPrintProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void onPrintProcessError(QProcess::ProcessError error);

private:
    // 进程管理
    QMap<QString, QProcess*> m_printProcesses;
    
    // 打印设置
    QMap<QString, int> m_printCopies;
    QMap<QString, QString> m_printMedia;
    QMap<QString, QString> m_printSides;
    
    // 模拟模式
    bool m_simulationMode;
    
    // 辅助方法
    QStringList buildPrintOptions(const QString &deviceName);
    int extractJobId(const QString &output);
    
    // 进程管理
    QProcess* getOrCreatePrintProcess(const QString &deviceName);
    void cleanupProcess(const QString &deviceName);
};

#endif // PRINTMANAGER_H 