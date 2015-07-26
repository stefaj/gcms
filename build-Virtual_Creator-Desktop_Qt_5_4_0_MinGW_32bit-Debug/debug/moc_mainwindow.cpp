/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Virtual_Creator/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[39];
    char stringdata[836];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 10), // "place_node"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 10), // "node_links"
QT_MOC_LITERAL(4, 34, 12), // "remove_nodes"
QT_MOC_LITERAL(5, 47, 12), // "remove_trees"
QT_MOC_LITERAL(6, 60, 14), // "place_pavement"
QT_MOC_LITERAL(7, 75, 10), // "place_wall"
QT_MOC_LITERAL(8, 86, 10), // "place_door"
QT_MOC_LITERAL(9, 97, 16), // "change_rotationY"
QT_MOC_LITERAL(10, 114, 10), // "place_tree"
QT_MOC_LITERAL(11, 125, 13), // "invert_mouseY"
QT_MOC_LITERAL(12, 139, 16), // "place_floor_plan"
QT_MOC_LITERAL(13, 156, 15), // "add_new_texture"
QT_MOC_LITERAL(14, 172, 16), // "set_object_scale"
QT_MOC_LITERAL(15, 189, 21), // "change_floor_selected"
QT_MOC_LITERAL(16, 211, 16), // "change_node_name"
QT_MOC_LITERAL(17, 228, 20), // "set_node_significant"
QT_MOC_LITERAL(18, 249, 13), // "load_premises"
QT_MOC_LITERAL(19, 263, 22), // "on_button_node_clicked"
QT_MOC_LITERAL(20, 286, 22), // "on_button_link_clicked"
QT_MOC_LITERAL(21, 309, 26), // "on_button_pavement_clicked"
QT_MOC_LITERAL(22, 336, 22), // "on_button_wall_clicked"
QT_MOC_LITERAL(23, 359, 22), // "on_button_door_clicked"
QT_MOC_LITERAL(24, 382, 30), // "on_spin_rotationY_valueChanged"
QT_MOC_LITERAL(25, 413, 4), // "arg1"
QT_MOC_LITERAL(26, 418, 34), // "on_checkBox_inversemouse_y_cl..."
QT_MOC_LITERAL(27, 453, 7), // "checked"
QT_MOC_LITERAL(28, 461, 23), // "on_button_tree1_clicked"
QT_MOC_LITERAL(29, 485, 29), // "on_button_remove_node_clicked"
QT_MOC_LITERAL(30, 515, 29), // "on_button_remove_tree_clicked"
QT_MOC_LITERAL(31, 545, 43), // "on_button_execute_virtual_con..."
QT_MOC_LITERAL(32, 589, 28), // "on_button_floor_plan_clicked"
QT_MOC_LITERAL(33, 618, 46), // "on_doubleSpinBox_floor_plan_w..."
QT_MOC_LITERAL(34, 665, 47), // "on_doubleSpinBox_floor_plan_h..."
QT_MOC_LITERAL(35, 713, 35), // "on_spinBox_floor_level_valueC..."
QT_MOC_LITERAL(36, 749, 33), // "on_lineEdit_node_name_textCha..."
QT_MOC_LITERAL(37, 783, 31), // "on_checkbox_significant_clicked"
QT_MOC_LITERAL(38, 815, 20) // "send_loaded_premises"

    },
    "MainWindow\0place_node\0\0node_links\0"
    "remove_nodes\0remove_trees\0place_pavement\0"
    "place_wall\0place_door\0change_rotationY\0"
    "place_tree\0invert_mouseY\0place_floor_plan\0"
    "add_new_texture\0set_object_scale\0"
    "change_floor_selected\0change_node_name\0"
    "set_node_significant\0load_premises\0"
    "on_button_node_clicked\0on_button_link_clicked\0"
    "on_button_pavement_clicked\0"
    "on_button_wall_clicked\0on_button_door_clicked\0"
    "on_spin_rotationY_valueChanged\0arg1\0"
    "on_checkBox_inversemouse_y_clicked\0"
    "checked\0on_button_tree1_clicked\0"
    "on_button_remove_node_clicked\0"
    "on_button_remove_tree_clicked\0"
    "on_button_execute_virtual_concierge_clicked\0"
    "on_button_floor_plan_clicked\0"
    "on_doubleSpinBox_floor_plan_width_valueChanged\0"
    "on_doubleSpinBox_floor_plan_height_valueChanged\0"
    "on_spinBox_floor_level_valueChanged\0"
    "on_lineEdit_node_name_textChanged\0"
    "on_checkbox_significant_clicked\0"
    "send_loaded_premises"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      35,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      17,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  189,    2, 0x06 /* Public */,
       3,    1,  192,    2, 0x06 /* Public */,
       4,    1,  195,    2, 0x06 /* Public */,
       5,    1,  198,    2, 0x06 /* Public */,
       6,    1,  201,    2, 0x06 /* Public */,
       7,    1,  204,    2, 0x06 /* Public */,
       8,    1,  207,    2, 0x06 /* Public */,
       9,    1,  210,    2, 0x06 /* Public */,
      10,    1,  213,    2, 0x06 /* Public */,
      11,    1,  216,    2, 0x06 /* Public */,
      12,    1,  219,    2, 0x06 /* Public */,
      13,    1,  222,    2, 0x06 /* Public */,
      14,    1,  225,    2, 0x06 /* Public */,
      15,    1,  228,    2, 0x06 /* Public */,
      16,    1,  231,    2, 0x06 /* Public */,
      17,    1,  234,    2, 0x06 /* Public */,
      18,    1,  237,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      19,    0,  240,    2, 0x08 /* Private */,
      20,    0,  241,    2, 0x08 /* Private */,
      21,    0,  242,    2, 0x08 /* Private */,
      22,    0,  243,    2, 0x08 /* Private */,
      23,    0,  244,    2, 0x08 /* Private */,
      24,    1,  245,    2, 0x08 /* Private */,
      26,    1,  248,    2, 0x08 /* Private */,
      28,    0,  251,    2, 0x08 /* Private */,
      29,    0,  252,    2, 0x08 /* Private */,
      30,    0,  253,    2, 0x08 /* Private */,
      31,    0,  254,    2, 0x08 /* Private */,
      32,    0,  255,    2, 0x08 /* Private */,
      33,    1,  256,    2, 0x08 /* Private */,
      34,    1,  259,    2, 0x08 /* Private */,
      35,    1,  262,    2, 0x08 /* Private */,
      36,    1,  265,    2, 0x08 /* Private */,
      37,    1,  268,    2, 0x08 /* Private */,
      38,    0,  271,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QVector3D,    2,
    QMetaType::Void, QMetaType::Float,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,   25,
    QMetaType::Void, QMetaType::Bool,   27,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,   25,
    QMetaType::Void, QMetaType::Double,   25,
    QMetaType::Void, QMetaType::Int,   25,
    QMetaType::Void, QMetaType::QString,   25,
    QMetaType::Void, QMetaType::Bool,   27,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->place_node((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->node_links((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->remove_nodes((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->remove_trees((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->place_pavement((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->place_wall((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->place_door((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->change_rotationY((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 8: _t->place_tree((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->invert_mouseY((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->place_floor_plan((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->add_new_texture((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: _t->set_object_scale((*reinterpret_cast< QVector3D(*)>(_a[1]))); break;
        case 13: _t->change_floor_selected((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 14: _t->change_node_name((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 15: _t->set_node_significant((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 16: _t->load_premises((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 17: _t->on_button_node_clicked(); break;
        case 18: _t->on_button_link_clicked(); break;
        case 19: _t->on_button_pavement_clicked(); break;
        case 20: _t->on_button_wall_clicked(); break;
        case 21: _t->on_button_door_clicked(); break;
        case 22: _t->on_spin_rotationY_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 23: _t->on_checkBox_inversemouse_y_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 24: _t->on_button_tree1_clicked(); break;
        case 25: _t->on_button_remove_node_clicked(); break;
        case 26: _t->on_button_remove_tree_clicked(); break;
        case 27: _t->on_button_execute_virtual_concierge_clicked(); break;
        case 28: _t->on_button_floor_plan_clicked(); break;
        case 29: _t->on_doubleSpinBox_floor_plan_width_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 30: _t->on_doubleSpinBox_floor_plan_height_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 31: _t->on_spinBox_floor_level_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 32: _t->on_lineEdit_node_name_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 33: _t->on_checkbox_significant_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 34: _t->send_loaded_premises(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainWindow::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::place_node)) {
                *result = 0;
            }
        }
        {
            typedef void (MainWindow::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::node_links)) {
                *result = 1;
            }
        }
        {
            typedef void (MainWindow::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::remove_nodes)) {
                *result = 2;
            }
        }
        {
            typedef void (MainWindow::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::remove_trees)) {
                *result = 3;
            }
        }
        {
            typedef void (MainWindow::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::place_pavement)) {
                *result = 4;
            }
        }
        {
            typedef void (MainWindow::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::place_wall)) {
                *result = 5;
            }
        }
        {
            typedef void (MainWindow::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::place_door)) {
                *result = 6;
            }
        }
        {
            typedef void (MainWindow::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::change_rotationY)) {
                *result = 7;
            }
        }
        {
            typedef void (MainWindow::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::place_tree)) {
                *result = 8;
            }
        }
        {
            typedef void (MainWindow::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::invert_mouseY)) {
                *result = 9;
            }
        }
        {
            typedef void (MainWindow::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::place_floor_plan)) {
                *result = 10;
            }
        }
        {
            typedef void (MainWindow::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::add_new_texture)) {
                *result = 11;
            }
        }
        {
            typedef void (MainWindow::*_t)(QVector3D );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::set_object_scale)) {
                *result = 12;
            }
        }
        {
            typedef void (MainWindow::*_t)(float );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::change_floor_selected)) {
                *result = 13;
            }
        }
        {
            typedef void (MainWindow::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::change_node_name)) {
                *result = 14;
            }
        }
        {
            typedef void (MainWindow::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::set_node_significant)) {
                *result = 15;
            }
        }
        {
            typedef void (MainWindow::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::load_premises)) {
                *result = 16;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 35)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 35;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 35)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 35;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::place_node(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::node_links(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MainWindow::remove_nodes(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MainWindow::remove_trees(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MainWindow::place_pavement(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void MainWindow::place_wall(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void MainWindow::place_door(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void MainWindow::change_rotationY(double _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void MainWindow::place_tree(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void MainWindow::invert_mouseY(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void MainWindow::place_floor_plan(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void MainWindow::add_new_texture(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void MainWindow::set_object_scale(QVector3D _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void MainWindow::change_floor_selected(float _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void MainWindow::change_node_name(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void MainWindow::set_node_significant(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void MainWindow::load_premises(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}
QT_END_MOC_NAMESPACE
