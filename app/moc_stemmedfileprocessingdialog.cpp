/****************************************************************************
** Meta object code from reading C++ file 'stemmedfileprocessingdialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dialogs/stemmedfileprocessingdialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'stemmedfileprocessingdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_StemmedFileProcessingDialog_t {
    QByteArrayData data[19];
    char stringdata[228];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StemmedFileProcessingDialog_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StemmedFileProcessingDialog_t qt_meta_stringdata_StemmedFileProcessingDialog = {
    {
QT_MOC_LITERAL(0, 0, 27), // "StemmedFileProcessingDialog"
QT_MOC_LITERAL(1, 28, 4), // "read"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 2), // "in"
QT_MOC_LITERAL(4, 37, 7), // "process"
QT_MOC_LITERAL(5, 45, 5), // "write"
QT_MOC_LITERAL(6, 51, 3), // "out"
QT_MOC_LITERAL(7, 55, 18), // "generateHistograms"
QT_MOC_LITERAL(8, 74, 12), // "processFiles"
QT_MOC_LITERAL(9, 87, 6), // "inFile"
QT_MOC_LITERAL(10, 94, 7), // "outFile"
QT_MOC_LITERAL(11, 102, 10), // "onReadDone"
QT_MOC_LITERAL(12, 113, 2), // "ok"
QT_MOC_LITERAL(13, 116, 13), // "onProcessDone"
QT_MOC_LITERAL(14, 130, 11), // "onWriteDone"
QT_MOC_LITERAL(15, 142, 24), // "onGenerateHistogramsDone"
QT_MOC_LITERAL(16, 167, 7), // "message"
QT_MOC_LITERAL(17, 175, 19), // "on_btnClose_clicked"
QT_MOC_LITERAL(18, 195, 32) // "on_btnGenerateHistograms_clicked"

    },
    "StemmedFileProcessingDialog\0read\0\0in\0"
    "process\0write\0out\0generateHistograms\0"
    "processFiles\0inFile\0outFile\0onReadDone\0"
    "ok\0onProcessDone\0onWriteDone\0"
    "onGenerateHistogramsDone\0message\0"
    "on_btnClose_clicked\0"
    "on_btnGenerateHistograms_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StemmedFileProcessingDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,
       4,    0,   72,    2, 0x06 /* Public */,
       5,    1,   73,    2, 0x06 /* Public */,
       7,    1,   76,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    2,   79,    2, 0x0a /* Public */,
      11,    1,   84,    2, 0x0a /* Public */,
      13,    0,   87,    2, 0x0a /* Public */,
      14,    1,   88,    2, 0x0a /* Public */,
      15,    2,   91,    2, 0x0a /* Public */,
      17,    0,   96,    2, 0x08 /* Private */,
      18,    0,   97,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    9,   10,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString,   12,   16,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void StemmedFileProcessingDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        StemmedFileProcessingDialog *_t = static_cast<StemmedFileProcessingDialog *>(_o);
        switch (_id) {
        case 0: _t->read((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->process(); break;
        case 2: _t->write((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->generateHistograms((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->processFiles((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 5: _t->onReadDone((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->onProcessDone(); break;
        case 7: _t->onWriteDone((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->onGenerateHistogramsDone((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 9: _t->on_btnClose_clicked(); break;
        case 10: _t->on_btnGenerateHistograms_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (StemmedFileProcessingDialog::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&StemmedFileProcessingDialog::read)) {
                *result = 0;
            }
        }
        {
            typedef void (StemmedFileProcessingDialog::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&StemmedFileProcessingDialog::process)) {
                *result = 1;
            }
        }
        {
            typedef void (StemmedFileProcessingDialog::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&StemmedFileProcessingDialog::write)) {
                *result = 2;
            }
        }
        {
            typedef void (StemmedFileProcessingDialog::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&StemmedFileProcessingDialog::generateHistograms)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject StemmedFileProcessingDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_StemmedFileProcessingDialog.data,
      qt_meta_data_StemmedFileProcessingDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *StemmedFileProcessingDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StemmedFileProcessingDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_StemmedFileProcessingDialog.stringdata))
        return static_cast<void*>(const_cast< StemmedFileProcessingDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int StemmedFileProcessingDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void StemmedFileProcessingDialog::read(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void StemmedFileProcessingDialog::process()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void StemmedFileProcessingDialog::write(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void StemmedFileProcessingDialog::generateHistograms(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
