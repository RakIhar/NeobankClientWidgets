/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN10MainWindowE_t {};
} // unnamed namespace

template <> constexpr inline auto MainWindow::qt_create_metaobjectdata<qt_meta_tag_ZN10MainWindowE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "MainWindow",
        "onRequestConnect",
        "",
        "host",
        "port",
        "onRequestLogin",
        "username",
        "password",
        "onRequestRegistration",
        "RegData",
        "regData",
        "onRequestLogout",
        "onRequestAccountsList",
        "onRequestTransactionsList",
        "onRequestCreateTransaction",
        "fromAccountId",
        "to",
        "amount",
        "Enums::Currency",
        "currency",
        "description",
        "onRequestCreateAccount",
        "curr",
        "onRequestTestCredit",
        "accountId"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'onRequestConnect'
        QtMocHelpers::SlotData<void(QString, quint16)>(1, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 3 }, { QMetaType::UShort, 4 },
        }}),
        // Slot 'onRequestLogin'
        QtMocHelpers::SlotData<void(const QString &, const QString &)>(5, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 6 }, { QMetaType::QString, 7 },
        }}),
        // Slot 'onRequestRegistration'
        QtMocHelpers::SlotData<void(const RegData &)>(8, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 9, 10 },
        }}),
        // Slot 'onRequestLogout'
        QtMocHelpers::SlotData<void()>(11, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onRequestAccountsList'
        QtMocHelpers::SlotData<void()>(12, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onRequestTransactionsList'
        QtMocHelpers::SlotData<void()>(13, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onRequestCreateTransaction'
        QtMocHelpers::SlotData<void(const QString &, const QString &, const QString &, const Enums::Currency &, const QString &)>(14, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 15 }, { QMetaType::QString, 16 }, { QMetaType::QString, 17 }, { 0x80000000 | 18, 19 },
            { QMetaType::QString, 20 },
        }}),
        // Slot 'onRequestCreateAccount'
        QtMocHelpers::SlotData<void(const Enums::Currency)>(21, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 18, 22 },
        }}),
        // Slot 'onRequestTestCredit'
        QtMocHelpers::SlotData<void(const QString &, const QString &)>(23, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 24 }, { QMetaType::QString, 17 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<MainWindow, qt_meta_tag_ZN10MainWindowE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN10MainWindowE_t>.metaTypes,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<MainWindow *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->onRequestConnect((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<quint16>>(_a[2]))); break;
        case 1: _t->onRequestLogin((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 2: _t->onRequestRegistration((*reinterpret_cast<std::add_pointer_t<RegData>>(_a[1]))); break;
        case 3: _t->onRequestLogout(); break;
        case 4: _t->onRequestAccountsList(); break;
        case 5: _t->onRequestTransactionsList(); break;
        case 6: _t->onRequestCreateTransaction((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<Enums::Currency>>(_a[4])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[5]))); break;
        case 7: _t->onRequestCreateAccount((*reinterpret_cast<std::add_pointer_t<Enums::Currency>>(_a[1]))); break;
        case 8: _t->onRequestTestCredit((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.strings))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
