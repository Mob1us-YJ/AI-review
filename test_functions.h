#ifndef TEST_FUNCTIONS_H
#define TEST_FUNCTIONS_H

#include <QObject>
#include <QDebug>

// 测试函数声明
void testAdvancedPrinting();
void testEquivalentCommands();

// 测试类
class FunctionTester : public QObject
{
    Q_OBJECT

public:
    explicit FunctionTester(QObject *parent = nullptr);
    void runAllTests();

private slots:
    void testBasicFunctions();
    void testDeviceDiscovery();
    void testPrintFunctions();
    void testScanFunctions();
    void testNetworkFunctions();
    void testErrorHandling();
    void testA3Print();
};

#endif // TEST_FUNCTIONS_H 