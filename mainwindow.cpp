#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_networkManager(new NetworkManager(this)),
    m_scanManager(new ScanManager(this)),
    m_printManager(new PrintManager(this)),
    m_examManager(new ExamManager(this)),
    m_refreshTimer(new QTimer(this))
{
    ui->setupUi(this);
    
    // 初始化管理器
    m_examManager->initialize(m_networkManager, m_scanManager, m_printManager);
    
    // 设置连接
    setupConnections();
    
    // 设置定时器
    m_refreshTimer->setInterval(10000); // 10秒刷新一次
    connect(m_refreshTimer, &QTimer::timeout, this, &MainWindow::onRefreshTimer);
    m_refreshTimer->start();
    
    // 初始化数据
    m_examManager->refreshExamTypes();
    m_examManager->refreshScanTasks();
    m_examManager->refreshPrintTasks();
    
    // 添加示例任务（保持原有UI）
    addSampleTasks();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addSampleTasks()
{
    // 保持原有的示例任务
    Form *form = new Form("1","高一（13）","数学","A3双面","待扫描","50","2025/8/2 8:07:25","扫描");
    ui->verticalLayout->addWidget(form);
    
    Form *form_1 = new Form("1","高一（12）","数学","A3双面","待扫描","50","2025/8/2 8:07:25","打印");
    ui->verticalLayout_2->addWidget(form_1);
    
    Form *form_2 = new Form("2","高一（12）","语文","A3双面","待扫描","50","2025/8/2 8:07:25","打印");
    ui->verticalLayout_4->addWidget(form_2);
    
    Form *form_3 = new Form("3","高一（12）","英语","A3双面","待扫描","50","2025/8/2 8:07:25","打印");
    ui->verticalLayout_5->addWidget(form_3);
    
    Form *form_4 = new Form("4","高一（12）","物理","A3双面","待扫描","50","2025/8/2 8:07:25","打印");
    ui->verticalLayout_6->addWidget(form_4);
    
    Form *form_5 = new Form("5","高一（12）","数学","A3双面","待扫描","50","2025/8/2 8:07:25","打印");
    ui->verticalLayout_7->addWidget(form_5);
    
    Form *form_6 = new Form("6","高一（12）","数学","A3双面","待扫描","50","2025/8/2 8:07:25","打印");
    ui->verticalLayout_8->addWidget(form_6);
    
    // 连接Form按钮信号
    connect(form, &Form::scanButtonClicked, this, &MainWindow::onFormScanButtonClicked);
    connect(form_1, &Form::printButtonClicked, this, &MainWindow::onFormPrintButtonClicked);
    connect(form_2, &Form::printButtonClicked, this, &MainWindow::onFormPrintButtonClicked);
    connect(form_3, &Form::printButtonClicked, this, &MainWindow::onFormPrintButtonClicked);
    connect(form_4, &Form::printButtonClicked, this, &MainWindow::onFormPrintButtonClicked);
    connect(form_5, &Form::printButtonClicked, this, &MainWindow::onFormPrintButtonClicked);
    connect(form_6, &Form::printButtonClicked, this, &MainWindow::onFormPrintButtonClicked);
    
    // 启用模拟模式
    qDebug() << "\n=== 启用模拟模式 ===";
    m_scanManager->enableSimulationMode(true);
    m_printManager->enableSimulationMode(true);
    m_networkManager->enableSimulationMode(true);
    
    // 添加测试功能
    qDebug() << "=== AI阅卷系统功能测试 ===";
    
    // 测试扫描管理器
    qDebug() << "\n--- 扫描功能测试 ---";
    QStringList devices = m_scanManager->getAvailableDevices();
    qDebug() << "可用扫描设备:" << devices;
    
    // 测试打印管理器
    qDebug() << "\n--- 打印功能测试 ---";
    QStringList printers = m_printManager->getAvailablePrinters();
    qDebug() << "可用打印机:" << printers;
    
    QString defaultPrinter = m_printManager->getDefaultPrinter();
    qDebug() << "默认打印机:" << defaultPrinter;
    
    // 测试网络管理器
    qDebug() << "\n--- 网络功能测试 ---";
    m_networkManager->setServerUrl("http://localhost:8080"); // 测试URL
    m_networkManager->setApiKey("test-api-key");
    
    // 测试扫描设置
    qDebug() << "\n--- 扫描设置测试 ---";
    m_scanManager->setScanSettings(300, "A4", "Color");
    qDebug() << "扫描设置已更新";
    
    // 测试打印设置
    qDebug() << "\n--- 打印设置测试 ---";
    m_printManager->setPrintSettings(1, "A4", "Duplex");
    qDebug() << "打印设置已更新";
    
    // 测试考试管理器
    qDebug() << "\n--- 考试管理器测试 ---";
    m_examManager->refreshExamTypes();
    m_examManager->refreshScanTasks();
    m_examManager->refreshPrintTasks();
    
    // 模拟网络响应测试
    qDebug() << "\n--- 模拟网络响应测试 ---";
    m_networkManager->simulateNetworkResponse("exam-types");
    m_networkManager->simulateNetworkResponse("class-info");
    m_networkManager->simulateNetworkResponse("scan-tasks");
    m_networkManager->simulateNetworkResponse("print-tasks");
    
    // 模拟扫描测试
    qDebug() << "\n--- 模拟扫描测试 ---";
    m_scanManager->simulateScan("test-scanner");
    
    // 模拟打印测试
    qDebug() << "\n--- 模拟打印测试 ---";
    m_printManager->simulatePrint("test_document.pdf", "test-printer");
    
    qDebug() << "\n=== 测试完成 ===";
    qDebug() << "注意：";
    qDebug() << "1. 扫描功能已启用模拟模式";
    qDebug() << "2. 打印功能已启用模拟模式";
    qDebug() << "3. 网络功能已启用模拟模式";
    qDebug() << "4. 所有功能接口已准备就绪，可以在主程序中调用";
    qDebug() << "5. 可以点击界面上的按钮来测试扫描和打印功能";
}

void MainWindow::setupConnections()
{
    // 网络相关
    connect(m_networkManager, &NetworkManager::networkError,
            this, &MainWindow::onNetworkError);
    
    // 扫描相关
    connect(m_scanManager, &ScanManager::scanProgress,
            this, &MainWindow::onScanProgress);
    connect(m_scanManager, &ScanManager::scanCompleted,
            this, &MainWindow::onScanCompleted);
    connect(m_scanManager, &ScanManager::scanError,
            this, &MainWindow::onScanError);
    
    // 打印相关
    connect(m_printManager, &PrintManager::printCompleted,
            this, &MainWindow::onPrintCompleted);
    connect(m_printManager, &PrintManager::printError,
            this, &MainWindow::onPrintError);
}

void MainWindow::onScanProgress(int current, int total)
{
    qDebug() << "扫描进度:" << current << "/" << total;
}

void MainWindow::onScanCompleted(const QString &filePath)
{
    qDebug() << "扫描完成:" << filePath;
}

void MainWindow::onScanError(const QString &error)
{
    qDebug() << "扫描错误:" << error;
}

void MainWindow::onPrintCompleted(const QString &jobName, int jobId)
{
    qDebug() << "打印完成:" << jobName << "任务ID:" << jobId;
}

void MainWindow::onPrintError(const QString &error)
{
    qDebug() << "打印错误:" << error;
}

void MainWindow::onNetworkError(const QString &error)
{
    qDebug() << "网络错误:" << error;
}

void MainWindow::onRefreshTimer()
{
    // 定时刷新任务状态
    m_examManager->refreshScanTasks();
    m_examManager->refreshPrintTasks();
}

void MainWindow::onTestScanClicked()
{
    qDebug() << "=== 手动测试扫描功能 ===";
    m_scanManager->simulateScan("manual-test-scanner");
}

void MainWindow::onTestPrintClicked()
{
    qDebug() << "=== 手动测试打印功能 ===";
    m_printManager->simulatePrint("manual_test_document.pdf", "manual-test-printer");
}

void MainWindow::onTestNetworkClicked()
{
    qDebug() << "=== 手动测试网络功能 ===";
    m_networkManager->simulateNetworkResponse("manual-exam-types");
    m_networkManager->simulateNetworkResponse("manual-scan-tasks");
    m_networkManager->simulateNetworkResponse("manual-print-tasks");
}

void MainWindow::onFormScanButtonClicked(const QString &taskId, const QString &className, const QString &subject)
{
    qDebug() << "=== 界面扫描按钮被点击 ===";
    qDebug() << "任务ID:" << taskId;
    qDebug() << "班级:" << className;
    qDebug() << "学科:" << subject;
    
    // 调用模拟扫描功能
    m_scanManager->simulateScan(QString("scanner-for-%1").arg(taskId));
}

void MainWindow::onFormPrintButtonClicked(const QString &taskId, const QString &className, const QString &subject)
{
    qDebug() << "=== 界面打印按钮被点击 ===";
    qDebug() << "任务ID:" << taskId;
    qDebug() << "班级:" << className;
    qDebug() << "学科:" << subject;
    
    // 调用模拟打印功能
    QString fileName = QString("print_task_%1_%2_%3.pdf").arg(taskId).arg(className).arg(subject);
    m_printManager->simulatePrint(fileName, QString("printer-for-%1").arg(taskId));
}
