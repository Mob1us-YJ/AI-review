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
    m_deviceManager(new DeviceManager(this)),  // 新增：设备管理器
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
    
    // 新增：初始化设备管理器
    initializeDeviceManager();
    
    // 添加示例任务（保持原有UI）
    addSampleTasks();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addSampleTasks()
{
    qDebug() << "=== 开始添加示例任务 ===";
    
    // 保持原有的示例任务
    Form *form = new Form("1","高一（13）","数学","A3双面","待扫描","50","2025/8/2 8:07:25","扫描");
    qDebug() << "创建扫描任务Form:" << form;
    ui->verticalLayout->addWidget(form);
    qDebug() << "添加到verticalLayout";
    
    Form *form_1 = new Form("1","高一（12）","数学","A3双面","待扫描","50","2025/8/2 8:07:25","打印");
    qDebug() << "创建打印任务Form_1:" << form_1;
    ui->verticalLayout_2->addWidget(form_1);
    qDebug() << "添加到verticalLayout_2";
    
    Form *form_2 = new Form("2","高一（12）","语文","A3双面","待扫描","50","2025/8/2 8:07:25","打印");
    qDebug() << "创建打印任务Form_2:" << form_2;
    ui->verticalLayout_4->addWidget(form_2);
    qDebug() << "添加到verticalLayout_4";
    
    Form *form_3 = new Form("3","高一（12）","英语","A3双面","待扫描","50","2025/8/2 8:07:25","打印");
    qDebug() << "创建打印任务Form_3:" << form_3;
    ui->verticalLayout_5->addWidget(form_3);
    qDebug() << "添加到verticalLayout_5";
    
    Form *form_4 = new Form("4","高一（12）","物理","A3双面","待扫描","50","2025/8/2 8:07:25","打印");
    qDebug() << "创建打印任务Form_4:" << form_4;
    ui->verticalLayout_6->addWidget(form_4);
    qDebug() << "添加到verticalLayout_6";
    
    Form *form_5 = new Form("5","高一（12）","数学","A3双面","待扫描","50","2025/8/2 8:07:25","打印");
    qDebug() << "创建打印任务Form_5:" << form_5;
    ui->verticalLayout_7->addWidget(form_5);
    qDebug() << "添加到verticalLayout_7";
    
    Form *form_6 = new Form("6","高一（12）","数学","A3双面","待扫描","50","2025/8/2 8:07:25","打印");
    qDebug() << "创建打印任务Form_6:" << form_6;
    ui->verticalLayout_8->addWidget(form_6);
    qDebug() << "添加到verticalLayout_8";
    
    qDebug() << "=== 所有Form组件已添加到布局 ===";
    
    // 连接Form按钮信号
    connect(form, &Form::scanButtonClicked, this, &MainWindow::onFormScanButtonClicked);
    connect(form_1, &Form::printButtonClicked, this, &MainWindow::onFormPrintButtonClicked);
    connect(form_2, &Form::printButtonClicked, this, &MainWindow::onFormPrintButtonClicked);
    connect(form_3, &Form::printButtonClicked, this, &MainWindow::onFormPrintButtonClicked);
    connect(form_4, &Form::printButtonClicked, this, &MainWindow::onFormPrintButtonClicked);
    connect(form_5, &Form::printButtonClicked, this, &MainWindow::onFormPrintButtonClicked);
    connect(form_6, &Form::printButtonClicked, this, &MainWindow::onFormPrintButtonClicked);
    
    qDebug() << "=== 信号连接完成 ===";
    
    // 启用模拟模式
    qDebug() << "\n=== 启用模拟模式 ===";
    m_scanManager->enableSimulationMode(true);
    m_printManager->enableSimulationMode(true);
    m_networkManager->enableSimulationMode(true);
    
    // 添加测试功能
    qDebug() << "=== AI阅卷系统功能测试 ===";
    
    // 测试扫描管理器
    qDebug() << "\n--- 扫描功能测试 ---";
    qDebug() << "扫描管理器已初始化";
    
    // 测试打印管理器
    qDebug() << "\n--- 打印功能测试 ---";
    qDebug() << "打印管理器已初始化";
    
    // 测试网络管理器
    qDebug() << "\n--- 网络功能测试 ---";
    m_networkManager->setServerUrl("http://localhost:8080"); // 测试URL
    m_networkManager->setApiKey("test-api-key");
    
    // 测试扫描设置
    qDebug() << "\n--- 扫描设置测试 ---";
    m_scanManager->setScanSettings("default-scanner", 300, "jpeg", "Color");
    qDebug() << "扫描设置已更新";
    
    // 测试打印设置
    qDebug() << "\n--- 打印设置测试 ---";
    m_printManager->setPrintSettings("default-printer", 1, "A4", "two-sided-long-edge");
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
    
    // 设备管理相关
    connect(m_deviceManager, &DeviceManager::deviceDiscovered,
            this, &MainWindow::onDeviceDiscovered);
    connect(m_deviceManager, &DeviceManager::deviceSelected,
            this, &MainWindow::onDeviceSelected);
    connect(m_deviceManager, &DeviceManager::deviceStatusChanged,
            this, &MainWindow::onDeviceStatusChanged);
    connect(m_deviceManager, &DeviceManager::deviceError,
            this, &MainWindow::onDeviceError);
    
    // 扫描相关 - 使用设备名称
    connect(m_scanManager, &ScanManager::scanStarted,
            [this](const QString &deviceName) {
                qDebug() << "扫描开始，设备:" << deviceName;
            });
    connect(m_scanManager, &ScanManager::scanProgress,
            [this](const QString &deviceName, int current, int total) {
                qDebug() << "扫描进度，设备:" << deviceName << current << "/" << total;
            });
    connect(m_scanManager, &ScanManager::scanCompleted,
            [this](const QString &deviceName, const QString &filePath) {
                qDebug() << "扫描完成，设备:" << deviceName << "文件:" << filePath;
                // 自动上传扫描文件
                m_scanManager->uploadFile(deviceName, filePath, "/exam/");
            });
    connect(m_scanManager, &ScanManager::scanError,
            [this](const QString &deviceName, const QString &error) {
                qDebug() << "扫描错误，设备:" << deviceName << "错误:" << error;
            });
    
    // 打印相关 - 使用设备名称
    connect(m_printManager, &PrintManager::printStarted,
            [this](const QString &deviceName, const QString &jobName) {
                qDebug() << "打印开始，设备:" << deviceName << "任务:" << jobName;
            });
    connect(m_printManager, &PrintManager::printCompleted,
            [this](const QString &deviceName, const QString &jobName, int jobId) {
                qDebug() << "打印完成，设备:" << deviceName << "任务:" << jobName << "ID:" << jobId;
            });
    connect(m_printManager, &PrintManager::printError,
            [this](const QString &deviceName, const QString &error) {
                qDebug() << "打印错误，设备:" << deviceName << "错误:" << error;
            });
    
    // 上传相关
    connect(m_scanManager, &ScanManager::uploadStarted,
            [this](const QString &deviceName, const QString &filePath) {
                qDebug() << "上传开始，设备:" << deviceName << "文件:" << filePath;
            });
    connect(m_scanManager, &ScanManager::uploadCompleted,
            [this](const QString &deviceName, const QString &fileUrl) {
                qDebug() << "上传完成，设备:" << deviceName << "URL:" << fileUrl;
            });
    connect(m_scanManager, &ScanManager::uploadError,
            [this](const QString &deviceName, const QString &error) {
                qDebug() << "上传错误，设备:" << deviceName << "错误:" << error;
            });
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
    
    // 获取当前选择的设备
    QString currentDevice = m_deviceManager->getCurrentDevice();
    if (currentDevice.isEmpty()) {
        // 如果没有选择设备，选择第一个多功能一体机
        QStringList multifunctionDevices = m_deviceManager->getMultifunctionDevices();
        if (!multifunctionDevices.isEmpty()) {
            currentDevice = multifunctionDevices.first();
            m_deviceManager->selectDevice(currentDevice);
        }
    }
    
    if (!currentDevice.isEmpty()) {
        // 调用设备扫描功能
        onDeviceScanRequested(currentDevice, taskId, className, subject);
    } else {
        qDebug() << "✗ 没有可用的扫描设备";
    }
}

void MainWindow::onFormPrintButtonClicked(const QString &taskId, const QString &className, const QString &subject)
{
    qDebug() << "=== 界面打印按钮被点击 ===";
    qDebug() << "任务ID:" << taskId;
    qDebug() << "班级:" << className;
    qDebug() << "学科:" << subject;
    
    // 获取当前选择的设备
    QString currentDevice = m_deviceManager->getCurrentDevice();
    if (currentDevice.isEmpty()) {
        // 如果没有选择设备，选择第一个多功能一体机
        QStringList multifunctionDevices = m_deviceManager->getMultifunctionDevices();
        if (!multifunctionDevices.isEmpty()) {
            currentDevice = multifunctionDevices.first();
            m_deviceManager->selectDevice(currentDevice);
        }
    }
    
    if (!currentDevice.isEmpty()) {
        // 调用设备打印功能
        onDevicePrintRequested(currentDevice, taskId, className, subject);
    } else {
        qDebug() << "✗ 没有可用的打印设备";
    }
}

// 新增：设备扫描请求处理
void MainWindow::onDeviceScanRequested(const QString &deviceName, const QString &taskId, 
                                      const QString &className, const QString &subject)
{
    qDebug() << "=== 设备扫描请求 ===";
    qDebug() << "设备:" << deviceName;
    qDebug() << "任务ID:" << taskId;
    qDebug() << "班级:" << className;
    qDebug() << "学科:" << subject;
    
    // 设置扫描参数
    m_scanManager->setScanSettings(deviceName, 300, "jpeg", "Color", true); // 双面扫描
    
    // 开始批量扫描
    bool success = m_scanManager->startBatchScan(deviceName, "2025年上第一次月考", className, subject, 6);
    if (success) {
        qDebug() << "✓ 批量扫描启动成功";
    } else {
        qDebug() << "✗ 批量扫描启动失败";
    }
}

// 新增：设备打印请求处理
void MainWindow::onDevicePrintRequested(const QString &deviceName, const QString &taskId, 
                                       const QString &className, const QString &subject)
{
    qDebug() << "=== 设备打印请求 ===";
    qDebug() << "设备:" << deviceName;
    qDebug() << "任务ID:" << taskId;
    qDebug() << "班级:" << className;
    qDebug() << "学科:" << subject;
    
    // 设置打印参数
    m_printManager->setPrintSettings(deviceName, 1, "A3", "two-sided-long-edge");
    
    // 生成打印文件名
    QString fileName = QString("print_task_%1_%2_%3.pdf").arg(taskId).arg(className).arg(subject);
    
    // 开始打印
    bool success = m_printManager->printFile(deviceName, fileName, fileName);
    if (success) {
        qDebug() << "✓ 打印任务启动成功";
    } else {
        qDebug() << "✗ 打印任务启动失败";
    }
}

// 新增：设备管理相关方法实现
void MainWindow::initializeDeviceManager()
{
    qDebug() << "\n=== 初始化设备管理器 ===";
    
    // 发现设备
    QStringList allDevices = m_deviceManager->discoverDevices();
    qDebug() << "发现设备总数:" << allDevices.size();
    
    // 显示设备信息
    displayDeviceInfo();
    
    // 测试多功能一体机
    testMultifunctionDevice();
}

void MainWindow::displayDeviceInfo()
{
    qDebug() << "\n--- 设备信息显示 ---";
    
    QStringList allDevices = m_deviceManager->discoverDevices();
    for (const QString &device : allDevices) {
        QString deviceType = m_deviceManager->getDeviceType(device);
        QString deviceModel = m_deviceManager->getDeviceModel(device);
        QString capabilities = m_deviceManager->getDeviceCapabilities(device);
        QString status = m_deviceManager->getDeviceStatus(device);
        
        qDebug() << "设备:" << device;
        qDebug() << "  类型:" << deviceType;
        qDebug() << "  型号:" << deviceModel;
        qDebug() << "  功能:" << capabilities;
        qDebug() << "  状态:" << status;
        qDebug() << "  是否多功能:" << (m_deviceManager->isMultifunctionDevice(device) ? "是" : "否");
        qDebug() << "  可扫描:" << (m_deviceManager->canScan(device) ? "是" : "否");
        qDebug() << "  可打印:" << (m_deviceManager->canPrint(device) ? "是" : "否");
        qDebug() << "";
    }
}

void MainWindow::testMultifunctionDevice()
{
    qDebug() << "\n--- 多功能一体机测试 ---";
    
    QStringList multifunctionDevices = m_deviceManager->getMultifunctionDevices();
    qDebug() << "多功能一体机数量:" << multifunctionDevices.size();
    
    for (const QString &device : multifunctionDevices) {
        qDebug() << "测试多功能一体机:" << device;
        
        // 选择设备
        if (m_deviceManager->selectDevice(device)) {
            qDebug() << "✓ 设备选择成功";
            
            // 获取设备配置
            QMap<QString, QString> config = m_deviceManager->getDeviceConfiguration(device);
            qDebug() << "设备配置:" << config;
            
            // 测试扫描功能
            if (m_deviceManager->canScan(device)) {
                qDebug() << "✓ 支持扫描功能";
                // 这里可以调用扫描管理器
            }
            
            // 测试打印功能
            if (m_deviceManager->canPrint(device)) {
                qDebug() << "✓ 支持打印功能";
                // 这里可以调用打印管理器
            }
        } else {
            qDebug() << "✗ 设备选择失败";
        }
    }
}

void MainWindow::onDeviceDiscovered(const QString &deviceName, const QString &deviceType)
{
    qDebug() << "发现新设备:" << deviceName << "类型:" << deviceType;
}

void MainWindow::onDeviceSelected(const QString &deviceName)
{
    qDebug() << "选择设备:" << deviceName;
}

void MainWindow::onDeviceStatusChanged(const QString &deviceName, const QString &status)
{
    qDebug() << "设备状态变化:" << deviceName << "状态:" << status;
}

void MainWindow::onDeviceError(const QString &deviceName, const QString &error)
{
    qDebug() << "设备错误:" << deviceName << "错误:" << error;
}
