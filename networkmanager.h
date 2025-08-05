#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QTimer>

class NetworkManager : public QObject
{
    Q_OBJECT

public:
    explicit NetworkManager(QObject *parent = nullptr);
    ~NetworkManager();

    // 服务器配置
    void setServerUrl(const QString &url);
    void setApiKey(const QString &key);

    // 考试类型管理
    void requestExamTypes();
    void requestClassInfo(const QString &examType);

    // 扫描任务管理
    void uploadScanData(const QString &examType, const QString &className, 
                       const QString &subject, const QStringList &scanFiles);
    void requestScanTasks();

    // 打印任务管理
    void requestPrintTasks();
    void downloadPrintFile(const QString &taskId, const QString &fileUrl);
    void updatePrintStatus(const QString &taskId, const QString &status);

    // 模拟网络功能（用于测试）
    void enableSimulationMode(bool enable = true);
    bool isSimulationMode() const { return m_simulationMode; }
    void simulateNetworkResponse(const QString &endpoint);

signals:
    // 考试类型相关信号
    void examTypesReceived(const QJsonArray &examTypes);
    void classInfoReceived(const QString &examType, const QJsonArray &classes);
    
    // 扫描任务相关信号
    void scanTasksReceived(const QJsonArray &tasks);
    void uploadCompleted(const QString &taskId, bool success);
    
    // 打印任务相关信号
    void printTasksReceived(const QJsonArray &tasks);
    void downloadCompleted(const QString &taskId, const QString &filePath, bool success);
    
    // 错误信号
    void networkError(const QString &error);

private slots:
    void onRequestFinished();
    void onUploadProgress(qint64 bytesSent, qint64 bytesTotal);
    void onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);

private:
    QNetworkAccessManager *m_networkManager;
    QString m_serverUrl;
    QString m_apiKey;
    QTimer *m_pollTimer;
    bool m_simulationMode;
    
    // 请求辅助方法
    QNetworkRequest createRequest(const QString &endpoint);
    void handleJsonResponse(QNetworkReply *reply);
    void handleError(QNetworkReply *reply);
};

#endif // NETWORKMANAGER_H 