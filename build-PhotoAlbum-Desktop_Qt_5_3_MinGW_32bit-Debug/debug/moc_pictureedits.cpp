/****************************************************************************
** Meta object code from reading C++ file 'pictureedits.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../PhotoAlbum/pictureedits.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pictureedits.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_pictureedits_t {
    QByteArrayData data[9];
    char stringdata[65];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_pictureedits_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_pictureedits_t qt_meta_stringdata_pictureedits = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 8),
QT_MOC_LITERAL(2, 22, 0),
QT_MOC_LITERAL(3, 23, 8),
QT_MOC_LITERAL(4, 32, 4),
QT_MOC_LITERAL(5, 37, 5),
QT_MOC_LITERAL(6, 43, 6),
QT_MOC_LITERAL(7, 50, 7),
QT_MOC_LITERAL(8, 58, 6)
    },
    "pictureedits\0brighten\0\0contrast\0edge\0"
    "gamma\0negate\0sharpen\0smooth"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_pictureedits[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x08 /* Private */,
       3,    1,   52,    2, 0x08 /* Private */,
       4,    0,   55,    2, 0x08 /* Private */,
       5,    1,   56,    2, 0x08 /* Private */,
       6,    0,   59,    2, 0x08 /* Private */,
       7,    1,   60,    2, 0x08 /* Private */,
       8,    1,   63,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void pictureedits::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        pictureedits *_t = static_cast<pictureedits *>(_o);
        switch (_id) {
        case 0: _t->brighten((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->contrast((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->edge(); break;
        case 3: _t->gamma((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->negate(); break;
        case 5: _t->sharpen((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->smooth((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject pictureedits::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_pictureedits.data,
      qt_meta_data_pictureedits,  qt_static_metacall, 0, 0}
};


const QMetaObject *pictureedits::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *pictureedits::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_pictureedits.stringdata))
        return static_cast<void*>(const_cast< pictureedits*>(this));
    return QWidget::qt_metacast(_clname);
}

int pictureedits::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
