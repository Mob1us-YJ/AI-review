#include "exammanager.h"
#include "networkmanager.h"
#include "scanmanager.h"
#include "printmanager.h"
#include <QDebug>
#include <QJsonDocument>

ExamManager::ExamManager(QObject *parent)
    : QObject(parent)
    , m_networkManager(nullptr)
    , m_scanManager(nullptr)
    , m_printManager(nullptr)
    , m_pollTimer(new QTimer(this))
{
    // 设置定时器用于轮询任务状态
    m_pollTimer->setInterval(30000); // 30秒轮询一次
    connect(m_pollTimer, &QTimer::timeout, this, &ExamManager::checkPrintTaskStatus);
}

ExamManager::~ExamManager()
{
}

void ExamManager::initialize(NetworkManager *networkManager, 
                           ScanManager *scanManager, 
                           PrintManager *printManager)
{
    m_networkManager = networkManager;
    m_scanManager = scanManager;
    m_printManager = printManager;
    
    // 连接网络管理器信号
    connect(m_networkManager, &NetworkManager::examTypesReceived,
            this, &ExamManager::onExamTypesReceived);
    connect(m_networkManager, &NetworkManager::classInfoReceived,
            this, &ExamManager::onClassInfoReceived);
    connect(m_networkManager, &NetworkManager::scanTasksReceived,
            this, &ExamManager::onScanTasksReceived);
    connect(m_networkManager, &NetworkManager::printTasksReceived,
            this, &ExamManager::onPrintTasksReceived);
    connect(m_networkManager, &NetworkManager::uploadCompleted,
            this, &ExamManager::onUploadCompleted);
    connect(m_networkManager, &NetworkManager::downloadCompleted,
            this, &ExamManager::onDownloadCompleted);
    connect(m_networkManager, &NetworkManager::networkError,
            this, &ExamManager::onNetworkError);
    
    // 连接扫描管理器信号
    connect(m_scanManager, &ScanManager::scanError,
            this, &ExamManager::onScanError);
    
    // 连接打印管理器信号
    connect(m_printManager, &PrintManager::printError,
            this, &ExamManager::onPrintError);
    
    // 启动定时器
    m_pollTimer->start();
    
    // 初始化数据
    refreshExamTypes();
}

void ExamManager::refreshExamTypes()
{
    if (m_networkManager) {
        m_networkManager->requestExamTypes();
    }
}

QStringList ExamManager::getExamTypes() const
{
    return m_examTypes;
}

void ExamManager::selectExamType(const QString &examType)
{
    m_currentExamType = examType;
    refreshClassInfo(examType);
}

void ExamManager::refreshClassInfo(const QString &examType)
{
    if (m_networkManager) {
        m_networkManager->requestClassInfo(examType);
    }
}

QJsonArray ExamManager::getClassesForExam(const QString &examType) const
{
    return m_classInfo.value(examType, QJsonArray());
}

void ExamManager::refreshScanTasks()
{
    if (m_networkManager) {
        m_networkManager->requestScanTasks();
    }
}

void ExamManager::refreshPrintTasks()
{
    if (m_networkManager) {
        m_networkManager->requestPrintTasks();
    }
}

void ExamManager::startScanTask(const QString &examType, const QString &className, 
                               const QString &subject, int pageCount)
{
    if (!m_scanManager) {
        qDebug() << "Scan manager not initialized";
        return;
    }
    
    m_currentScanTask = QString("%1_%2_%3").arg(examType).arg(className).arg(subject);
    
    // 开始批量扫描
    if (m_scanManager->startScan("default-scanner", "output.pdf")) {
        updateTaskStatus(m_currentScanTask, "扫描中");
        qDebug() << "Started batch scan for" << m_currentScanTask;
    } else {
        updateTaskStatus(m_currentScanTask, "扫描失败");
        qDebug() << "Failed to start batch scan for" << m_currentScanTask;
    }
}

void ExamManager::startPrintTask(const QString &taskId, const QString &filePath)
{
    if (!m_printManager) {
        qDebug() << "Print manager not initialized";
        return;
    }
    
    // 开始打印
    if (m_printManager->printFile("default-printer", filePath, "Task_" + taskId)) {
        updateTaskStatus(taskId, "打印中");
        qDebug() << "Started print task" << taskId;
    } else {
        updateTaskStatus(taskId, "打印失败");
        qDebug() << "Failed to start print task" << taskId;
    }
}

void ExamManager::onExamTypesReceived(const QJsonArray &examTypes)
{
    m_examTypes.clear();
    for (const QJsonValue &value : examTypes) {
        if (value.isString()) {
            m_examTypes.append(value.toString());
        }
    }
    
    emit examTypesUpdated(m_examTypes);
    qDebug() << "Received" << m_examTypes.size() << "exam types";
}

void ExamManager::onClassInfoReceived(const QString &examType, const QJsonArray &classes)
{
    m_classInfo[examType] = classes;
    emit classInfoUpdated(examType, classes);
    qDebug() << "Received class info for" << examType << ":" << classes.size() << "classes";
}

void ExamManager::onScanTasksReceived(const QJsonArray &tasks)
{
    m_scanTasks = tasks;
    emit scanTasksUpdated(tasks);
    qDebug() << "Received" << tasks.size() << "scan tasks";
}

void ExamManager::onPrintTasksReceived(const QJsonArray &tasks)
{
    m_printTasks = tasks;
    emit printTasksUpdated(tasks);
    qDebug() << "Received" << tasks.size() << "print tasks";
}

void ExamManager::onUploadCompleted(const QString &taskId, bool success)
{
    if (success) {
        updateTaskStatus(taskId, "已上传");
        moveTaskFromScanToPrint(taskId);
        qDebug() << "Upload completed for task" << taskId;
    } else {
        updateTaskStatus(taskId, "上传失败");
        qDebug() << "Upload failed for task" << taskId;
    }
}



void ExamManager::onDownloadCompleted(const QString &taskId, const QString &filePath, bool success)
{
    if (success) {
        updateTaskStatus(taskId, "可打印");
        qDebug() << "Download completed for task" << taskId << ":" << filePath;
    } else {
        updateTaskStatus(taskId, "下载失败");
        qDebug() << "Download failed for task" << taskId;
    }
}

void ExamManager::onPrintCompleted(const QString &deviceName, const QString &jobName, int jobId)
{
    updateTaskStatus(jobName, "打印完成");
    qDebug() << "Print completed:" << deviceName << jobName << "Job ID:" << jobId;
}

void ExamManager::onNetworkError(const QString &error)
{
    qDebug() << "Network error:" << error;
}

void ExamManager::onScanError(const QString &error)
{
    if (!m_currentScanTask.isEmpty()) {
        updateTaskStatus(m_currentScanTask, "扫描失败");
    }
    qDebug() << "Scan error:" << error;
}

void ExamManager::onPrintError(const QString &error)
{
    qDebug() << "Print error:" << error;
}

void ExamManager::updateTaskStatus(const QString &taskId, const QString &status)
{
    emit taskStatusChanged(taskId, status);
}

void ExamManager::moveTaskFromScanToPrint(const QString &taskId)
{
    // 从扫描任务列表中移除，添加到打印任务列表
    // 这里需要根据实际的数据结构来实现
    qDebug() << "Moving task" << taskId << "from scan to print";
}

void ExamManager::checkPrintTaskStatus()
{
    // 检查打印任务状态，如果处理完成则下载文件
    for (const QJsonValue &value : m_printTasks) {
        if (value.isObject()) {
            QJsonObject task = value.toObject();
            QString status = task["status"].toString();
            QString taskId = task["id"].toString();
            
            if (status == "completed" && !task["fileUrl"].toString().isEmpty()) {
                // 下载处理完成的文件
                m_networkManager->downloadPrintFile(taskId, task["fileUrl"].toString());
            }
        }
    }
}

void ExamManager::onBatchScanCompleted(const QStringList &filePaths)
{
    qDebug() << "批量扫描完成，文件数量:" << filePaths.size();
    
    // 更新当前扫描任务状态
    if (!m_currentScanTask.isEmpty()) {
        updateTaskStatus(m_currentScanTask, "扫描完成");
        
        // 上传扫描文件
        if (m_networkManager) {
            m_networkManager->uploadScanData("考试类型", "班级", "学科", filePaths);
        }
        
        qDebug() << "批量扫描任务完成:" << m_currentScanTask 
                 << "文件数量:" << filePaths.size();
    }
} 