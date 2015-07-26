/****************************************************************************
** Meta object code from reading C++ file 'virtualconcierge.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Virtual_Creator/virtualconcierge.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'virtualconcierge.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_VirtualConcierge_t {
    QByteArrayData data[5];
    char stringdata[77];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VirtualConcierge_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VirtualConcierge_t qt_meta_stringdata_VirtualConcierge = {
    {
QT_MOC_LITERAL(0, 0, 16), // "VirtualConcierge"
QT_MOC_LITERAL(1, 17, 9), // "find_path"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 16), // "get_button_value"
QT_MOC_LITERAL(4, 45, 31) // "on_pushButton_send_mail_clicked"

    },
    "VirtualConcierge\0find_path\0\0"
    "get_button_value\0on_pushButton_send_mail_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VirtualConcierge[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   34,    2, 0x08 /* Private */,
       4,    0,   37,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,

       0        // eod
};

void VirtualConcierge::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VirtualConcierge *_t = static_cast<VirtualConcierge *>(_o);
        switch (_id) {
        case 0: _t->find_path((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->get_button_value((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_pushButton_send_mail_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (VirtualConcierge::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VirtualConcierge::find_path)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject VirtualConcierge::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_VirtualConcierge.data,
      qt_meta_data_VirtualConcierge,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *VirtualConcierge::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VirtualConcierge::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_VirtualConcierge.stringdata))
        return static_cast<void*>(const_cast< VirtualConcierge*>(this));
    return QWidget::qt_metacast(_clname);
}

int VirtualConcierge::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void VirtualConcierge::find_path(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
