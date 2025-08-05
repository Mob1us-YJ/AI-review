#include <QCoreApplication>
#include <QDebug>
#include <QTimer>
#include "networkmanager.h"
#include "scanmanager.h"
#include "printmanager.h"
#include "exammanager.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    
    qDebug() << "=== AI阅卷系统功能测试 ===";
    
    // 创建管理器
    NetworkManager networkManager;
    ScanManager scanManager;
    PrintManager printManager;
    ExamManager examManager;
    
    // 初始化考试管理器
    examManager.initialize(&networkManager, &scanManager, &printManager);
    
    // 测试扫描管理器
    qDebug() << "\n--- 扫描功能测试 ---";
    QStringList devices = scanManager.getAvailableDevices();
    qDebug() << "可用扫描设备:" << devices;
    
    // 测试打印管理器
    qDebug() << "\n--- 打印功能测试 ---";
    QStringList printers = printManager.getAvailablePrinters();
    qDebug() << "可用打印机:" << printers;
    
    QString defaultPrinter = printManager.getDefaultPrinter();
    qDebug() << "默认打印机:" << defaultPrinter;
    
    // 测试网络管理器
    qDebug() << "\n--- 网络功能测试 ---";
    networkManager.setServerUrl("http://localhost:8080"); // 测试URL
    networkManager.setApiKey("test-api-key");
    
    // 连接信号
    QObject::connect(&scanManager, &ScanManager::scanProgress,
                    [](int current, int total) {
                        qDebug() << "扫描进度:" << current << "/" << total;
                    });
    
    QObject::connect(&scanManager, &ScanManager::scanCompleted,
                    [](const QString &filePath) {
                        qDebug() << "扫描完成:" << filePath;
                    });
    
    QObject::connect(&scanManager, &ScanManager::scanError,
                    [](const QString &error) {
                        qDebug() << "扫描错误:" << error;
                    });
    
    QObject::connect(&printManager, &PrintManager::printCompleted,
                    [](const QString &jobName, int jobId) {
                        qDebug() << "打印完成:" << jobName << "任务ID:" << jobId;
                    });
    
    QObject::connect(&printManager, &PrintManager::printError,
                    [](const QString &error) {
                        qDebug() << "打印错误:" << error;
                    });
    
    QObject::connect(&networkManager, &NetworkManager::networkError,
                    [](const QString &error) {
                        qDebug() << "网络错误:" << error;
                    });
    
    // 测试扫描设置
    qDebug() << "\n--- 扫描设置测试 ---";
    scanManager.setScanSettings(300, "A4", "Color");
    qDebug() << "扫描设置已更新";
    
    // 测试打印设置
    qDebug() << "\n--- 打印设置测试 ---";
    printManager.setPrintSettings(1, "A4", "Duplex");
    qDebug() << "打印设置已更新";
    
    // 测试考试管理器
    qDebug() << "\n--- 考试管理器测试 ---";
    examManager.refreshExamTypes();
    examManager.refreshScanTasks();
    examManager.refreshPrintTasks();
    
    qDebug() << "\n=== 测试完成 ===";
    qDebug() << "注意：";
    qDebug() << "1. 扫描功能需要连接扫描仪";
    qDebug() << "2. 打印功能需要配置打印机";
    qDebug() << "3. 网络功能需要有效的服务器地址";
    qDebug() << "4. 所有功能接口已准备就绪，可以在主程序中调用";
    
    return 0;
} 