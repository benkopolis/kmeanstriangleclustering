/****************************************************************************
** Meta object code from reading C++ file 'stemmedfileparsercontroller.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "controllers/stemmedfileparsercontroller.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'stemmedfileparsercontroller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_StemmedFileParserController_t {
    QByteArrayData data[14];
    char stringdata[147];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StemmedFileParserController_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StemmedFileParserController_t qt_meta_stringdata_StemmedFileParserController = {
    {
QT_MOC_LITERAL(0, 0, 27), // "StemmedFileParserController"
QT_MOC_LITERAL(1, 28, 8), // "readDone"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 2), // "ok"
QT_MOC_LITERAL(4, 41, 11), // "processDone"
QT_MOC_LITERAL(5, 53, 9), // "writeDone"
QT_MOC_LITERAL(6, 63, 22), // "generateHistogramsDone"
QT_MOC_LITERAL(7, 86, 7), // "message"
QT_MOC_LITERAL(8, 94, 6), // "onRead"
QT_MOC_LITERAL(9, 101, 2), // "in"
QT_MOC_LITERAL(10, 104, 9), // "onProcess"
QT_MOC_LITERAL(11, 114, 7), // "onWrite"
QT_MOC_LITERAL(12, 122, 3), // "out"
QT_MOC_LITERAL(13, 126, 20) // "onGenerateHistograms"

    },
    "StemmedFileParserController\0readDone\0"
    "\0ok\0processDone\0writeDone\0"
    "generateHistogramsDone\0message\0onRead\0"
    "in\0onProcess\0onWrite\0out\0onGenerateHistograms"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StemmedFileParserController[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       4,    0,   57,    2, 0x06 /* Public */,
       5,    1,   58,    2, 0x06 /* Public */,
       6,    2,   61,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    1,   66,    2, 0x0a /* Public */,
      10,    0,   69,    2, 0x0a /* Public */,
      11,    1,   70,    2, 0x0a /* Public */,
      13,    1,   73,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString,    3,    7,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void, QMetaType::QString,   12,

       0        // eod
};

void StemmedFileParserController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        StemmedFileParserController *_t = static_cast<StemmedFileParserController *>(_o);
        switch (_id) {
        case 0: _t->readDone((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->processDone(); break;
        case 2: _t->writeDone((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->generateHistogramsDone((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 4: _t->onRead((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->onProcess(); break;
        case 6: _t->onWrite((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->onGenerateHistograms((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (StemmedFileParserController::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&StemmedFileParserController::readDone)) {
                *result = 0;
            }
        }
        {
            typedef void (StemmedFileParserController::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&StemmedFileParserController::processDone)) {
                *result = 1;
            }
        }
        {
            typedef void (StemmedFileParserController::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&StemmedFileParserController::writeDone)) {
                *result = 2;
            }
        }
        {
            typedef void (StemmedFileParserController::*_t)(bool , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&StemmedFileParserController::generateHistogramsDone)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject StemmedFileParserController::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_StemmedFileParserController.data,
      qt_meta_data_StemmedFileParserController,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *StemmedFileParserController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StemmedFileParserController::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_StemmedFileParserController.stringdata))
        return static_cast<void*>(const_cast< StemmedFileParserController*>(this));
    return QObject::qt_metacast(_clname);
}

int StemmedFileParserController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void StemmedFileParserController::readDone(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void StemmedFileParserController::processDone()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void StemmedFileParserController::writeDone(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void StemmedFileParserController::generateHistogramsDone(bool _t1, const QString & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
