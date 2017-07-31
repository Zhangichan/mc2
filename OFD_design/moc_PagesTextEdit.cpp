/****************************************************************************
** Meta object code from reading C++ file 'PagesTextEdit.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "PagesTextEdit.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PagesTextEdit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PagesTextEdit_t {
    QByteArrayData data[16];
    char stringdata0[234];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PagesTextEdit_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PagesTextEdit_t qt_meta_stringdata_PagesTextEdit = {
    {
QT_MOC_LITERAL(0, 0, 13), // "PagesTextEdit"
QT_MOC_LITERAL(1, 14, 14), // "setUsePageMode"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 4), // "_use"
QT_MOC_LITERAL(4, 35, 19), // "setAddSpaceToBottom"
QT_MOC_LITERAL(5, 55, 9), // "_addSpace"
QT_MOC_LITERAL(6, 65, 18), // "setShowPageNumbers"
QT_MOC_LITERAL(7, 84, 5), // "_show"
QT_MOC_LITERAL(8, 90, 23), // "setPageNumbersAlignment"
QT_MOC_LITERAL(9, 114, 13), // "Qt::Alignment"
QT_MOC_LITERAL(10, 128, 6), // "_align"
QT_MOC_LITERAL(11, 135, 31), // "aboutVerticalScrollRangeChanged"
QT_MOC_LITERAL(12, 167, 8), // "_minimum"
QT_MOC_LITERAL(13, 176, 8), // "_maximum"
QT_MOC_LITERAL(14, 185, 20), // "aboutDocumentChanged"
QT_MOC_LITERAL(15, 206, 27) // "aboutUpdateDocumentGeometry"

    },
    "PagesTextEdit\0setUsePageMode\0\0_use\0"
    "setAddSpaceToBottom\0_addSpace\0"
    "setShowPageNumbers\0_show\0"
    "setPageNumbersAlignment\0Qt::Alignment\0"
    "_align\0aboutVerticalScrollRangeChanged\0"
    "_minimum\0_maximum\0aboutDocumentChanged\0"
    "aboutUpdateDocumentGeometry"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PagesTextEdit[] = {

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
       1,    1,   49,    2, 0x0a /* Public */,
       4,    1,   52,    2, 0x0a /* Public */,
       6,    1,   55,    2, 0x0a /* Public */,
       8,    1,   58,    2, 0x0a /* Public */,
      11,    2,   61,    2, 0x08 /* Private */,
      14,    0,   66,    2, 0x08 /* Private */,
      15,    0,   67,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   12,   13,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PagesTextEdit::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PagesTextEdit *_t = static_cast<PagesTextEdit *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setUsePageMode((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->setAddSpaceToBottom((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->setShowPageNumbers((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->setPageNumbersAlignment((*reinterpret_cast< Qt::Alignment(*)>(_a[1]))); break;
        case 4: _t->aboutVerticalScrollRangeChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->aboutDocumentChanged(); break;
        case 6: _t->aboutUpdateDocumentGeometry(); break;
        default: ;
        }
    }
}

const QMetaObject PagesTextEdit::staticMetaObject = {
    { &QTextEdit::staticMetaObject, qt_meta_stringdata_PagesTextEdit.data,
      qt_meta_data_PagesTextEdit,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PagesTextEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PagesTextEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PagesTextEdit.stringdata0))
        return static_cast<void*>(const_cast< PagesTextEdit*>(this));
    return QTextEdit::qt_metacast(_clname);
}

int PagesTextEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTextEdit::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
