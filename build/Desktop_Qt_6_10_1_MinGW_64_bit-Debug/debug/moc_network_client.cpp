/****************************************************************************
** Meta object code from reading C++ file 'network_client.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/client/network_client.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'network_client.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.10.1. It"
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
struct qt_meta_tag_ZN13NetworkClientE_t {};
} // unnamed namespace

template <> constexpr inline auto NetworkClient::qt_create_metaobjectdata<qt_meta_tag_ZN13NetworkClientE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "NetworkClient",
        "connected",
        "",
        "disconnected",
        "connectionError",
        "error",
        "loginResponse",
        "int32_t",
        "status",
        "message",
        "uint32_t",
        "userId",
        "token",
        "registerResponse",
        "depositResponse",
        "int64_t",
        "newBalance",
        "redeemResponse",
        "createRoomResponse",
        "roomId",
        "joinRoomResponse",
        "listRoomsResponse",
        "uint16_t",
        "count",
        "QList<RoomInfo>",
        "rooms",
        "bidResponse",
        "buyNowResponse",
        "viewItemsResponse",
        "QList<ItemInfo>",
        "items",
        "viewHistoryResponse",
        "bidNotify",
        "itemId",
        "newPrice",
        "winnerId",
        "winnerName",
        "chatNotify",
        "senderId",
        "senderName",
        "text",
        "timerUpdate",
        "remainingSec",
        "itemSold",
        "finalPrice",
        "onConnected",
        "onDisconnected",
        "onReadyRead",
        "onError",
        "QAbstractSocket::SocketError",
        "socketError"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'connected'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'disconnected'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'connectionError'
        QtMocHelpers::SignalData<void(const QString &)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 5 },
        }}),
        // Signal 'loginResponse'
        QtMocHelpers::SignalData<void(int32_t, const QString &, uint32_t, const QString &)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 7, 8 }, { QMetaType::QString, 9 }, { 0x80000000 | 10, 11 }, { QMetaType::QString, 12 },
        }}),
        // Signal 'registerResponse'
        QtMocHelpers::SignalData<void(int32_t, const QString &)>(13, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 7, 8 }, { QMetaType::QString, 9 },
        }}),
        // Signal 'depositResponse'
        QtMocHelpers::SignalData<void(int32_t, const QString &, int64_t)>(14, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 7, 8 }, { QMetaType::QString, 9 }, { 0x80000000 | 15, 16 },
        }}),
        // Signal 'redeemResponse'
        QtMocHelpers::SignalData<void(int32_t, const QString &, int64_t)>(17, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 7, 8 }, { QMetaType::QString, 9 }, { 0x80000000 | 15, 16 },
        }}),
        // Signal 'createRoomResponse'
        QtMocHelpers::SignalData<void(int32_t, const QString &, uint32_t)>(18, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 7, 8 }, { QMetaType::QString, 9 }, { 0x80000000 | 10, 19 },
        }}),
        // Signal 'joinRoomResponse'
        QtMocHelpers::SignalData<void(int32_t, const QString &)>(20, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 7, 8 }, { QMetaType::QString, 9 },
        }}),
        // Signal 'listRoomsResponse'
        QtMocHelpers::SignalData<void(int32_t, const QString &, uint16_t, const QVector<RoomInfo> &)>(21, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 7, 8 }, { QMetaType::QString, 9 }, { 0x80000000 | 22, 23 }, { 0x80000000 | 24, 25 },
        }}),
        // Signal 'bidResponse'
        QtMocHelpers::SignalData<void(int32_t, const QString &)>(26, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 7, 8 }, { QMetaType::QString, 9 },
        }}),
        // Signal 'buyNowResponse'
        QtMocHelpers::SignalData<void(int32_t, const QString &)>(27, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 7, 8 }, { QMetaType::QString, 9 },
        }}),
        // Signal 'viewItemsResponse'
        QtMocHelpers::SignalData<void(int32_t, const QString &, uint16_t, const QVector<ItemInfo> &)>(28, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 7, 8 }, { QMetaType::QString, 9 }, { 0x80000000 | 22, 23 }, { 0x80000000 | 29, 30 },
        }}),
        // Signal 'viewHistoryResponse'
        QtMocHelpers::SignalData<void(int32_t, const QString &, uint16_t)>(31, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 7, 8 }, { QMetaType::QString, 9 }, { 0x80000000 | 22, 23 },
        }}),
        // Signal 'bidNotify'
        QtMocHelpers::SignalData<void(uint32_t, int64_t, uint32_t, const QString &)>(32, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 10, 33 }, { 0x80000000 | 15, 34 }, { 0x80000000 | 10, 35 }, { QMetaType::QString, 36 },
        }}),
        // Signal 'chatNotify'
        QtMocHelpers::SignalData<void(uint32_t, const QString &, const QString &)>(37, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 10, 38 }, { QMetaType::QString, 39 }, { QMetaType::QString, 40 },
        }}),
        // Signal 'timerUpdate'
        QtMocHelpers::SignalData<void(uint32_t, uint32_t)>(41, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 10, 33 }, { 0x80000000 | 10, 42 },
        }}),
        // Signal 'itemSold'
        QtMocHelpers::SignalData<void(uint32_t, uint32_t, const QString &, int64_t)>(43, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 10, 33 }, { 0x80000000 | 10, 35 }, { QMetaType::QString, 36 }, { 0x80000000 | 15, 44 },
        }}),
        // Slot 'onConnected'
        QtMocHelpers::SlotData<void()>(45, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onDisconnected'
        QtMocHelpers::SlotData<void()>(46, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onReadyRead'
        QtMocHelpers::SlotData<void()>(47, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onError'
        QtMocHelpers::SlotData<void(QAbstractSocket::SocketError)>(48, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 49, 50 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<NetworkClient, qt_meta_tag_ZN13NetworkClientE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject NetworkClient::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13NetworkClientE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13NetworkClientE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN13NetworkClientE_t>.metaTypes,
    nullptr
} };

void NetworkClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<NetworkClient *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->connected(); break;
        case 1: _t->disconnected(); break;
        case 2: _t->connectionError((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->loginResponse((*reinterpret_cast<std::add_pointer_t<int32_t>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<uint32_t>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[4]))); break;
        case 4: _t->registerResponse((*reinterpret_cast<std::add_pointer_t<int32_t>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 5: _t->depositResponse((*reinterpret_cast<std::add_pointer_t<int32_t>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<int64_t>>(_a[3]))); break;
        case 6: _t->redeemResponse((*reinterpret_cast<std::add_pointer_t<int32_t>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<int64_t>>(_a[3]))); break;
        case 7: _t->createRoomResponse((*reinterpret_cast<std::add_pointer_t<int32_t>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<uint32_t>>(_a[3]))); break;
        case 8: _t->joinRoomResponse((*reinterpret_cast<std::add_pointer_t<int32_t>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 9: _t->listRoomsResponse((*reinterpret_cast<std::add_pointer_t<int32_t>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<uint16_t>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<QList<RoomInfo>>>(_a[4]))); break;
        case 10: _t->bidResponse((*reinterpret_cast<std::add_pointer_t<int32_t>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 11: _t->buyNowResponse((*reinterpret_cast<std::add_pointer_t<int32_t>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 12: _t->viewItemsResponse((*reinterpret_cast<std::add_pointer_t<int32_t>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<uint16_t>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<QList<ItemInfo>>>(_a[4]))); break;
        case 13: _t->viewHistoryResponse((*reinterpret_cast<std::add_pointer_t<int32_t>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<uint16_t>>(_a[3]))); break;
        case 14: _t->bidNotify((*reinterpret_cast<std::add_pointer_t<uint32_t>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int64_t>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<uint32_t>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[4]))); break;
        case 15: _t->chatNotify((*reinterpret_cast<std::add_pointer_t<uint32_t>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[3]))); break;
        case 16: _t->timerUpdate((*reinterpret_cast<std::add_pointer_t<uint32_t>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<uint32_t>>(_a[2]))); break;
        case 17: _t->itemSold((*reinterpret_cast<std::add_pointer_t<uint32_t>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<uint32_t>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<int64_t>>(_a[4]))); break;
        case 18: _t->onConnected(); break;
        case 19: _t->onDisconnected(); break;
        case 20: _t->onReadyRead(); break;
        case 21: _t->onError((*reinterpret_cast<std::add_pointer_t<QAbstractSocket::SocketError>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 21:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (NetworkClient::*)()>(_a, &NetworkClient::connected, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (NetworkClient::*)()>(_a, &NetworkClient::disconnected, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (NetworkClient::*)(const QString & )>(_a, &NetworkClient::connectionError, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (NetworkClient::*)(int32_t , const QString & , uint32_t , const QString & )>(_a, &NetworkClient::loginResponse, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (NetworkClient::*)(int32_t , const QString & )>(_a, &NetworkClient::registerResponse, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (NetworkClient::*)(int32_t , const QString & , int64_t )>(_a, &NetworkClient::depositResponse, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (NetworkClient::*)(int32_t , const QString & , int64_t )>(_a, &NetworkClient::redeemResponse, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (NetworkClient::*)(int32_t , const QString & , uint32_t )>(_a, &NetworkClient::createRoomResponse, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (NetworkClient::*)(int32_t , const QString & )>(_a, &NetworkClient::joinRoomResponse, 8))
            return;
        if (QtMocHelpers::indexOfMethod<void (NetworkClient::*)(int32_t , const QString & , uint16_t , const QVector<RoomInfo> & )>(_a, &NetworkClient::listRoomsResponse, 9))
            return;
        if (QtMocHelpers::indexOfMethod<void (NetworkClient::*)(int32_t , const QString & )>(_a, &NetworkClient::bidResponse, 10))
            return;
        if (QtMocHelpers::indexOfMethod<void (NetworkClient::*)(int32_t , const QString & )>(_a, &NetworkClient::buyNowResponse, 11))
            return;
        if (QtMocHelpers::indexOfMethod<void (NetworkClient::*)(int32_t , const QString & , uint16_t , const QVector<ItemInfo> & )>(_a, &NetworkClient::viewItemsResponse, 12))
            return;
        if (QtMocHelpers::indexOfMethod<void (NetworkClient::*)(int32_t , const QString & , uint16_t )>(_a, &NetworkClient::viewHistoryResponse, 13))
            return;
        if (QtMocHelpers::indexOfMethod<void (NetworkClient::*)(uint32_t , int64_t , uint32_t , const QString & )>(_a, &NetworkClient::bidNotify, 14))
            return;
        if (QtMocHelpers::indexOfMethod<void (NetworkClient::*)(uint32_t , const QString & , const QString & )>(_a, &NetworkClient::chatNotify, 15))
            return;
        if (QtMocHelpers::indexOfMethod<void (NetworkClient::*)(uint32_t , uint32_t )>(_a, &NetworkClient::timerUpdate, 16))
            return;
        if (QtMocHelpers::indexOfMethod<void (NetworkClient::*)(uint32_t , uint32_t , const QString & , int64_t )>(_a, &NetworkClient::itemSold, 17))
            return;
    }
}

const QMetaObject *NetworkClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NetworkClient::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13NetworkClientE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int NetworkClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    }
    return _id;
}

// SIGNAL 0
void NetworkClient::connected()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void NetworkClient::disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void NetworkClient::connectionError(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void NetworkClient::loginResponse(int32_t _t1, const QString & _t2, uint32_t _t3, const QString & _t4)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1, _t2, _t3, _t4);
}

// SIGNAL 4
void NetworkClient::registerResponse(int32_t _t1, const QString & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1, _t2);
}

// SIGNAL 5
void NetworkClient::depositResponse(int32_t _t1, const QString & _t2, int64_t _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1, _t2, _t3);
}

// SIGNAL 6
void NetworkClient::redeemResponse(int32_t _t1, const QString & _t2, int64_t _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 6, nullptr, _t1, _t2, _t3);
}

// SIGNAL 7
void NetworkClient::createRoomResponse(int32_t _t1, const QString & _t2, uint32_t _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 7, nullptr, _t1, _t2, _t3);
}

// SIGNAL 8
void NetworkClient::joinRoomResponse(int32_t _t1, const QString & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 8, nullptr, _t1, _t2);
}

// SIGNAL 9
void NetworkClient::listRoomsResponse(int32_t _t1, const QString & _t2, uint16_t _t3, const QVector<RoomInfo> & _t4)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 9, nullptr, _t1, _t2, _t3, _t4);
}

// SIGNAL 10
void NetworkClient::bidResponse(int32_t _t1, const QString & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 10, nullptr, _t1, _t2);
}

// SIGNAL 11
void NetworkClient::buyNowResponse(int32_t _t1, const QString & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 11, nullptr, _t1, _t2);
}

// SIGNAL 12
void NetworkClient::viewItemsResponse(int32_t _t1, const QString & _t2, uint16_t _t3, const QVector<ItemInfo> & _t4)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 12, nullptr, _t1, _t2, _t3, _t4);
}

// SIGNAL 13
void NetworkClient::viewHistoryResponse(int32_t _t1, const QString & _t2, uint16_t _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 13, nullptr, _t1, _t2, _t3);
}

// SIGNAL 14
void NetworkClient::bidNotify(uint32_t _t1, int64_t _t2, uint32_t _t3, const QString & _t4)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 14, nullptr, _t1, _t2, _t3, _t4);
}

// SIGNAL 15
void NetworkClient::chatNotify(uint32_t _t1, const QString & _t2, const QString & _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 15, nullptr, _t1, _t2, _t3);
}

// SIGNAL 16
void NetworkClient::timerUpdate(uint32_t _t1, uint32_t _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 16, nullptr, _t1, _t2);
}

// SIGNAL 17
void NetworkClient::itemSold(uint32_t _t1, uint32_t _t2, const QString & _t3, int64_t _t4)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 17, nullptr, _t1, _t2, _t3, _t4);
}
QT_WARNING_POP
