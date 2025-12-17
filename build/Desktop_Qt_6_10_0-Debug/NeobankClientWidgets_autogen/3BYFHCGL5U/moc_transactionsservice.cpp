/****************************************************************************
** Meta object code from reading C++ file 'transactionsservice.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../services/transactionsservice.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'transactionsservice.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN19TransactionsServiceE_t {};
} // unnamed namespace

template <> constexpr inline auto TransactionsService::qt_create_metaobjectdata<qt_meta_tag_ZN19TransactionsServiceE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "TransactionsService",
        "transactionsUpdated",
        "",
        "QList<TransactionInfo>",
        "transactions",
        "transactionsFailed",
        "reason",
        "transactionCreated",
        "TransactionInfo",
        "transaction"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'transactionsUpdated'
        QtMocHelpers::SignalData<void(const QList<TransactionInfo> &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Signal 'transactionsFailed'
        QtMocHelpers::SignalData<void(const QString &)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 6 },
        }}),
        // Signal 'transactionCreated'
        QtMocHelpers::SignalData<void(const TransactionInfo &)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 8, 9 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<TransactionsService, qt_meta_tag_ZN19TransactionsServiceE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject TransactionsService::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN19TransactionsServiceE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN19TransactionsServiceE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN19TransactionsServiceE_t>.metaTypes,
    nullptr
} };

void TransactionsService::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<TransactionsService *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->transactionsUpdated((*reinterpret_cast<std::add_pointer_t<QList<TransactionInfo>>>(_a[1]))); break;
        case 1: _t->transactionsFailed((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->transactionCreated((*reinterpret_cast<std::add_pointer_t<TransactionInfo>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (TransactionsService::*)(const QList<TransactionInfo> & )>(_a, &TransactionsService::transactionsUpdated, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (TransactionsService::*)(const QString & )>(_a, &TransactionsService::transactionsFailed, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (TransactionsService::*)(const TransactionInfo & )>(_a, &TransactionsService::transactionCreated, 2))
            return;
    }
}

const QMetaObject *TransactionsService::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TransactionsService::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN19TransactionsServiceE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int TransactionsService::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void TransactionsService::transactionsUpdated(const QList<TransactionInfo> & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void TransactionsService::transactionsFailed(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void TransactionsService::transactionCreated(const TransactionInfo & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}
QT_WARNING_POP
