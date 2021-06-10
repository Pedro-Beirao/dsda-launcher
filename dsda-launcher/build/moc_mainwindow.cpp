/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    const uint offsetsAndSize[42];
    char stringdata0[364];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 10), // "MainWindow"
QT_MOC_LITERAL(11, 7), // "addWads"
QT_MOC_LITERAL(19, 0), // ""
QT_MOC_LITERAL(20, 9), // "fileNames"
QT_MOC_LITERAL(30, 27), // "on_LaunchGameButton_clicked"
QT_MOC_LITERAL(58, 33), // "on_iwadSelect_currentIndexCha..."
QT_MOC_LITERAL(92, 5), // "index"
QT_MOC_LITERAL(98, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(120, 15), // "on_plus_clicked"
QT_MOC_LITERAL(136, 16), // "on_minus_clicked"
QT_MOC_LITERAL(153, 20), // "on_fastCheck_toggled"
QT_MOC_LITERAL(174, 7), // "checked"
QT_MOC_LITERAL(182, 18), // "on_noCheck_toggled"
QT_MOC_LITERAL(201, 21), // "on_toolButton_toggled"
QT_MOC_LITERAL(223, 20), // "on_noCheck_4_toggled"
QT_MOC_LITERAL(244, 20), // "on_noCheck_3_toggled"
QT_MOC_LITERAL(265, 23), // "on_soloNetCheck_toggled"
QT_MOC_LITERAL(289, 22), // "on_tabs_currentChanged"
QT_MOC_LITERAL(312, 3), // "foo"
QT_MOC_LITERAL(316, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(340, 23) // "on_pushButton_3_clicked"

    },
    "MainWindow\0addWads\0\0fileNames\0"
    "on_LaunchGameButton_clicked\0"
    "on_iwadSelect_currentIndexChanged\0"
    "index\0on_pushButton_clicked\0on_plus_clicked\0"
    "on_minus_clicked\0on_fastCheck_toggled\0"
    "checked\0on_noCheck_toggled\0"
    "on_toolButton_toggled\0on_noCheck_4_toggled\0"
    "on_noCheck_3_toggled\0on_soloNetCheck_toggled\0"
    "on_tabs_currentChanged\0foo\0"
    "on_pushButton_2_clicked\0on_pushButton_3_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       9,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,  110,    2, 0x0a,    0 /* Public */,
       4,    0,  113,    2, 0x08,    2 /* Private */,
       5,    1,  114,    2, 0x08,    3 /* Private */,
       7,    0,  117,    2, 0x08,    5 /* Private */,
       8,    0,  118,    2, 0x08,    6 /* Private */,
       9,    0,  119,    2, 0x08,    7 /* Private */,
      10,    1,  120,    2, 0x08,    8 /* Private */,
      12,    1,  123,    2, 0x08,   10 /* Private */,
      13,    1,  126,    2, 0x08,   12 /* Private */,
      14,    1,  129,    2, 0x08,   14 /* Private */,
      15,    1,  132,    2, 0x08,   16 /* Private */,
      16,    1,  135,    2, 0x08,   18 /* Private */,
      17,    1,  138,    2, 0x08,   20 /* Private */,
      18,    0,  141,    2, 0x08,   22 /* Private */,
      19,    0,  142,    2, 0x08,   23 /* Private */,
      20,    0,  143,    2, 0x08,   24 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QStringList,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   11,
    QMetaType::Void, QMetaType::Bool,   11,
    QMetaType::Void, QMetaType::Bool,   11,
    QMetaType::Void, QMetaType::Bool,   11,
    QMetaType::Void, QMetaType::Bool,   11,
    QMetaType::Void, QMetaType::Bool,   11,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->addWads((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 1: _t->on_LaunchGameButton_clicked(); break;
        case 2: _t->on_iwadSelect_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_pushButton_clicked(); break;
        case 4: _t->on_plus_clicked(); break;
        case 5: _t->on_minus_clicked(); break;
        case 6: _t->on_fastCheck_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->on_noCheck_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->on_toolButton_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->on_noCheck_4_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->on_noCheck_3_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->on_soloNetCheck_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->on_tabs_currentChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->foo(); break;
        case 14: _t->on_pushButton_2_clicked(); break;
        case 15: _t->on_pushButton_3_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.offsetsAndSize,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_MainWindow_t

, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QStringList, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 16;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
