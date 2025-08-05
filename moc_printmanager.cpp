/****************************************************************************
** Meta object code from reading C++ file 'printmanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.15)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "printmanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'printmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.15. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PrintManager_t {
    QByteArrayData data[17];
    char stringdata0[221];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PrintManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PrintManager_t qt_meta_stringdata_PrintManager = {
    {
QT_MOC_LITERAL(0, 0, 12), // "PrintManager"
QT_MOC_LITERAL(1, 13, 12), // "printStarted"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 7), // "jobName"
QT_MOC_LITERAL(4, 35, 14), // "printCompleted"
QT_MOC_LITERAL(5, 50, 5), // "jobId"
QT_MOC_LITERAL(6, 56, 10), // "printError"
QT_MOC_LITERAL(7, 67, 5), // "error"
QT_MOC_LITERAL(8, 73, 17), // "printJobsReceived"
QT_MOC_LITERAL(9, 91, 17), // "QMap<int,QString>"
QT_MOC_LITERAL(10, 109, 4), // "jobs"
QT_MOC_LITERAL(11, 114, 22), // "onPrintProcessFinished"
QT_MOC_LITERAL(12, 137, 8), // "exitCode"
QT_MOC_LITERAL(13, 146, 20), // "QProcess::ExitStatus"
QT_MOC_LITERAL(14, 167, 10), // "exitStatus"
QT_MOC_LITERAL(15, 178, 19), // "onPrintProcessError"
QT_MOC_LITERAL(16, 198, 22) // "QProcess::ProcessError"

    },
    "PrintManager\0printStarted\0\0jobName\0"
    "printCompleted\0jobId\0printError\0error\0"
    "printJobsReceived\0QMap<int,QString>\0"
    "jobs\0onPrintProcessFinished\0exitCode\0"
    "QProcess::ExitStatus\0exitStatus\0"
    "onPrintProcessError\0QProcess::ProcessError"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PrintManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       4,    2,   47,    2, 0x06 /* Public */,
       6,    1,   52,    2, 0x06 /* Public */,
       8,    1,   55,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    2,   58,    2, 0x08 /* Private */,
      15,    1,   63,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    3,    5,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, 0x80000000 | 9,   10,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 13,   12,   14,
    QMetaType::Void, 0x80000000 | 16,    7,

       0        // eod
};

void PrintManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PrintManager *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->printStarted((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->printCompleted((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->printError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->printJobsReceived((*reinterpret_cast< const QMap<int,QString>(*)>(_a[1]))); break;
        case 4: _t->onPrintProcessFinished((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QProcess::ExitStatus(*)>(_a[2]))); break;
        case 5: _t->onPrintProcessError((*reinterpret_cast< QProcess::ProcessError(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PrintManager::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PrintManager::printStarted)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PrintManager::*)(const QString & , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PrintManager::printCompleted)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (PrintManager::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PrintManager::printError)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (PrintManager::*)(const QMap<int,QString> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PrintManager::printJobsReceived)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PrintManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_PrintManager.data,
    qt_meta_data_PrintManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PrintManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PrintManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PrintManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int PrintManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void PrintManager::printStarted(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PrintManager::printCompleted(const QString & _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PrintManager::printError(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void PrintManager::printJobsReceived(const QMap<int,QString> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
