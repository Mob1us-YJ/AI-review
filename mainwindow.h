#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QTimer>
#include "form.h"
#include "networkmanager.h"
#include "scanmanager.h"
#include "printmanager.h"
#include "exammanager.h"
#include "devicemanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // 扫描相关
    void onScanProgress(int current, int total);
    void onScanCompleted(const QString &filePath);
    void onScanError(const QString &error);
    
    // 打印相关
    void onPrintCompleted(const QString &jobName, int jobId);
    void onPrintError(const QString &error);
    
    // 网络相关
    void onNetworkError(const QString &error);
    
    // 定时器
    void onRefreshTimer();
    
    // 测试功能
    void onTestScanClicked();
    void onTestPrintClicked();
    void onTestNetworkClicked();
    
    // 新增：设备管理功能
    void onDeviceDiscovered(const QString &deviceName, const QString &deviceType);
    void onDeviceSelected(const QString &deviceName);
    void onDeviceStatusChanged(const QString &deviceName, const QString &status);
    void onDeviceError(const QString &deviceName, const QString &error);
    
    // Form按钮点击处理
    void onFormScanButtonClicked(const QString &taskId, const QString &className, const QString &subject);
    void onFormPrintButtonClicked(const QString &taskId, const QString &className, const QString &subject);

private:
    Ui::MainWindow *ui;
    
    // 管理器
    NetworkManager *m_networkManager;
    ScanManager *m_scanManager;
    PrintManager *m_printManager;
    ExamManager *m_examManager;
    DeviceManager *m_deviceManager;  // 设备管理器
    
    // 定时器
    QTimer *m_refreshTimer;
    
    // 辅助方法
    void setupConnections();
    void addSampleTasks();
    
    // 设备管理辅助方法
    void initializeDeviceManager();
    void displayDeviceInfo();
    void testMultifunctionDevice();
    
    // 新增：简化后的功能调用方法
    void onDeviceScanRequested(const QString &deviceName, const QString &taskId, 
                              const QString &className, const QString &subject);
    void onDevicePrintRequested(const QString &deviceName, const QString &taskId, 
                               const QString &className, const QString &subject);
};

#endif // MAINWINDOW_H
