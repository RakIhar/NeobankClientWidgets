/****************************************************************************
** Meta object code from reading C++ file 'transactionspage.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../pages/transactionspage.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'transactionspage.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN16TransactionsPageE_t {};
} // unnamed namespace

template <> constexpr inline auto TransactionsPage::qt_create_metaobjectdata<qt_meta_tag_ZN16TransactionsPageE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "TransactionsPage",
        "pr_dashboard",
        "",
        "r_transactions",
        "onTransactionsUpdated",
        "QList<TransactionInfo>",
        "transactions",
        "onTransactionsFailed",
        "reason",
        "onTransactionCreated",
        "TransactionInfo",
        "transaction"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'pr_dashboard'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'r_transactions'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'onTransactionsUpdated'
        QtMocHelpers::SlotData<void(const QList<TransactionInfo> &)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 5, 6 },
        }}),
        // Slot 'onTransactionsFailed'
        QtMocHelpers::SlotData<void(const QString &)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 8 },
        }}),
        // Slot 'onTransactionCreated'
        QtMocHelpers::SlotData<void(const TransactionInfo &)>(9, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 10, 11 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<TransactionsPage, qt_meta_tag_ZN16TransactionsPageE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject TransactionsPage::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16TransactionsPageE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16TransactionsPageE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN16TransactionsPageE_t>.metaTypes,
    nullptr
} };

void TransactionsPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<TransactionsPage *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->pr_dashboard(); break;
        case 1: _t->r_transactions(); break;
        case 2: _t->onTransactionsUpdated((*reinterpret_cast<std::add_pointer_t<QList<TransactionInfo>>>(_a[1]))); break;
        case 3: _t->onTransactionsFailed((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->onTransactionCreated((*reinterpret_cast<std::add_pointer_t<TransactionInfo>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (TransactionsPage::*)()>(_a, &TransactionsPage::pr_dashboard, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (TransactionsPage::*)()>(_a, &TransactionsPage::r_transactions, 1))
            return;
    }
}

const QMetaObject *TransactionsPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TransactionsPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16TransactionsPageE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int TransactionsPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void TransactionsPage::pr_dashboard()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void TransactionsPage::r_transactions()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
