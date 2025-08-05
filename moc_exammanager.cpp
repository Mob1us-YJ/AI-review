/****************************************************************************
** Meta object code from reading C++ file 'exammanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.15)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "exammanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'exammanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.15. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ExamManager_t {
    QByteArrayData data[30];
    char stringdata0[391];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ExamManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ExamManager_t qt_meta_stringdata_ExamManager = {
    {
QT_MOC_LITERAL(0, 0, 11), // "ExamManager"
QT_MOC_LITERAL(1, 12, 16), // "examTypesUpdated"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 9), // "examTypes"
QT_MOC_LITERAL(4, 40, 16), // "classInfoUpdated"
QT_MOC_LITERAL(5, 57, 8), // "examType"
QT_MOC_LITERAL(6, 66, 7), // "classes"
QT_MOC_LITERAL(7, 74, 16), // "scanTasksUpdated"
QT_MOC_LITERAL(8, 91, 5), // "tasks"
QT_MOC_LITERAL(9, 97, 17), // "printTasksUpdated"
QT_MOC_LITERAL(10, 115, 17), // "taskStatusChanged"
QT_MOC_LITERAL(11, 133, 6), // "taskId"
QT_MOC_LITERAL(12, 140, 6), // "status"
QT_MOC_LITERAL(13, 147, 19), // "onExamTypesReceived"
QT_MOC_LITERAL(14, 167, 19), // "onClassInfoReceived"
QT_MOC_LITERAL(15, 187, 19), // "onScanTasksReceived"
QT_MOC_LITERAL(16, 207, 20), // "onPrintTasksReceived"
QT_MOC_LITERAL(17, 228, 17), // "onUploadCompleted"
QT_MOC_LITERAL(18, 246, 7), // "success"
QT_MOC_LITERAL(19, 254, 20), // "onBatchScanCompleted"
QT_MOC_LITERAL(20, 275, 9), // "filePaths"
QT_MOC_LITERAL(21, 285, 19), // "onDownloadCompleted"
QT_MOC_LITERAL(22, 305, 8), // "filePath"
QT_MOC_LITERAL(23, 314, 16), // "onPrintCompleted"
QT_MOC_LITERAL(24, 331, 7), // "jobName"
QT_MOC_LITERAL(25, 339, 5), // "jobId"
QT_MOC_LITERAL(26, 345, 14), // "onNetworkError"
QT_MOC_LITERAL(27, 360, 5), // "error"
QT_MOC_LITERAL(28, 366, 11), // "onScanError"
QT_MOC_LITERAL(29, 378, 12) // "onPrintError"

    },
    "ExamManager\0examTypesUpdated\0\0examTypes\0"
    "classInfoUpdated\0examType\0classes\0"
    "scanTasksUpdated\0tasks\0printTasksUpdated\0"
    "taskStatusChanged\0taskId\0status\0"
    "onExamTypesReceived\0onClassInfoReceived\0"
    "onScanTasksReceived\0onPrintTasksReceived\0"
    "onUploadCompleted\0success\0"
    "onBatchScanCompleted\0filePaths\0"
    "onDownloadCompleted\0filePath\0"
    "onPrintCompleted\0jobName\0jobId\0"
    "onNetworkError\0error\0onScanError\0"
    "onPrintError"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ExamManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   94,    2, 0x06 /* Public */,
       4,    2,   97,    2, 0x06 /* Public */,
       7,    1,  102,    2, 0x06 /* Public */,
       9,    1,  105,    2, 0x06 /* Public */,
      10,    2,  108,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    1,  113,    2, 0x08 /* Private */,
      14,    2,  116,    2, 0x08 /* Private */,
      15,    1,  121,    2, 0x08 /* Private */,
      16,    1,  124,    2, 0x08 /* Private */,
      17,    2,  127,    2, 0x08 /* Private */,
      19,    1,  132,    2, 0x08 /* Private */,
      21,    3,  135,    2, 0x08 /* Private */,
      23,    2,  142,    2, 0x08 /* Private */,
      26,    1,  147,    2, 0x08 /* Private */,
      28,    1,  150,    2, 0x08 /* Private */,
      29,    1,  153,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QStringList,    3,
    QMetaType::Void, QMetaType::QString, QMetaType::QJsonArray,    5,    6,
    QMetaType::Void, QMetaType::QJsonArray,    8,
    QMetaType::Void, QMetaType::QJsonArray,    8,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   11,   12,

 // slots: parameters
    QMetaType::Void, QMetaType::QJsonArray,    3,
    QMetaType::Void, QMetaType::QString, QMetaType::QJsonArray,    5,    6,
    QMetaType::Void, QMetaType::QJsonArray,    8,
    QMetaType::Void, QMetaType::QJsonArray,    8,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,   11,   18,
    QMetaType::Void, QMetaType::QStringList,   20,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Bool,   11,   22,   18,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   24,   25,
    QMetaType::Void, QMetaType::QString,   27,
    QMetaType::Void, QMetaType::QString,   27,
    QMetaType::Void, QMetaType::QString,   27,

       0        // eod
};

void ExamManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ExamManager *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->examTypesUpdated((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 1: _t->classInfoUpdated((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QJsonArray(*)>(_a[2]))); break;
        case 2: _t->scanTasksUpdated((*reinterpret_cast< const QJsonArray(*)>(_a[1]))); break;
        case 3: _t->printTasksUpdated((*reinterpret_cast< const QJsonArray(*)>(_a[1]))); break;
        case 4: _t->taskStatusChanged((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 5: _t->onExamTypesReceived((*reinterpret_cast< const QJsonArray(*)>(_a[1]))); break;
        case 6: _t->onClassInfoReceived((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QJsonArray(*)>(_a[2]))); break;
        case 7: _t->onScanTasksReceived((*reinterpret_cast< const QJsonArray(*)>(_a[1]))); break;
        case 8: _t->onPrintTasksReceived((*reinterpret_cast< const QJsonArray(*)>(_a[1]))); break;
        case 9: _t->onUploadCompleted((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 10: _t->onBatchScanCompleted((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 11: _t->onDownloadCompleted((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 12: _t->onPrintCompleted((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 13: _t->onNetworkError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 14: _t->onScanError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 15: _t->onPrintError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ExamManager::*)(const QStringList & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ExamManager::examTypesUpdated)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ExamManager::*)(const QString & , const QJsonArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ExamManager::classInfoUpdated)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ExamManager::*)(const QJsonArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ExamManager::scanTasksUpdated)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ExamManager::*)(const QJsonArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ExamManager::printTasksUpdated)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ExamManager::*)(const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ExamManager::taskStatusChanged)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ExamManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ExamManager.data,
    qt_meta_data_ExamManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ExamManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ExamManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ExamManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ExamManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void ExamManager::examTypesUpdated(const QStringList & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ExamManager::classInfoUpdated(const QString & _t1, const QJsonArray & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ExamManager::scanTasksUpdated(const QJsonArray & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ExamManager::printTasksUpdated(const QJsonArray & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ExamManager::taskStatusChanged(const QString & _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
