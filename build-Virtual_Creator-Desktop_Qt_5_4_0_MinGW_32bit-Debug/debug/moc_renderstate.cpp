/****************************************************************************
** Meta object code from reading C++ file 'renderstate.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Virtual_Creator/RenderStates/renderstate.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'renderstate.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_RenderState_t {
    QByteArrayData data[21];
    char stringdata[307];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RenderState_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RenderState_t qt_meta_stringdata_RenderState = {
    {
QT_MOC_LITERAL(0, 0, 11), // "RenderState"
QT_MOC_LITERAL(1, 12, 8), // "add_node"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 8), // "QString*"
QT_MOC_LITERAL(4, 31, 10), // "allow_node"
QT_MOC_LITERAL(5, 42, 17), // "allow_remove_node"
QT_MOC_LITERAL(6, 60, 17), // "allow_remove_tree"
QT_MOC_LITERAL(7, 78, 10), // "allow_link"
QT_MOC_LITERAL(8, 89, 14), // "allow_pavement"
QT_MOC_LITERAL(9, 104, 10), // "allow_door"
QT_MOC_LITERAL(10, 115, 10), // "allow_wall"
QT_MOC_LITERAL(11, 126, 10), // "allow_tree"
QT_MOC_LITERAL(12, 137, 16), // "allow_floor_plan"
QT_MOC_LITERAL(13, 154, 11), // "change_rotY"
QT_MOC_LITERAL(14, 166, 13), // "invert_mouseY"
QT_MOC_LITERAL(15, 180, 22), // "load_texture_from_file"
QT_MOC_LITERAL(16, 203, 16), // "set_object_scale"
QT_MOC_LITERAL(17, 220, 27), // "change_current_floor_height"
QT_MOC_LITERAL(18, 248, 18), // "set_next_node_name"
QT_MOC_LITERAL(19, 267, 25), // "set_next_node_significant"
QT_MOC_LITERAL(20, 293, 13) // "load_premises"

    },
    "RenderState\0add_node\0\0QString*\0"
    "allow_node\0allow_remove_node\0"
    "allow_remove_tree\0allow_link\0"
    "allow_pavement\0allow_door\0allow_wall\0"
    "allow_tree\0allow_floor_plan\0change_rotY\0"
    "invert_mouseY\0load_texture_from_file\0"
    "set_object_scale\0change_current_floor_height\0"
    "set_next_node_name\0set_next_node_significant\0"
    "load_premises"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RenderState[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,  104,    2, 0x08 /* Private */,
       4,    1,  107,    2, 0x08 /* Private */,
       5,    1,  110,    2, 0x08 /* Private */,
       6,    1,  113,    2, 0x08 /* Private */,
       7,    1,  116,    2, 0x08 /* Private */,
       8,    1,  119,    2, 0x08 /* Private */,
       9,    1,  122,    2, 0x08 /* Private */,
      10,    1,  125,    2, 0x08 /* Private */,
      11,    1,  128,    2, 0x08 /* Private */,
      12,    1,  131,    2, 0x08 /* Private */,
      13,    1,  134,    2, 0x08 /* Private */,
      14,    1,  137,    2, 0x08 /* Private */,
      15,    1,  140,    2, 0x08 /* Private */,
      16,    1,  143,    2, 0x08 /* Private */,
      17,    1,  146,    2, 0x08 /* Private */,
      18,    1,  149,    2, 0x08 /* Private */,
      19,    1,  152,    2, 0x08 /* Private */,
      20,    1,  155,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QVector3D,    2,
    QMetaType::Void, QMetaType::Float,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::QString,    2,

       0        // eod
};

void RenderState::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RenderState *_t = static_cast<RenderState *>(_o);
        switch (_id) {
        case 0: _t->add_node((*reinterpret_cast< QString*(*)>(_a[1]))); break;
        case 1: _t->allow_node((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->allow_remove_node((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->allow_remove_tree((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->allow_link((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->allow_pavement((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->allow_door((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->allow_wall((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->allow_tree((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->allow_floor_plan((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->change_rotY((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 11: _t->invert_mouseY((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->load_texture_from_file((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: _t->set_object_scale((*reinterpret_cast< QVector3D(*)>(_a[1]))); break;
        case 14: _t->change_current_floor_height((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 15: _t->set_next_node_name((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 16: _t->set_next_node_significant((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 17: _t->load_premises((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject RenderState::staticMetaObject = {
    { &QOpenGLWidget::staticMetaObject, qt_meta_stringdata_RenderState.data,
      qt_meta_data_RenderState,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *RenderState::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RenderState::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_RenderState.stringdata))
        return static_cast<void*>(const_cast< RenderState*>(this));
    if (!strcmp(_clname, "QOpenGLFunctions"))
        return static_cast< QOpenGLFunctions*>(const_cast< RenderState*>(this));
    return QOpenGLWidget::qt_metacast(_clname);
}

int RenderState::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QOpenGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 18;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
