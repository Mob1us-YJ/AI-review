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

    // 打印机管理
    QStringList getAvailablePrinters();
    bool selectPrinter(const QString &printerName);
    QString getDefaultPrinter();
    
    // 打印设置
    void setPrintSettings(int copies = 1, const QString &media = "A4", 
                         const QString &sides = "two-sided-long-edge");
    
    // 打印操作
    bool printFile(const QString &filePath, const QString &jobName = "");
    bool printFileWithOptions(const QString &filePath, const QStringList &options);
    
    // 打印任务管理
    void getPrintJobs();
    void cancelPrintJob(int jobId);
    void pausePrinter();
    void resumePrinter();

    // 模拟打印功能（用于测试）
    void enableSimulationMode(bool enable = true);
    bool isSimulationMode() const { return m_simulationMode; }
    void simulatePrint(const QString &fileName, const QString &printerName = "test-printer");

signals:
    void printStarted(const QString &jobName);
    void printCompleted(const QString &jobName, int jobId);
    void printError(const QString &error);
    void printJobsReceived(const QMap<int, QString> &jobs);

private slots:
    void onPrintProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void onPrintProcessError(QProcess::ProcessError error);

private:
    QProcess *m_printProcess;
    QString m_currentPrinter;
    int m_copies;
    QString m_media;
    QString m_sides;
    bool m_simulationMode; // Added for simulation mode
    
    // 辅助方法
    QString buildPrintCommand(const QString &filePath, const QString &jobName);
    QStringList buildPrintOptions();
    int extractJobId(const QString &output);
};

#endif // PRINTMANAGER_H 