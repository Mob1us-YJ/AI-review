#ifndef EXAMMANAGER_H
#define EXAMMANAGER_H

#include <QObject>
#include <QJsonArray>
#include <QJsonObject>
#include <QMap>
#include <QTimer>

class NetworkManager;
class ScanManager;
class PrintManager;

class ExamManager : public QObject
{
    Q_OBJECT

public:
    explicit ExamManager(QObject *parent = nullptr);
    ~ExamManager();

    // 初始化
    void initialize(NetworkManager *networkManager, 
                   ScanManager *scanManager, 
                   PrintManager *printManager);

    // 考试类型管理
    void refreshExamTypes();
    QStringList getExamTypes() const;
    void selectExamType(const QString &examType);

    // 班级信息管理
    void refreshClassInfo(const QString &examType);
    QJsonArray getClassesForExam(const QString &examType) const;

    // 任务管理
    void refreshScanTasks();
    void refreshPrintTasks();
    void startScanTask(const QString &examType, const QString &className, 
                      const QString &subject, int pageCount);
    void startPrintTask(const QString &taskId, const QString &filePath);

signals:
    void examTypesUpdated(const QStringList &examTypes);
    void classInfoUpdated(const QString &examType, const QJsonArray &classes);
    void scanTasksUpdated(const QJsonArray &tasks);
    void printTasksUpdated(const QJsonArray &tasks);
    void taskStatusChanged(const QString &taskId, const QString &status);

private slots:
    void onExamTypesReceived(const QJsonArray &examTypes);
    void onClassInfoReceived(const QString &examType, const QJsonArray &classes);
    void onScanTasksReceived(const QJsonArray &tasks);
    void onPrintTasksReceived(const QJsonArray &tasks);
    void onUploadCompleted(const QString &taskId, bool success);
    void onBatchScanCompleted(const QStringList &filePaths);
    void onDownloadCompleted(const QString &taskId, const QString &filePath, bool success);
    void onPrintCompleted(const QString &jobName, int jobId);
    void onNetworkError(const QString &error);
    void onScanError(const QString &error);
    void onPrintError(const QString &error);

private:
    NetworkManager *m_networkManager;
    ScanManager *m_scanManager;
    PrintManager *m_printManager;
    
    // 数据存储
    QStringList m_examTypes;
    QMap<QString, QJsonArray> m_classInfo;
    QJsonArray m_scanTasks;
    QJsonArray m_printTasks;
    
    // 当前状态
    QString m_currentExamType;
    QString m_currentScanTask;
    
    // 定时器
    QTimer *m_pollTimer;
    
    // 辅助方法
    void updateTaskStatus(const QString &taskId, const QString &status);
    void moveTaskFromScanToPrint(const QString &taskId);
    void checkPrintTaskStatus();
};

#endif // EXAMMANAGER_H 