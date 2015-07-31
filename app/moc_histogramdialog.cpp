/****************************************************************************
** Meta object code from reading C++ file 'histogramdialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dialogs/histogramdialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'histogramdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_HistogramDialog_t {
    QByteArrayData data[21];
    char stringdata[263];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HistogramDialog_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HistogramDialog_t qt_meta_stringdata_HistogramDialog = {
    {
QT_MOC_LITERAL(0, 0, 15), // "HistogramDialog"
QT_MOC_LITERAL(1, 16, 4), // "read"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 8), // "fileName"
QT_MOC_LITERAL(4, 31, 14), // "readHistograms"
QT_MOC_LITERAL(5, 46, 6), // "coords"
QT_MOC_LITERAL(6, 53, 4), // "dims"
QT_MOC_LITERAL(7, 58, 21), // "requestHistogramsData"
QT_MOC_LITERAL(8, 80, 5), // "write"
QT_MOC_LITERAL(9, 86, 12), // "processTfidf"
QT_MOC_LITERAL(10, 99, 10), // "onReadDone"
QT_MOC_LITERAL(11, 110, 2), // "ok"
QT_MOC_LITERAL(12, 113, 7), // "message"
QT_MOC_LITERAL(13, 121, 11), // "onWriteDone"
QT_MOC_LITERAL(14, 133, 20), // "onReadHistogramsData"
QT_MOC_LITERAL(15, 154, 18), // "readHistogramsData"
QT_MOC_LITERAL(16, 173, 16), // "onHistogramsData"
QT_MOC_LITERAL(17, 190, 22), // "HistogramsDrawingData*"
QT_MOC_LITERAL(18, 213, 10), // "histograms"
QT_MOC_LITERAL(19, 224, 19), // "on_btnClose_clicked"
QT_MOC_LITERAL(20, 244, 18) // "on_btnView_clicked"

    },
    "HistogramDialog\0read\0\0fileName\0"
    "readHistograms\0coords\0dims\0"
    "requestHistogramsData\0write\0processTfidf\0"
    "onReadDone\0ok\0message\0onWriteDone\0"
    "onReadHistogramsData\0readHistogramsData\0"
    "onHistogramsData\0HistogramsDrawingData*\0"
    "histograms\0on_btnClose_clicked\0"
    "on_btnView_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HistogramDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,
       4,    2,   77,    2, 0x06 /* Public */,
       7,    0,   82,    2, 0x06 /* Public */,
       8,    1,   83,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,   86,    2, 0x0a /* Public */,
      10,    2,   89,    2, 0x0a /* Public */,
      13,    2,   94,    2, 0x0a /* Public */,
      14,    2,   99,    2, 0x0a /* Public */,
      15,    0,  104,    2, 0x0a /* Public */,
      16,    1,  105,    2, 0x0a /* Public */,
      19,    0,  108,    2, 0x08 /* Private */,
      20,    0,  109,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    5,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString,   11,   12,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString,   11,   12,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString,   11,   12,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void HistogramDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        HistogramDialog *_t = static_cast<HistogramDialog *>(_o);
        switch (_id) {
        case 0: _t->read((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->readHistograms((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 2: _t->requestHistogramsData(); break;
        case 3: _t->write((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->processTfidf((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->onReadDone((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 6: _t->onWriteDone((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 7: _t->onReadHistogramsData((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 8: _t->readHistogramsData(); break;
        case 9: _t->onHistogramsData((*reinterpret_cast< HistogramsDrawingData*(*)>(_a[1]))); break;
        case 10: _t->on_btnClose_clicked(); break;
        case 11: _t->on_btnView_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (HistogramDialog::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HistogramDialog::read)) {
                *result = 0;
            }
        }
        {
            typedef void (HistogramDialog::*_t)(const QString & , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HistogramDialog::readHistograms)) {
                *result = 1;
            }
        }
        {
            typedef void (HistogramDialog::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HistogramDialog::requestHistogramsData)) {
                *result = 2;
            }
        }
        {
            typedef void (HistogramDialog::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HistogramDialog::write)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject HistogramDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_HistogramDialog.data,
      qt_meta_data_HistogramDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *HistogramDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HistogramDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_HistogramDialog.stringdata))
        return static_cast<void*>(const_cast< HistogramDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int HistogramDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void HistogramDialog::read(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void HistogramDialog::readHistograms(const QString & _t1, const QString & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void HistogramDialog::requestHistogramsData()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void HistogramDialog::write(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
