/****************************************************************************
** Meta object code from reading C++ file 'addelement.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/addelement.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'addelement.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AddElement_t {
    QByteArrayData data[17];
    char stringdata0[343];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AddElement_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AddElement_t qt_meta_stringdata_AddElement = {
    {
QT_MOC_LITERAL(0, 0, 10), // "AddElement"
QT_MOC_LITERAL(1, 11, 21), // "sendTimeTableZoneData"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 5), // "bool*"
QT_MOC_LITERAL(4, 40, 11), // "ElementData"
QT_MOC_LITERAL(5, 52, 18), // "sendBreeksZoneData"
QT_MOC_LITERAL(6, 71, 10), // "BreeksData"
QT_MOC_LITERAL(7, 82, 20), // "on_buttonAdd_clicked"
QT_MOC_LITERAL(8, 103, 23), // "on_buttonMonday_clicked"
QT_MOC_LITERAL(9, 127, 24), // "on_buttonTuesday_clicked"
QT_MOC_LITERAL(10, 152, 26), // "on_buttonWednesday_clicked"
QT_MOC_LITERAL(11, 179, 25), // "on_buttonThursday_clicked"
QT_MOC_LITERAL(12, 205, 23), // "on_buttonFriday_clicked"
QT_MOC_LITERAL(13, 229, 25), // "on_buttonSaturday_clicked"
QT_MOC_LITERAL(14, 255, 20), // "on_buttonTag_clicked"
QT_MOC_LITERAL(15, 276, 34), // "on_pushButtonTimeTableZone_cl..."
QT_MOC_LITERAL(16, 311, 31) // "on_pushButtonBreeksZone_clicked"

    },
    "AddElement\0sendTimeTableZoneData\0\0"
    "bool*\0ElementData\0sendBreeksZoneData\0"
    "BreeksData\0on_buttonAdd_clicked\0"
    "on_buttonMonday_clicked\0"
    "on_buttonTuesday_clicked\0"
    "on_buttonWednesday_clicked\0"
    "on_buttonThursday_clicked\0"
    "on_buttonFriday_clicked\0"
    "on_buttonSaturday_clicked\0"
    "on_buttonTag_clicked\0"
    "on_pushButtonTimeTableZone_clicked\0"
    "on_pushButtonBreeksZone_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AddElement[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   74,    2, 0x06 /* Public */,
       5,    3,   81,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   88,    2, 0x08 /* Private */,
       8,    0,   89,    2, 0x08 /* Private */,
       9,    0,   90,    2, 0x08 /* Private */,
      10,    0,   91,    2, 0x08 /* Private */,
      11,    0,   92,    2, 0x08 /* Private */,
      12,    0,   93,    2, 0x08 /* Private */,
      13,    0,   94,    2, 0x08 /* Private */,
      14,    0,   95,    2, 0x08 /* Private */,
      15,    0,   96,    2, 0x08 /* Private */,
      16,    0,   97,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int, 0x80000000 | 4,    2,    2,    2,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int, 0x80000000 | 6,    2,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void AddElement::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AddElement *_t = static_cast<AddElement *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendTimeTableZoneData((*reinterpret_cast< bool*(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2])),(*reinterpret_cast< ElementData(*)>(_a[3]))); break;
        case 1: _t->sendBreeksZoneData((*reinterpret_cast< bool*(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2])),(*reinterpret_cast< BreeksData(*)>(_a[3]))); break;
        case 2: _t->on_buttonAdd_clicked(); break;
        case 3: _t->on_buttonMonday_clicked(); break;
        case 4: _t->on_buttonTuesday_clicked(); break;
        case 5: _t->on_buttonWednesday_clicked(); break;
        case 6: _t->on_buttonThursday_clicked(); break;
        case 7: _t->on_buttonFriday_clicked(); break;
        case 8: _t->on_buttonSaturday_clicked(); break;
        case 9: _t->on_buttonTag_clicked(); break;
        case 10: _t->on_pushButtonTimeTableZone_clicked(); break;
        case 11: _t->on_pushButtonBreeksZone_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (AddElement::*)(bool * , const int , ElementData );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AddElement::sendTimeTableZoneData)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (AddElement::*)(bool * , const int , BreeksData );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AddElement::sendBreeksZoneData)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject AddElement::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_AddElement.data,
      qt_meta_data_AddElement,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *AddElement::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AddElement::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AddElement.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int AddElement::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void AddElement::sendTimeTableZoneData(bool * _t1, const int _t2, ElementData _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AddElement::sendBreeksZoneData(bool * _t1, const int _t2, BreeksData _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
