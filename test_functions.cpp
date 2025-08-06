#include <QCoreApplication>
#include <QDebug>
#include <QTimer>
#include "scanmanager.h"
#include "printmanager.h"
#include "networkmanager.h"
#include "test_functions.h"
#include "QFile"

class FunctionTester : public QObject
{
    Q_OBJECT

public:
    FunctionTester(QObject *parent = nullptr) : QObject(parent)
    {
        // 初始化管理器
        m_scanManager = new ScanManager(this);
        m_printManager = new PrintManager(this);
        m_networkManager = new NetworkManager(this);
        
        // 设置连接
        setupConnections();
        
        // 启用模拟模式
        m_scanManager->enableSimulationMode(true);
        m_printManager->enableSimulationMode(true);
        m_networkManager->enableSimulationMode(true);
    }

private slots:
    void runTests()
    {
        qDebug() << "\n=== AI阅卷系统功能验证测试 ===";
        qDebug() << "测试时间:" << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        
        // 测试1: 扫描管理器功能
        testScanManager();
        
        // 测试2: 打印管理器功能
        testPrintManager();
        
        // 测试3: 网络管理器功能
        testNetworkManager();
        
        // 测试4: 双面扫描功能
        testDuplexScan();
        
        // 测试5: 批量扫描功能
        testBatchScan();
        
        // 测试6: 网络上传功能
        testUploadFunction();
        
        // 测试7: A3打印功能
        testA3Print();

        // 测试高级打印功能
        testAdvancedPrinting();
        testEquivalentCommands();
        
        qDebug() << "\n=== 所有测试完成 ===";
        QTimer::singleShot(1000, qApp, &QCoreApplication::quit);
    }

private:
    ScanManager *m_scanManager;
    PrintManager *m_printManager;
    NetworkManager *m_networkManager;

    void setupConnections()
    {
        // 扫描相关连接
        connect(m_scanManager, &ScanManager::scanStarted, [this]() {
            qDebug() << "✓ 扫描开始";
        });
        connect(m_scanManager, &ScanManager::scanProgress, [this](int current, int total) {
            qDebug() << "✓ 扫描进度:" << current << "/" << total;
        });
        connect(m_scanManager, &ScanManager::scanCompleted, [this](const QString &filePath) {
            qDebug() << "✓ 扫描完成:" << filePath;
        });
        connect(m_scanManager, &ScanManager::scanError, [this](const QString &error) {
            qDebug() << "✗ 扫描错误:" << error;
        });
        
        // 打印相关连接
        connect(m_printManager, &PrintManager::printStarted, [this](const QString &jobName) {
            qDebug() << "✓ 打印开始:" << jobName;
        });
        connect(m_printManager, &PrintManager::printCompleted, [this](const QString &jobName, int jobId) {
            qDebug() << "✓ 打印完成:" << jobName << "任务ID:" << jobId;
        });
        connect(m_printManager, &PrintManager::printError, [this](const QString &error) {
            qDebug() << "✗ 打印错误:" << error;
        });
        
        // 网络上传相关连接
        connect(m_scanManager, &ScanManager::uploadStarted, [this](const QString &filePath) {
            qDebug() << "✓ 上传开始:" << filePath;
        });
        connect(m_scanManager, &ScanManager::uploadCompleted, [this](const QString &fileUrl) {
            qDebug() << "✓ 上传完成:" << fileUrl;
        });
        connect(m_scanManager, &ScanManager::uploadError, [this](const QString &error) {
            qDebug() << "✗ 上传错误:" << error;
        });
    }

    void testScanManager()
    {
        qDebug() << "\n--- 测试1: 扫描管理器功能 ---";
        
        // 测试获取可用设备
        QStringList devices = m_scanManager->getAvailableDevices();
        qDebug() << "可用扫描设备数量:" << devices.size();
        for (const QString &device : devices) {
            qDebug() << "  -" << device;
        }
        
        // 测试设备选择
        if (!devices.isEmpty()) {
            bool success = m_scanManager->selectDevice(devices.first());
            qDebug() << "设备选择结果:" << (success ? "成功" : "失败");
        }
        
        // 测试扫描设置
        m_scanManager->setScanSettings(300, "jpeg", "Color");
        qDebug() << "扫描设置已更新";
        
        // 测试模拟扫描
        m_scanManager->simulateScan("test-device");
    }

    void testPrintManager()
    {
        qDebug() << "\n--- 测试2: 打印管理器功能 ---";
        
        // 测试获取可用打印机
        QStringList printers = m_printManager->getAvailablePrinters();
        qDebug() << "可用打印机数量:" << printers.size();
        for (const QString &printer : printers) {
            qDebug() << "  -" << printer;
        }
        
        // 测试默认打印机
        QString defaultPrinter = m_printManager->getDefaultPrinter();
        qDebug() << "默认打印机:" << defaultPrinter;
        
        // 测试打印机选择
        if (!printers.isEmpty()) {
            bool success = m_printManager->selectPrinter(printers.first());
            qDebug() << "打印机选择结果:" << (success ? "成功" : "失败");
        }
        
        // 测试打印设置
        m_printManager->setPrintSettings(1, "A4", "two-sided-long-edge");
        qDebug() << "打印设置已更新";
        
        // 测试模拟打印
        m_printManager->simulatePrint("test_document.pdf", "test-printer");
    }

    void testNetworkManager()
    {
        qDebug() << "\n--- 测试3: 网络管理器功能 ---";
        
        // 测试服务器设置
        m_networkManager->setServerUrl("http://117.72.74.246:18000");
        m_networkManager->setApiKey("test-api-key");
        qDebug() << "网络设置已更新";
        
        // 测试模拟网络响应
        m_networkManager->simulateNetworkResponse("exam-types");
        m_networkManager->simulateNetworkResponse("scan-tasks");
        m_networkManager->simulateNetworkResponse("print-tasks");
    }

    void testDuplexScan()
    {
        qDebug() << "\n--- 测试4: 双面扫描功能 ---";
        
        // 测试双面扫描设置
        m_scanManager->setDuplexMode(true);
        qDebug() << "双面扫描模式:" << (m_scanManager->isDuplexMode() ? "启用" : "禁用");
        
        // 测试双面扫描
        m_scanManager->simulateScan("duplex-scanner");
        
        // 恢复单面模式
        m_scanManager->setDuplexMode(false);
        qDebug() << "恢复单面扫描模式";
    }

    void testBatchScan()
    {
        qDebug() << "\n--- 测试5: 批量扫描功能 ---";
        
        // 测试批量扫描设置
        m_scanManager->setBatchMode(true, "scan%d.jpg");
        qDebug() << "批量扫描模式:" << (m_scanManager->isBatchMode() ? "启用" : "禁用");
        
        // 测试批量扫描
        bool success = m_scanManager->startBatchScan("2025年上第一次月考", "高一（13）", "数学", 3);
        qDebug() << "批量扫描启动:" << (success ? "成功" : "失败");
        
        // 恢复单页模式
        m_scanManager->setBatchMode(false);
        qDebug() << "恢复单页扫描模式";
    }

    void testUploadFunction()
    {
        qDebug() << "\n--- 测试6: 网络上传功能 ---";
        
        // 测试上传服务器设置
        m_scanManager->setUploadServer("http://117.72.74.246:18000");
        qDebug() << "上传服务器已设置";
        
        // 测试文件上传（模拟）
        QString testFile = "/tmp/test_scan.jpg";
        m_scanManager->uploadFile(testFile, "/exam/");
    }

    void testA3Print()
    {
        qDebug() << "\n--- 测试7: A3打印功能 ---";
        
        // 测试A3打印设置
        m_printManager->setPrintSettings(1, "A3", "two-sided-long-edge");
        qDebug() << "A3打印设置已更新";
        
        // 测试A3打印
        m_printManager->simulatePrint("A3_test_document.pdf", "Brother_MFC_J3940DW");
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    
    FunctionTester tester;
    QTimer::singleShot(100, &tester, &FunctionTester::runTests);
    
    return app.exec();
}

#include "test_functions.moc" 