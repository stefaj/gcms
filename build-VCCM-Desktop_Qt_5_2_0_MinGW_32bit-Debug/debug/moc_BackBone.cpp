/****************************************************************************
** Meta object code from reading C++ file 'BackBone.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../VCCM/VCCMUI/BackBone.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'BackBone.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_BackBone_t {
    QByteArrayData data[12];
    char stringdata[102];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_BackBone_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_BackBone_t qt_meta_stringdata_BackBone = {
    {
QT_MOC_LITERAL(0, 0, 8),
QT_MOC_LITERAL(1, 9, 8),
QT_MOC_LITERAL(2, 18, 0),
QT_MOC_LITERAL(3, 19, 8),
QT_MOC_LITERAL(4, 28, 4),
QT_MOC_LITERAL(5, 33, 7),
QT_MOC_LITERAL(6, 41, 19),
QT_MOC_LITERAL(7, 61, 13),
QT_MOC_LITERAL(8, 75, 3),
QT_MOC_LITERAL(9, 79, 11),
QT_MOC_LITERAL(10, 91, 1),
QT_MOC_LITERAL(11, 93, 7)
    },
    "BackBone\0tChanged\0\0fForward\0sync\0"
    "cleanup\0handleWindowChanged\0QQuickWindow*\0"
    "win\0quitclicked\0t\0forward\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BackBone[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       2,   52, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06,
       3,    0,   45,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       4,    0,   46,    2, 0x0a,
       5,    0,   47,    2, 0x0a,
       6,    1,   48,    2, 0x08,
       9,    0,   51,    2, 0x08,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,

 // properties: name, type, flags
      10, QMetaType::QReal, 0x00495103,
      11, QMetaType::QReal, 0x00495003,

 // properties: notify_signal_id
       0,
       1,

       0        // eod
};

void BackBone::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        BackBone *_t = static_cast<BackBone *>(_o);
        switch (_id) {
        case 0: _t->tChanged(); break;
        case 1: _t->fForward(); break;
        case 2: _t->sync(); break;
        case 3: _t->cleanup(); break;
        case 4: _t->handleWindowChanged((*reinterpret_cast< QQuickWindow*(*)>(_a[1]))); break;
        case 5: _t->quitclicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (BackBone::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BackBone::tChanged)) {
                *result = 0;
            }
        }
        {
            typedef void (BackBone::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BackBone::fForward)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject BackBone::staticMetaObject = {
    { &QQuickItem::staticMetaObject, qt_meta_stringdata_BackBone.data,
      qt_meta_data_BackBone,  qt_static_metacall, 0, 0}
};


const QMetaObject *BackBone::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BackBone::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BackBone.stringdata))
        return static_cast<void*>(const_cast< BackBone*>(this));
    return QQuickItem::qt_metacast(_clname);
}

int BackBone::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QQuickItem::qt_metacall(_c, _id, _a);
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
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< qreal*>(_v) = t(); break;
        case 1: *reinterpret_cast< qreal*>(_v) = forward(); break;
        }
        _id -= 2;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setT(*reinterpret_cast< qreal*>(_v)); break;
        case 1: MoveForward(*reinterpret_cast< qreal*>(_v)); break;
        }
        _id -= 2;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void BackBone::tChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void BackBone::fForward()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
