#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <QObject>
#include <QStringList>
#include <QMap>

class DeviceManager : public QObject
{
    Q_OBJECT

public:
    explicit DeviceManager(QObject *parent = nullptr);
    ~DeviceManager();

    // 设备发现和管理
    QStringList discoverDevices();
    QStringList getMultifunctionDevices();
    QStringList getScanDevices();
    QStringList getPrintDevices();
    
    // 设备信息
    QString getDeviceType(const QString &deviceName);
    QString getDeviceModel(const QString &deviceName);
    QString getDeviceCapabilities(const QString &deviceName);
    
    // 设备选择
    bool selectDevice(const QString &deviceName);
    QString getCurrentDevice() const { return m_currentDevice; }
    
    // 设备状态
    bool isDeviceAvailable(const QString &deviceName);
    bool isDeviceBusy(const QString &deviceName);
    QString getDeviceStatus(const QString &deviceName);
    
    // 多功能一体机特定功能
    bool isMultifunctionDevice(const QString &deviceName);
    bool canScan(const QString &deviceName);
    bool canPrint(const QString &deviceName);
    bool canCopy(const QString &deviceName);
    bool canFax(const QString &deviceName);
    
    // 设备配置
    void setDeviceConfiguration(const QString &deviceName, const QMap<QString, QString> &config);
    QMap<QString, QString> getDeviceConfiguration(const QString &deviceName);
    
    // 新增：设备状态监控
    void startDeviceMonitoring();
    void stopDeviceMonitoring();
    void refreshDeviceStatus();

signals:
    void deviceDiscovered(const QString &deviceName, const QString &deviceType);
    void deviceSelected(const QString &deviceName);
    void deviceStatusChanged(const QString &deviceName, const QString &status);
    void deviceError(const QString &deviceName, const QString &error);
    
    // 新增：设备监控信号
    void deviceConnected(const QString &deviceName);
    void deviceDisconnected(const QString &deviceName);
    void deviceBusy(const QString &deviceName);
    void deviceReady(const QString &deviceName);

private:
    QString m_currentDevice;
    QMap<QString, QString> m_deviceTypes;      // 设备名称 -> 设备类型
    QMap<QString, QString> m_deviceModels;     // 设备名称 -> 设备型号
    QMap<QString, QStringList> m_deviceCapabilities; // 设备名称 -> 功能列表
    QMap<QString, QMap<QString, QString>> m_deviceConfigs; // 设备名称 -> 配置
    
    // 辅助方法
    void initializeDeviceDatabase();
    void detectBrotherMFCJ3940DW();
    QStringList parseDeviceCapabilities(const QString &deviceName);
    
    bool m_simulationMode; // 新增：模拟模式标志
};

#endif // DEVICEMANAGER_H 