/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.15)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.15. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[23];
    char stringdata0[290];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 14), // "onScanProgress"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 7), // "current"
QT_MOC_LITERAL(4, 35, 5), // "total"
QT_MOC_LITERAL(5, 41, 15), // "onScanCompleted"
QT_MOC_LITERAL(6, 57, 8), // "filePath"
QT_MOC_LITERAL(7, 66, 11), // "onScanError"
QT_MOC_LITERAL(8, 78, 5), // "error"
QT_MOC_LITERAL(9, 84, 16), // "onPrintCompleted"
QT_MOC_LITERAL(10, 101, 7), // "jobName"
QT_MOC_LITERAL(11, 109, 5), // "jobId"
QT_MOC_LITERAL(12, 115, 12), // "onPrintError"
QT_MOC_LITERAL(13, 128, 14), // "onNetworkError"
QT_MOC_LITERAL(14, 143, 14), // "onRefreshTimer"
QT_MOC_LITERAL(15, 158, 17), // "onTestScanClicked"
QT_MOC_LITERAL(16, 176, 18), // "onTestPrintClicked"
QT_MOC_LITERAL(17, 195, 20), // "onTestNetworkClicked"
QT_MOC_LITERAL(18, 216, 23), // "onFormScanButtonClicked"
QT_MOC_LITERAL(19, 240, 6), // "taskId"
QT_MOC_LITERAL(20, 247, 9), // "className"
QT_MOC_LITERAL(21, 257, 7), // "subject"
QT_MOC_LITERAL(22, 265, 24) // "onFormPrintButtonClicked"

    },
    "MainWindow\0onScanProgress\0\0current\0"
    "total\0onScanCompleted\0filePath\0"
    "onScanError\0error\0onPrintCompleted\0"
    "jobName\0jobId\0onPrintError\0onNetworkError\0"
    "onRefreshTimer\0onTestScanClicked\0"
    "onTestPrintClicked\0onTestNetworkClicked\0"
    "onFormScanButtonClicked\0taskId\0className\0"
    "subject\0onFormPrintButtonClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   74,    2, 0x08 /* Private */,
       5,    1,   79,    2, 0x08 /* Private */,
       7,    1,   82,    2, 0x08 /* Private */,
       9,    2,   85,    2, 0x08 /* Private */,
      12,    1,   90,    2, 0x08 /* Private */,
      13,    1,   93,    2, 0x08 /* Private */,
      14,    0,   96,    2, 0x08 /* Private */,
      15,    0,   97,    2, 0x08 /* Private */,
      16,    0,   98,    2, 0x08 /* Private */,
      17,    0,   99,    2, 0x08 /* Private */,
      18,    3,  100,    2, 0x08 /* Private */,
      22,    3,  107,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   10,   11,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   19,   20,   21,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   19,   20,   21,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onScanProgress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->onScanCompleted((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->onScanError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->onPrintCompleted((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->onPrintError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->onNetworkError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->onRefreshTimer(); break;
        case 7: _t->onTestScanClicked(); break;
        case 8: _t->onTestPrintClicked(); break;
        case 9: _t->onTestNetworkClicked(); break;
        case 10: _t->onFormScanButtonClicked((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 11: _t->onFormPrintButtonClicked((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
