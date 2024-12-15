/****************************************************************************
** Meta object code from reading C++ file 'interface.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.13)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../LAB №6/LAB5_Client/interface.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'interface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.13. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Interface_t {
    QByteArrayData data[17];
    char stringdata0[287];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Interface_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Interface_t qt_meta_stringdata_Interface = {
    {
QT_MOC_LITERAL(0, 0, 9), // "Interface"
QT_MOC_LITERAL(1, 10, 22), // "OnCreatePolynomClicked"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 20), // "OnChangeValueClicked"
QT_MOC_LITERAL(4, 55, 20), // "OnCalcPolynomClicked"
QT_MOC_LITERAL(5, 76, 21), // "OnPrintPolynomClicked"
QT_MOC_LITERAL(6, 98, 18), // "onRootCountChanged"
QT_MOC_LITERAL(7, 117, 4), // "text"
QT_MOC_LITERAL(8, 122, 15), // "onConfirmCreate"
QT_MOC_LITERAL(9, 138, 19), // "onClearCreateFields"
QT_MOC_LITERAL(10, 158, 21), // "onConfirmChangeButton"
QT_MOC_LITERAL(11, 180, 16), // "createLeftLayout"
QT_MOC_LITERAL(12, 197, 24), // "createRightComplexLayout"
QT_MOC_LITERAL(13, 222, 23), // "createRightDoubleLayout"
QT_MOC_LITERAL(14, 246, 18), // "onNumberSetChanged"
QT_MOC_LITERAL(15, 265, 13), // "handleMessage"
QT_MOC_LITERAL(16, 279, 7) // "message"

    },
    "Interface\0OnCreatePolynomClicked\0\0"
    "OnChangeValueClicked\0OnCalcPolynomClicked\0"
    "OnPrintPolynomClicked\0onRootCountChanged\0"
    "text\0onConfirmCreate\0onClearCreateFields\0"
    "onConfirmChangeButton\0createLeftLayout\0"
    "createRightComplexLayout\0"
    "createRightDoubleLayout\0onNumberSetChanged\0"
    "handleMessage\0message"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Interface[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x08 /* Private */,
       3,    0,   80,    2, 0x08 /* Private */,
       4,    0,   81,    2, 0x08 /* Private */,
       5,    0,   82,    2, 0x08 /* Private */,
       6,    1,   83,    2, 0x08 /* Private */,
       8,    0,   86,    2, 0x08 /* Private */,
       9,    0,   87,    2, 0x08 /* Private */,
      10,    0,   88,    2, 0x08 /* Private */,
      11,    0,   89,    2, 0x08 /* Private */,
      12,    0,   90,    2, 0x08 /* Private */,
      13,    0,   91,    2, 0x08 /* Private */,
      14,    0,   92,    2, 0x08 /* Private */,
      15,    1,   93,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   16,

       0        // eod
};

void Interface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Interface *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->OnCreatePolynomClicked(); break;
        case 1: _t->OnChangeValueClicked(); break;
        case 2: _t->OnCalcPolynomClicked(); break;
        case 3: _t->OnPrintPolynomClicked(); break;
        case 4: _t->onRootCountChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->onConfirmCreate(); break;
        case 6: _t->onClearCreateFields(); break;
        case 7: _t->onConfirmChangeButton(); break;
        case 8: _t->createLeftLayout(); break;
        case 9: _t->createRightComplexLayout(); break;
        case 10: _t->createRightDoubleLayout(); break;
        case 11: _t->onNumberSetChanged(); break;
        case 12: _t->handleMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Interface::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_Interface.data,
    qt_meta_data_Interface,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Interface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Interface::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Interface.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Interface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
