#include "networkmanager.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QHttpMultiPart>
#include <QFile>
#include <QDir>
#include <QStandardPaths>
#include <QDebug>

NetworkManager::NetworkManager(QObject *parent)
    : QObject(parent),
      m_networkManager(new QNetworkAccessManager(this)),
      m_pollTimer(new QTimer(this)),
      m_simulationMode(false)
{
    m_serverUrl = "http://localhost:8080/api"; // 默认服务器地址
    m_apiKey = "";
    
    // 设置定时器用于轮询打印任务状态
    m_pollTimer->setInterval(30000); // 30秒轮询一次
    connect(m_pollTimer, &QTimer::timeout, this, &NetworkManager::requestPrintTasks);
    
    connect(m_networkManager, &QNetworkAccessManager::finished,
            this, &NetworkManager::onRequestFinished);
}

NetworkManager::~NetworkManager()
{
}

void NetworkManager::setServerUrl(const QString &url)
{
    m_serverUrl = url;
}

void NetworkManager::setApiKey(const QString &key)
{
    m_apiKey = key;
}

QNetworkRequest NetworkManager::createRequest(const QString &endpoint)
{
    QNetworkRequest request;
    request.setUrl(QUrl(m_serverUrl + endpoint));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    
    if (!m_apiKey.isEmpty()) {
        request.setRawHeader("Authorization", "Bearer " + m_apiKey.toUtf8());
    }
    
    return request;
}

void NetworkManager::requestExamTypes()
{
    QNetworkRequest request = createRequest("/exam-types");
    QNetworkReply *reply = m_networkManager->get(request);
    reply->setProperty("requestType", "examTypes");
}

void NetworkManager::requestClassInfo(const QString &examType)
{
    QNetworkRequest request = createRequest("/classes/" + examType);
    QNetworkReply *reply = m_networkManager->get(request);
    reply->setProperty("requestType", "classInfo");
    reply->setProperty("examType", examType);
}

void NetworkManager::uploadScanData(const QString &examType, const QString &className,
                                   const QString &subject, const QStringList &scanFiles)
{
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    
    // 添加表单数据
    QHttpPart examTypePart;
    examTypePart.setHeader(QNetworkRequest::ContentDispositionHeader, 
                          QVariant("form-data; name=\"examType\""));
    examTypePart.setBody(examType.toUtf8());
    multiPart->append(examTypePart);
    
    QHttpPart classPart;
    classPart.setHeader(QNetworkRequest::ContentDispositionHeader, 
                       QVariant("form-data; name=\"className\""));
    classPart.setBody(className.toUtf8());
    multiPart->append(classPart);
    
    QHttpPart subjectPart;
    subjectPart.setHeader(QNetworkRequest::ContentDispositionHeader, 
                         QVariant("form-data; name=\"subject\""));
    subjectPart.setBody(subject.toUtf8());
    multiPart->append(subjectPart);
    
    // 添加文件
    for (const QString &filePath : scanFiles) {
        QFile *file = new QFile(filePath);
        if (file->open(QIODevice::ReadOnly)) {
            QHttpPart filePart;
            filePart.setHeader(QNetworkRequest::ContentDispositionHeader, 
                              QVariant("form-data; name=\"files\"; filename=\"" + 
                                      QFileInfo(filePath).fileName() + "\""));
            filePart.setBodyDevice(file);
            multiPart->append(filePart);
        }
    }
    
    QNetworkRequest request = createRequest("/upload-scan");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "multipart/form-data; boundary=" + multiPart->boundary());
    
    QNetworkReply *reply = m_networkManager->post(request, multiPart);
    reply->setProperty("requestType", "uploadScan");
    multiPart->setParent(reply);
    
    connect(reply, &QNetworkReply::uploadProgress,
            this, &NetworkManager::onUploadProgress);
}

void NetworkManager::requestScanTasks()
{
    QNetworkRequest request = createRequest("/scan-tasks");
    QNetworkReply *reply = m_networkManager->get(request);
    reply->setProperty("requestType", "scanTasks");
}

void NetworkManager::requestPrintTasks()
{
    QNetworkRequest request = createRequest("/print-tasks");
    QNetworkReply *reply = m_networkManager->get(request);
    reply->setProperty("requestType", "printTasks");
}

void NetworkManager::downloadPrintFile(const QString &taskId, const QString &fileUrl)
{
    QNetworkRequest request;
    request.setUrl(QUrl(fileUrl));
    
    QNetworkReply *reply = m_networkManager->get(request);
    reply->setProperty("requestType", "downloadPrint");
    reply->setProperty("taskId", taskId);
    
    connect(reply, &QNetworkReply::downloadProgress,
            this, &NetworkManager::onDownloadProgress);
}

void NetworkManager::updatePrintStatus(const QString &taskId, const QString &status)
{
    QJsonObject data;
    data["taskId"] = taskId;
    data["status"] = status;
    
    QNetworkRequest request = createRequest("/print-status");
    QNetworkReply *reply = m_networkManager->post(request, 
                                                 QJsonDocument(data).toJson());
    reply->setProperty("requestType", "updatePrintStatus");
}

void NetworkManager::onRequestFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply) return;
    
    if (reply->error() == QNetworkReply::NoError) {
        handleJsonResponse(reply);
    } else {
        handleError(reply);
    }
    
    reply->deleteLater();
}

void NetworkManager::handleJsonResponse(QNetworkReply *reply)
{
    QString requestType = reply->property("requestType").toString();
    QByteArray data = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    
    if (requestType == "examTypes") {
        if (doc.isArray()) {
            emit examTypesReceived(doc.array());
        }
    } else if (requestType == "classInfo") {
        QString examType = reply->property("examType").toString();
        if (doc.isArray()) {
            emit classInfoReceived(examType, doc.array());
        }
    } else if (requestType == "scanTasks") {
        if (doc.isArray()) {
            emit scanTasksReceived(doc.array());
        }
    } else if (requestType == "printTasks") {
        if (doc.isArray()) {
            emit printTasksReceived(doc.array());
        }
    } else if (requestType == "uploadScan") {
        QJsonObject response = doc.object();
        QString taskId = response["taskId"].toString();
        bool success = response["success"].toBool();
        emit uploadCompleted(taskId, success);
    } else if (requestType == "downloadPrint") {
        QString taskId = reply->property("taskId").toString();
        QString downloadPath = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation) 
                              + "/print_" + taskId + ".pdf";
        
        QFile file(downloadPath);
        if (file.open(QIODevice::WriteOnly)) {
            file.write(reply->readAll());
            file.close();
            emit downloadCompleted(taskId, downloadPath, true);
        } else {
            emit downloadCompleted(taskId, "", false);
        }
    }
}

void NetworkManager::handleError(QNetworkReply *reply)
{
    QString errorString = reply->errorString();
    qDebug() << "Network error:" << errorString;
    emit networkError(errorString);
}

void NetworkManager::onUploadProgress(qint64 bytesSent, qint64 bytesTotal)
{
    if (bytesTotal > 0) {
        int progress = (bytesSent * 100) / bytesTotal;
        qDebug() << "Upload progress:" << progress << "%";
    }
}

void NetworkManager::onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    if (bytesTotal > 0) {
        int progress = (bytesReceived * 100) / bytesTotal;
        qDebug() << "Download progress:" << progress << "%";
    }
} 

void NetworkManager::enableSimulationMode(bool enable)
{
    m_simulationMode = enable;
    qDebug() << "网络模拟模式:" << (enable ? "启用" : "禁用");
}

void NetworkManager::simulateNetworkResponse(const QString &endpoint)
{
    if (!m_simulationMode) {
        qDebug() << "模拟模式未启用";
        return;
    }
    
    qDebug() << "模拟网络响应，端点:" << endpoint;
    
    // 模拟不同的API响应
    if (endpoint.contains("exam-types")) {
        QJsonArray examTypes;
        examTypes.append("期中考试");
        examTypes.append("期末考试");
        examTypes.append("月考");
        emit examTypesReceived(examTypes);
    } else if (endpoint.contains("class-info")) {
        QJsonArray classes;
        classes.append(QJsonObject{{"name", "高一(1)班"}, {"id", "1"}});
        classes.append(QJsonObject{{"name", "高一(2)班"}, {"id", "2"}});
        classes.append(QJsonObject{{"name", "高一(3)班"}, {"id", "3"}});
        emit classInfoReceived("期中考试", classes);
    } else if (endpoint.contains("scan-tasks")) {
        QJsonArray tasks;
        tasks.append(QJsonObject{
            {"id", "1"}, {"className", "高一(1)班"}, {"subject", "数学"},
            {"paper", "A3双面"}, {"status", "待扫描"}, {"quantity", "50"},
            {"time", "2025/8/2 8:07:25"}
        });
        emit scanTasksReceived(tasks);
    } else if (endpoint.contains("print-tasks")) {
        QJsonArray tasks;
        tasks.append(QJsonObject{
            {"id", "2"}, {"className", "高一(2)班"}, {"subject", "语文"},
            {"paper", "A4单面"}, {"status", "可打印"}, {"quantity", "30"},
            {"time", "2025/8/2 9:15:30"}
        });
        emit printTasksReceived(tasks);
    }
} 