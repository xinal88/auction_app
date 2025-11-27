/****************************************************************************
** Meta object code from reading C++ file 'main_window.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/client/main_window.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'main_window.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN10MainWindowE_t {};
} // unnamed namespace

template <> constexpr inline auto MainWindow::qt_create_metaobjectdata<qt_meta_tag_ZN10MainWindowE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "MainWindow",
        "onDepositClicked",
        "",
        "onRedeemClicked",
        "onViewHistoryClicked",
        "onDepositResponse",
        "int32_t",
        "status",
        "message",
        "int64_t",
        "newBalance",
        "onRedeemResponse",
        "onCreateRoomClicked",
        "onRefreshRoomsClicked",
        "onJoinRoomClicked",
        "onLeaveRoomClicked",
        "onRoomItemDoubleClicked",
        "QListWidgetItem*",
        "item",
        "onCreateRoomResponse",
        "uint32_t",
        "roomId",
        "onJoinRoomResponse",
        "onListRoomsResponse",
        "uint16_t",
        "count",
        "QList<RoomInfo>",
        "rooms",
        "onRefreshItemsClicked",
        "onBidClicked",
        "onBuyNowClicked",
        "onSendChatClicked",
        "onViewItemsResponse",
        "QList<ItemInfo>",
        "items",
        "onBidResponse",
        "onBuyNowResponse",
        "onBidNotify",
        "itemId",
        "newPrice",
        "winnerId",
        "winnerName",
        "onChatNotify",
        "senderId",
        "senderName",
        "text",
        "onTimerUpdate",
        "remainingSec",
        "onDisconnected",
        "onLogoutClicked"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'onDepositClicked'
        QtMocHelpers::SlotData<void()>(1, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onRedeemClicked'
        QtMocHelpers::SlotData<void()>(3, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onViewHistoryClicked'
        QtMocHelpers::SlotData<void()>(4, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onDepositResponse'
        QtMocHelpers::SlotData<void(int32_t, const QString &, int64_t)>(5, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 6, 7 }, { QMetaType::QString, 8 }, { 0x80000000 | 9, 10 },
        }}),
        // Slot 'onRedeemResponse'
        QtMocHelpers::SlotData<void(int32_t, const QString &, int64_t)>(11, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 6, 7 }, { QMetaType::QString, 8 }, { 0x80000000 | 9, 10 },
        }}),
        // Slot 'onCreateRoomClicked'
        QtMocHelpers::SlotData<void()>(12, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onRefreshRoomsClicked'
        QtMocHelpers::SlotData<void()>(13, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onJoinRoomClicked'
        QtMocHelpers::SlotData<void()>(14, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onLeaveRoomClicked'
        QtMocHelpers::SlotData<void()>(15, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onRoomItemDoubleClicked'
        QtMocHelpers::SlotData<void(QListWidgetItem *)>(16, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 17, 18 },
        }}),
        // Slot 'onCreateRoomResponse'
        QtMocHelpers::SlotData<void(int32_t, const QString &, uint32_t)>(19, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 6, 7 }, { QMetaType::QString, 8 }, { 0x80000000 | 20, 21 },
        }}),
        // Slot 'onJoinRoomResponse'
        QtMocHelpers::SlotData<void(int32_t, const QString &)>(22, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 6, 7 }, { QMetaType::QString, 8 },
        }}),
        // Slot 'onListRoomsResponse'
        QtMocHelpers::SlotData<void(int32_t, const QString &, uint16_t, const QVector<RoomInfo> &)>(23, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 6, 7 }, { QMetaType::QString, 8 }, { 0x80000000 | 24, 25 }, { 0x80000000 | 26, 27 },
        }}),
        // Slot 'onRefreshItemsClicked'
        QtMocHelpers::SlotData<void()>(28, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onBidClicked'
        QtMocHelpers::SlotData<void()>(29, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onBuyNowClicked'
        QtMocHelpers::SlotData<void()>(30, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onSendChatClicked'
        QtMocHelpers::SlotData<void()>(31, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onViewItemsResponse'
        QtMocHelpers::SlotData<void(int32_t, const QString &, uint16_t, const QVector<ItemInfo> &)>(32, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 6, 7 }, { QMetaType::QString, 8 }, { 0x80000000 | 24, 25 }, { 0x80000000 | 33, 34 },
        }}),
        // Slot 'onBidResponse'
        QtMocHelpers::SlotData<void(int32_t, const QString &)>(35, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 6, 7 }, { QMetaType::QString, 8 },
        }}),
        // Slot 'onBuyNowResponse'
        QtMocHelpers::SlotData<void(int32_t, const QString &)>(36, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 6, 7 }, { QMetaType::QString, 8 },
        }}),
        // Slot 'onBidNotify'
        QtMocHelpers::SlotData<void(uint32_t, int64_t, uint32_t, const QString &)>(37, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 20, 38 }, { 0x80000000 | 9, 39 }, { 0x80000000 | 20, 40 }, { QMetaType::QString, 41 },
        }}),
        // Slot 'onChatNotify'
        QtMocHelpers::SlotData<void(uint32_t, const QString &, const QString &)>(42, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 20, 43 }, { QMetaType::QString, 44 }, { QMetaType::QString, 45 },
        }}),
        // Slot 'onTimerUpdate'
        QtMocHelpers::SlotData<void(uint32_t, uint32_t)>(46, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 20, 38 }, { 0x80000000 | 20, 47 },
        }}),
        // Slot 'onDisconnected'
        QtMocHelpers::SlotData<void()>(48, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onLogoutClicked'
        QtMocHelpers::SlotData<void()>(49, 2, QMC::AccessPrivate, QMetaType::Void),
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
        case 0: _t->onDepositClicked(); break;
        case 1: _t->onRedeemClicked(); break;
        case 2: _t->onViewHistoryClicked(); break;
        case 3: _t->onDepositResponse((*reinterpret_cast<std::add_pointer_t<int32_t>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<int64_t>>(_a[3]))); break;
        case 4: _t->onRedeemResponse((*reinterpret_cast<std::add_pointer_t<int32_t>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<int64_t>>(_a[3]))); break;
        case 5: _t->onCreateRoomClicked(); break;
        case 6: _t->onRefreshRoomsClicked(); break;
        case 7: _t->onJoinRoomClicked(); break;
        case 8: _t->onLeaveRoomClicked(); break;
        case 9: _t->onRoomItemDoubleClicked((*reinterpret_cast<std::add_pointer_t<QListWidgetItem*>>(_a[1]))); break;
        case 10: _t->onCreateRoomResponse((*reinterpret_cast<std::add_pointer_t<int32_t>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<uint32_t>>(_a[3]))); break;
        case 11: _t->onJoinRoomResponse((*reinterpret_cast<std::add_pointer_t<int32_t>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 12: _t->onListRoomsResponse((*reinterpret_cast<std::add_pointer_t<int32_t>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<uint16_t>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<QList<RoomInfo>>>(_a[4]))); break;
        case 13: _t->onRefreshItemsClicked(); break;
        case 14: _t->onBidClicked(); break;
        case 15: _t->onBuyNowClicked(); break;
        case 16: _t->onSendChatClicked(); break;
        case 17: _t->onViewItemsResponse((*reinterpret_cast<std::add_pointer_t<int32_t>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<uint16_t>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<QList<ItemInfo>>>(_a[4]))); break;
        case 18: _t->onBidResponse((*reinterpret_cast<std::add_pointer_t<int32_t>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 19: _t->onBuyNowResponse((*reinterpret_cast<std::add_pointer_t<int32_t>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 20: _t->onBidNotify((*reinterpret_cast<std::add_pointer_t<uint32_t>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int64_t>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<uint32_t>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[4]))); break;
        case 21: _t->onChatNotify((*reinterpret_cast<std::add_pointer_t<uint32_t>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[3]))); break;
        case 22: _t->onTimerUpdate((*reinterpret_cast<std::add_pointer_t<uint32_t>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<uint32_t>>(_a[2]))); break;
        case 23: _t->onDisconnected(); break;
        case 24: _t->onLogoutClicked(); break;
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
        if (_id < 25)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 25;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 25)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 25;
    }
    return _id;
}
QT_WARNING_POP
