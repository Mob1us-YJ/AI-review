#include "devicemanager.h"
#include <QProcess>
#include <QDebug>
#include <QRegularExpression>

DeviceManager::DeviceManager(QObject *parent)
    : QObject(parent)
{
    initializeDeviceDatabase();
}

DeviceManager::~DeviceManager()
{
}

void DeviceManager::initializeDeviceDatabase()
{
    qDebug() << "初始化设备数据库...";
    
    // 检测Brother MFC-J3940DW多功能一体机
    detectBrotherMFCJ3940DW();
}

void DeviceManager::detectBrotherMFCJ3940DW()
{
    // 检查扫描设备
    QProcess scanProcess;
    scanProcess.start("scanimage", QStringList() << "-L");
    scanProcess.waitForFinished();
    
    QString scanOutput = scanProcess.readAllStandardOutput();
    QStringList scanLines = scanOutput.split('\n', QString::SkipEmptyParts);
    
    // 检查打印设备
    QProcess printProcess;
    printProcess.start("lpstat", QStringList() << "-p");
    printProcess.waitForFinished();
    
    QString printOutput = printProcess.readAllStandardOutput();
    QStringList printLines = printOutput.split('\n', QString::SkipEmptyParts);
    
    // 查找Brother MFC-J3940DW设备
    QStringList brotherDevices;
    
    // 从扫描设备中查找
    for (const QString &line : scanLines) {
        if (line.contains("Brother MFC-J3940DW", Qt::CaseInsensitive)) {
            int start = line.indexOf("`") + 1;
            int end = line.indexOf("'", start);
            if (start > 0 && end > start) {
                QString deviceName = line.mid(start, end - start);
                brotherDevices.append(deviceName);
                m_deviceTypes[deviceName] = "Multifunction";
                m_deviceModels[deviceName] = "Brother MFC-J3940DW";
                m_deviceCapabilities[deviceName] = QStringList() << "Scan" << "Print" << "Copy" << "Fax";
                
                qDebug() << "发现多功能一体机:" << deviceName;
                emit deviceDiscovered(deviceName, "Multifunction");
            }
        }
    }
    
    // 从打印设备中查找
    for (const QString &line : printLines) {
        if (line.contains("Brother MFC-J3940DW", Qt::CaseInsensitive)) {
            QStringList parts = line.split(' ');
            if (parts.size() >= 2) {
                QString printerName = parts[1];
                if (!brotherDevices.contains(printerName)) {
                    brotherDevices.append(printerName);
                    m_deviceTypes[printerName] = "Multifunction";
                    m_deviceModels[printerName] = "Brother MFC-J3940DW";
                    m_deviceCapabilities[printerName] = QStringList() << "Scan" << "Print" << "Copy" << "Fax";
                    
                    qDebug() << "发现多功能一体机:" << printerName;
                    emit deviceDiscovered(printerName, "Multifunction");
                }
            }
        }
    }
    
    // 设置默认配置
    for (const QString &device : brotherDevices) {
        QMap<QString, QString> config;
        config["scan_resolution"] = "300";
        config["scan_mode"] = "Color";
        config["scan_format"] = "jpeg";
        config["scan_source"] = "ADF";
        config["print_media"] = "A4";
        config["print_sides"] = "two-sided-long-edge";
        config["print_copies"] = "1";
        m_deviceConfigs[device] = config;
    }
}

QStringList DeviceManager::discoverDevices()
{
    QStringList allDevices;
    
    // 获取扫描设备
    QStringList scanDevices = getScanDevices();
    allDevices.append(scanDevices);
    
    // 获取打印设备
    QStringList printDevices = getPrintDevices();
    allDevices.append(printDevices);
    
    // 去重
    allDevices.removeDuplicates();
    
    return allDevices;
}

QStringList DeviceManager::getMultifunctionDevices()
{
    QStringList multifunctionDevices;
    
    for (auto it = m_deviceTypes.begin(); it != m_deviceTypes.end(); ++it) {
        if (it.value() == "Multifunction") {
            multifunctionDevices.append(it.key());
        }
    }
    
    return multifunctionDevices;
}

QStringList DeviceManager::getScanDevices()
{
    QStringList scanDevices;
    
    QProcess process;
    process.start("scanimage", QStringList() << "-L");
    process.waitForFinished();
    
    QString output = process.readAllStandardOutput();
    QStringList lines = output.split('\n', QString::SkipEmptyParts);
    
    for (const QString &line : lines) {
        if (line.contains("device")) {
            int start = line.indexOf("`") + 1;
            int end = line.indexOf("'", start);
            if (start > 0 && end > start) {
                QString deviceName = line.mid(start, end - start);
                scanDevices.append(deviceName);
                
                // 如果还没有类型信息，设置为扫描设备
                if (!m_deviceTypes.contains(deviceName)) {
                    m_deviceTypes[deviceName] = "Scanner";
                    m_deviceCapabilities[deviceName] = QStringList() << "Scan";
                }
            }
        }
    }
    
    return scanDevices;
}

QStringList DeviceManager::getPrintDevices()
{
    QStringList printDevices;
    
    QProcess process;
    process.start("lpstat", QStringList() << "-p");
    process.waitForFinished();
    
    QString output = process.readAllStandardOutput();
    QStringList lines = output.split('\n', QString::SkipEmptyParts);
    
    for (const QString &line : lines) {
        if (line.startsWith("printer")) {
            QStringList parts = line.split(' ');
            if (parts.size() >= 2) {
                QString printerName = parts[1];
                printDevices.append(printerName);
                
                // 如果还没有类型信息，设置为打印设备
                if (!m_deviceTypes.contains(printerName)) {
                    m_deviceTypes[printerName] = "Printer";
                    m_deviceCapabilities[printerName] = QStringList() << "Print";
                }
            }
        }
    }
    
    return printDevices;
}

QString DeviceManager::getDeviceType(const QString &deviceName)
{
    return m_deviceTypes.value(deviceName, "Unknown");
}

QString DeviceManager::getDeviceModel(const QString &deviceName)
{
    return m_deviceModels.value(deviceName, "Unknown");
}

QString DeviceManager::getDeviceCapabilities(const QString &deviceName)
{
    QStringList capabilities = m_deviceCapabilities.value(deviceName, QStringList());
    return capabilities.join(", ");
}

bool DeviceManager::selectDevice(const QString &deviceName)
{
    if (m_deviceTypes.contains(deviceName)) {
        m_currentDevice = deviceName;
        emit deviceSelected(deviceName);
        qDebug() << "选择设备:" << deviceName << "类型:" << getDeviceType(deviceName);
        return true;
    }
    return false;
}

bool DeviceManager::isDeviceAvailable(const QString &deviceName)
{
    // 检查设备是否在已知设备列表中
    return m_deviceTypes.contains(deviceName);
}

bool DeviceManager::isDeviceBusy(const QString &deviceName)
{
    // 这里可以实现更复杂的设备状态检查
    // 目前简单返回false
    return false;
}

QString DeviceManager::getDeviceStatus(const QString &deviceName)
{
    if (!isDeviceAvailable(deviceName)) {
        return "Not Found";
    }
    
    if (isDeviceBusy(deviceName)) {
        return "Busy";
    }
    
    return "Ready";
}

bool DeviceManager::isMultifunctionDevice(const QString &deviceName)
{
    return getDeviceType(deviceName) == "Multifunction";
}

bool DeviceManager::canScan(const QString &deviceName)
{
    QStringList capabilities = m_deviceCapabilities.value(deviceName, QStringList());
    return capabilities.contains("Scan");
}

bool DeviceManager::canPrint(const QString &deviceName)
{
    QStringList capabilities = m_deviceCapabilities.value(deviceName, QStringList());
    return capabilities.contains("Print");
}

bool DeviceManager::canCopy(const QString &deviceName)
{
    QStringList capabilities = m_deviceCapabilities.value(deviceName, QStringList());
    return capabilities.contains("Copy");
}

bool DeviceManager::canFax(const QString &deviceName)
{
    QStringList capabilities = m_deviceCapabilities.value(deviceName, QStringList());
    return capabilities.contains("Fax");
}

void DeviceManager::setDeviceConfiguration(const QString &deviceName, const QMap<QString, QString> &config)
{
    m_deviceConfigs[deviceName] = config;
    qDebug() << "设置设备配置:" << deviceName << config;
}

QMap<QString, QString> DeviceManager::getDeviceConfiguration(const QString &deviceName)
{
    return m_deviceConfigs.value(deviceName, QMap<QString, QString>());
} 