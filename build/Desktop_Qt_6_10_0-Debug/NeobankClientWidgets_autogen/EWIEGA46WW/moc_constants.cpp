/****************************************************************************
** Meta object code from reading C++ file 'constants.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../constants.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'constants.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN5EnumsE_t {};
} // unnamed namespace

template <> constexpr inline auto Enums::qt_create_metaobjectdata<qt_meta_tag_ZN5EnumsE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Enums",
        "Currency",
        "BYN",
        "RUB",
        "USD",
        "EUR",
        "GBP",
        "KZT",
        "UAH",
        "PLN",
        "CNY"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
        // enum 'Currency'
        QtMocHelpers::EnumData<enum Currency>(1, 1, QMC::EnumIsScoped).add({
            {    2, Currency::BYN },
            {    3, Currency::RUB },
            {    4, Currency::USD },
            {    5, Currency::EUR },
            {    6, Currency::GBP },
            {    7, Currency::KZT },
            {    8, Currency::UAH },
            {    9, Currency::PLN },
            {   10, Currency::CNY },
        }),
    };
    return QtMocHelpers::metaObjectData<Enums, qt_meta_tag_ZN5EnumsE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Enums::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN5EnumsE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN5EnumsE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN5EnumsE_t>.metaTypes,
    nullptr
} };

void Enums::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Enums *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *Enums::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Enums::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN5EnumsE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Enums::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
