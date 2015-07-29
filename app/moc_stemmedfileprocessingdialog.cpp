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
    QByteArrayData data[15];
    char stringdata[143];
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
QT_MOC_LITERAL(7, 55, 12), // "processFiles"
QT_MOC_LITERAL(8, 68, 6), // "inFile"
QT_MOC_LITERAL(9, 75, 7), // "outFile"
QT_MOC_LITERAL(10, 83, 10), // "onReadDone"
QT_MOC_LITERAL(11, 94, 2), // "ok"
QT_MOC_LITERAL(12, 97, 13), // "onProcessDone"
QT_MOC_LITERAL(13, 111, 11), // "onWriteDone"
QT_MOC_LITERAL(14, 123, 19) // "on_btnClose_clicked"

    },
    "StemmedFileProcessingDialog\0read\0\0in\0"
    "process\0write\0out\0processFiles\0inFile\0"
    "outFile\0onReadDone\0ok\0onProcessDone\0"
    "onWriteDone\0on_btnClose_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StemmedFileProcessingDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       4,    0,   57,    2, 0x06 /* Public */,
       5,    1,   58,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    2,   61,    2, 0x0a /* Public */,
      10,    1,   66,    2, 0x0a /* Public */,
      12,    0,   69,    2, 0x0a /* Public */,
      13,    1,   70,    2, 0x0a /* Public */,
      14,    0,   73,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    8,    9,
    QMetaType::Void, QMetaType::Bool,   11,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   11,
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
        case 3: _t->processFiles((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 4: _t->onReadDone((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->onProcessDone(); break;
        case 6: _t->onWriteDone((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->on_btnClose_clicked(); break;
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
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
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
QT_END_MOC_NAMESPACE
