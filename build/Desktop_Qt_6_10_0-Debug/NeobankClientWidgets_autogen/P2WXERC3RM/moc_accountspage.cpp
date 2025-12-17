/****************************************************************************
** Meta object code from reading C++ file 'accountspage.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../pages/accountspage.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'accountspage.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN12AccountsPageE_t {};
} // unnamed namespace

template <> constexpr inline auto AccountsPage::qt_create_metaobjectdata<qt_meta_tag_ZN12AccountsPageE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "AccountsPage",
        "pr_dashboard",
        "",
        "r_accounts",
        "r_transferRequested",
        "fromAccountId",
        "to",
        "amount",
        "Enums::Currency",
        "currency",
        "description",
        "r_createAccount",
        "curr",
        "r_testCreditRequested",
        "accountId",
        "onAccountsUpdated",
        "QList<AccountInfo>",
        "accounts",
        "onAccountsFailed",
        "reason"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'pr_dashboard'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'r_accounts'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'r_transferRequested'
        QtMocHelpers::SignalData<void(const QString &, const QString &, const QString &, const Enums::Currency &, const QString &)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 5 }, { QMetaType::QString, 6 }, { QMetaType::QString, 7 }, { 0x80000000 | 8, 9 },
            { QMetaType::QString, 10 },
        }}),
        // Signal 'r_createAccount'
        QtMocHelpers::SignalData<void(Enums::Currency)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 8, 12 },
        }}),
        // Signal 'r_testCreditRequested'
        QtMocHelpers::SignalData<void(const QString &, const QString &)>(13, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 14 }, { QMetaType::QString, 7 },
        }}),
        // Slot 'onAccountsUpdated'
        QtMocHelpers::SlotData<void(const QList<AccountInfo> &)>(15, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 16, 17 },
        }}),
        // Slot 'onAccountsFailed'
        QtMocHelpers::SlotData<void(const QString &)>(18, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 19 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<AccountsPage, qt_meta_tag_ZN12AccountsPageE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject AccountsPage::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12AccountsPageE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12AccountsPageE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN12AccountsPageE_t>.metaTypes,
    nullptr
} };

void AccountsPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<AccountsPage *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->pr_dashboard(); break;
        case 1: _t->r_accounts(); break;
        case 2: _t->r_transferRequested((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<Enums::Currency>>(_a[4])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[5]))); break;
        case 3: _t->r_createAccount((*reinterpret_cast<std::add_pointer_t<Enums::Currency>>(_a[1]))); break;
        case 4: _t->r_testCreditRequested((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 5: _t->onAccountsUpdated((*reinterpret_cast<std::add_pointer_t<QList<AccountInfo>>>(_a[1]))); break;
        case 6: _t->onAccountsFailed((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (AccountsPage::*)()>(_a, &AccountsPage::pr_dashboard, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (AccountsPage::*)()>(_a, &AccountsPage::r_accounts, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (AccountsPage::*)(const QString & , const QString & , const QString & , const Enums::Currency & , const QString & )>(_a, &AccountsPage::r_transferRequested, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (AccountsPage::*)(Enums::Currency )>(_a, &AccountsPage::r_createAccount, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (AccountsPage::*)(const QString & , const QString & )>(_a, &AccountsPage::r_testCreditRequested, 4))
            return;
    }
}

const QMetaObject *AccountsPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AccountsPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12AccountsPageE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int AccountsPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void AccountsPage::pr_dashboard()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void AccountsPage::r_accounts()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void AccountsPage::r_transferRequested(const QString & _t1, const QString & _t2, const QString & _t3, const Enums::Currency & _t4, const QString & _t5)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1, _t2, _t3, _t4, _t5);
}

// SIGNAL 3
void AccountsPage::r_createAccount(Enums::Currency _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}

// SIGNAL 4
void AccountsPage::r_testCreditRequested(const QString & _t1, const QString & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1, _t2);
}
QT_WARNING_POP
