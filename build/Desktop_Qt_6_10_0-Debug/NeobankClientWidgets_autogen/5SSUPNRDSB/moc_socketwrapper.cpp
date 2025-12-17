/****************************************************************************
** Meta object code from reading C++ file 'socketwrapper.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../network/socketwrapper.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'socketwrapper.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN13SocketWrapperE_t {};
} // unnamed namespace

template <> constexpr inline auto SocketWrapper::qt_create_metaobjectdata<qt_meta_tag_ZN13SocketWrapperE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "SocketWrapper",
        "connected",
        "",
        "disconnected",
        "sent",
        "errorOccurred",
        "msg",
        "received",
        "onReadyRead"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'connected'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'disconnected'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'sent'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'errorOccurred'
        QtMocHelpers::SignalData<void(const QString &)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 6 },
        }}),
        // Signal 'received'
        QtMocHelpers::SignalData<void(const QByteArray &)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QByteArray, 6 },
        }}),
        // Slot 'onReadyRead'
        QtMocHelpers::SlotData<void()>(8, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<SocketWrapper, qt_meta_tag_ZN13SocketWrapperE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject SocketWrapper::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13SocketWrapperE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13SocketWrapperE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN13SocketWrapperE_t>.metaTypes,
    nullptr
} };

void SocketWrapper::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<SocketWrapper *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->connected(); break;
        case 1: _t->disconnected(); break;
        case 2: _t->sent(); break;
        case 3: _t->errorOccurred((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->received((*reinterpret_cast<std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 5: _t->onReadyRead(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (SocketWrapper::*)()>(_a, &SocketWrapper::connected, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (SocketWrapper::*)()>(_a, &SocketWrapper::disconnected, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (SocketWrapper::*)()>(_a, &SocketWrapper::sent, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (SocketWrapper::*)(const QString & )>(_a, &SocketWrapper::errorOccurred, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (SocketWrapper::*)(const QByteArray & )>(_a, &SocketWrapper::received, 4))
            return;
    }
}

const QMetaObject *SocketWrapper::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SocketWrapper::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13SocketWrapperE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SocketWrapper::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void SocketWrapper::connected()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void SocketWrapper::disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void SocketWrapper::sent()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void SocketWrapper::errorOccurred(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}

// SIGNAL 4
void SocketWrapper::received(const QByteArray & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1);
}
QT_WARNING_POP
