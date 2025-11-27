#include "network_client.h"
#include <QDataStream>
#include <QDebug>
#include <cstring>

NetworkClient::NetworkClient(QObject *parent)
    : QObject(parent)
    , socket(new QTcpSocket(this))
    , nextRequestId(1)
    , currentUserId(0)
    , currentRoomId(0)
{
    connect(socket, &QTcpSocket::connected, this, &NetworkClient::onConnected);
    connect(socket, &QTcpSocket::disconnected, this, &NetworkClient::onDisconnected);
    connect(socket, &QTcpSocket::readyRead, this, &NetworkClient::onReadyRead);
#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 0)
    connect(socket, &QTcpSocket::errorOccurred, this, &NetworkClient::onError);
#else
    connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::error),
            this, &NetworkClient::onError);
#endif
}

NetworkClient::~NetworkClient() {
    disconnectFromServer();
}

bool NetworkClient::connectToServer(const QString &host, quint16 port) {
    if (socket->state() == QAbstractSocket::ConnectedState) {
        return true;
    }
    socket->connectToHost(host, port);
    return socket->waitForConnected(3000);
}

void NetworkClient::disconnectFromServer() {
    if (socket->state() == QAbstractSocket::ConnectedState) {
        socket->disconnectFromHost();
    }
}

bool NetworkClient::isConnected() const {
    return socket->state() == QAbstractSocket::ConnectedState;
}

bool NetworkClient::sendMessage(const Message &msg) {
    if (!isConnected()) {
        return false;
    }

    // Send header
    qint64 written = socket->write(reinterpret_cast<const char*>(&msg.header), sizeof(MessageHeader));
    if (written != sizeof(MessageHeader)) {
        return false;
    }

    // Send payload if exists
    if (msg.header.payload_length > 0) {
        written = socket->write(msg.payload, msg.header.payload_length);
        if (written != msg.header.payload_length) {
            return false;
        }
    }

    socket->flush();
    return true;
}

bool NetworkClient::sendLogin(const QString &username, const QString &password) {
    Message msg;
    msg.header.type = LOGIN_REQ;
    msg.header.request_id = getNextRequestId();
    msg.header.payload_length = sizeof(LoginReq);

    LoginReq req;
    memset(&req, 0, sizeof(LoginReq));
    strncpy(req.username, username.toUtf8().constData(), sizeof(req.username) - 1);
    strncpy(req.password, password.toUtf8().constData(), sizeof(req.password) - 1);

    memcpy(msg.payload, &req, sizeof(LoginReq));
    return sendMessage(msg);
}

bool NetworkClient::sendRegister(const QString &username, const QString &password,
                                 const QString &email, const QString &bankAccount, const QString &bankName) {
    Message msg;
    msg.header.type = REGISTER_REQ;
    msg.header.request_id = getNextRequestId();
    msg.header.payload_length = sizeof(RegisterReq);

    RegisterReq req;
    memset(&req, 0, sizeof(RegisterReq));
    strncpy(req.username, username.toUtf8().constData(), sizeof(req.username) - 1);
    strncpy(req.password, password.toUtf8().constData(), sizeof(req.password) - 1);
    strncpy(req.email, email.toUtf8().constData(), sizeof(req.email) - 1);
    strncpy(req.bank_account, bankAccount.toUtf8().constData(), sizeof(req.bank_account) - 1);
    strncpy(req.bank_name, bankName.toUtf8().constData(), sizeof(req.bank_name) - 1);

    memcpy(msg.payload, &req, sizeof(RegisterReq));
    return sendMessage(msg);
}

bool NetworkClient::sendDeposit(int64_t amount) {
    Message msg;
    msg.header.type = DEPOSIT_REQ;
    msg.header.request_id = getNextRequestId();
    msg.header.payload_length = sizeof(MoneyReq);

    MoneyReq req;
    req.amount = amount;

    memcpy(msg.payload, &req, sizeof(MoneyReq));
    return sendMessage(msg);
}

bool NetworkClient::sendRedeem(int64_t amount) {
    Message msg;
    msg.header.type = REDEEM_REQ;
    msg.header.request_id = getNextRequestId();
    msg.header.payload_length = sizeof(MoneyReq);

    MoneyReq req;
    req.amount = amount;

    memcpy(msg.payload, &req, sizeof(MoneyReq));
    return sendMessage(msg);
}

bool NetworkClient::sendCreateRoom(const QString &name, const QString &description) {
    Message msg;
    msg.header.type = CREATE_ROOM_REQ;
    msg.header.request_id = getNextRequestId();
    msg.header.payload_length = sizeof(CreateRoomReq);

    CreateRoomReq req;
    memset(&req, 0, sizeof(CreateRoomReq));
    strncpy(req.name, name.toUtf8().constData(), sizeof(req.name) - 1);
    strncpy(req.description, description.toUtf8().constData(), sizeof(req.description) - 1);

    memcpy(msg.payload, &req, sizeof(CreateRoomReq));
    return sendMessage(msg);
}

bool NetworkClient::sendJoinRoom(uint32_t roomId) {
    Message msg;
    msg.header.type = JOIN_ROOM_REQ;
    msg.header.request_id = getNextRequestId();
    msg.header.payload_length = sizeof(JoinRoomReq);

    JoinRoomReq req;
    req.room_id = roomId;

    memcpy(msg.payload, &req, sizeof(JoinRoomReq));
    return sendMessage(msg);
}

bool NetworkClient::sendLeaveRoom() {
    Message msg;
    msg.header.type = LEAVE_ROOM_REQ;
    msg.header.request_id = getNextRequestId();
    msg.header.payload_length = 0;

    return sendMessage(msg);
}

bool NetworkClient::sendListRooms(const QString &query) {
    Message msg;
    msg.header.type = LIST_ROOMS_REQ;
    msg.header.request_id = getNextRequestId();
    msg.header.payload_length = sizeof(ListRoomsReq);

    ListRoomsReq req;
    memset(&req, 0, sizeof(ListRoomsReq));
    strncpy(req.query, query.toUtf8().constData(), sizeof(req.query) - 1);

    memcpy(msg.payload, &req, sizeof(ListRoomsReq));
    return sendMessage(msg);
}

bool NetworkClient::sendBid(uint32_t itemId, int64_t bidAmount) {
    Message msg;
    msg.header.type = BID_REQ;
    msg.header.request_id = getNextRequestId();
    msg.header.payload_length = sizeof(BidReq);

    BidReq req;
    req.item_id = itemId;
    req.bid_amount = bidAmount;

    memcpy(msg.payload, &req, sizeof(BidReq));
    return sendMessage(msg);
}

bool NetworkClient::sendBuyNow(uint32_t itemId) {
    Message msg;
    msg.header.type = BUY_NOW_REQ;
    msg.header.request_id = getNextRequestId();
    msg.header.payload_length = sizeof(BuyNowReq);

    BuyNowReq req;
    req.item_id = itemId;

    memcpy(msg.payload, &req, sizeof(BuyNowReq));
    return sendMessage(msg);
}

bool NetworkClient::sendChat(const QString &text, uint32_t roomId) {
    Message msg;
    msg.header.type = CHAT_REQ;
    msg.header.request_id = getNextRequestId();
    msg.header.payload_length = sizeof(ChatReq);

    ChatReq req;
    memset(&req, 0, sizeof(ChatReq));
    strncpy(req.text, text.toUtf8().constData(), sizeof(req.text) - 1);
    req.user_id = currentUserId;
    req.room_id = roomId;

    memcpy(msg.payload, &req, sizeof(ChatReq));
    return sendMessage(msg);
}

bool NetworkClient::sendViewItems() {
    Message msg;
    msg.header.type = VIEW_ITEMS_REQ;
    msg.header.request_id = getNextRequestId();
    msg.header.payload_length = 0;

    return sendMessage(msg);
}

bool NetworkClient::sendViewHistory() {
    Message msg;
    msg.header.type = VIEW_HISTORY_REQ;
    msg.header.request_id = getNextRequestId();
    msg.header.payload_length = 0;

    return sendMessage(msg);
}

void NetworkClient::onConnected() {
    qDebug() << "Connected to server";
    emit connected();
}

void NetworkClient::onDisconnected() {
    qDebug() << "Disconnected from server";
    emit disconnected();
}

void NetworkClient::onReadyRead() {
    receiveBuffer.append(socket->readAll());

    while (receiveBuffer.size() >= (int)sizeof(MessageHeader)) {
        MessageHeader header;
        memcpy(&header, receiveBuffer.constData(), sizeof(MessageHeader));

        int totalSize = sizeof(MessageHeader) + header.payload_length;
        if (receiveBuffer.size() < totalSize) {
            break; // Wait for more data
        }

        Message msg;
        msg.header = header;
        if (header.payload_length > 0) {
            memcpy(msg.payload, receiveBuffer.constData() + sizeof(MessageHeader), header.payload_length);
        }

        receiveBuffer.remove(0, totalSize);
        processMessage(msg);
    }
}

void NetworkClient::onError(QAbstractSocket::SocketError socketError) {
    QString errorMsg = socket->errorString();
    qDebug() << "Socket error:" << errorMsg;
    emit connectionError(errorMsg);
}

void NetworkClient::processMessage(const Message &msg) {
    switch (msg.header.type) {
        case LOGIN_RES:
            handleLoginResponse(msg.payload, msg.header.payload_length);
            break;
        case REGISTER_RES:
            handleRegisterResponse(msg.payload, msg.header.payload_length);
            break;
        case DEPOSIT_RES:
            handleDepositResponse(msg.payload, msg.header.payload_length);
            break;
        case REDEEM_RES:
            handleRedeemResponse(msg.payload, msg.header.payload_length);
            break;
        case CREATE_ROOM_RES:
            handleCreateRoomResponse(msg.payload, msg.header.payload_length);
            break;
        case JOIN_ROOM_RES:
            handleJoinRoomResponse(msg.payload, msg.header.payload_length);
            break;
        case LIST_ROOMS_RES:
            handleListRoomsResponse(msg.payload, msg.header.payload_length);
            break;
        case BID_RES:
            handleBidResponse(msg.payload, msg.header.payload_length);
            break;
        case BUY_NOW_RES:
            handleBuyNowResponse(msg.payload, msg.header.payload_length);
            break;
        case VIEW_ITEMS_RES:
            handleViewItemsResponse(msg.payload, msg.header.payload_length);
            break;
        case BID_NOTIFY:
            handleBidNotify(msg.payload, msg.header.payload_length);
            break;
        case CHAT_NOTIFY:
            handleChatNotify(msg.payload, msg.header.payload_length);
            break;
        case TIMER_UPDATE:
            handleTimerUpdate(msg.payload, msg.header.payload_length);
            break;
        default:
            qDebug() << "Unknown message type:" << msg.header.type;
    }
}

void NetworkClient::handleLoginResponse(const char *payload, uint32_t length) {
    if (length < sizeof(LoginRes)) return;
    
    LoginRes res;
    memcpy(&res, payload, sizeof(LoginRes));
    
    if (res.status == 1) {
        currentUserId = res.user_id;
        sessionToken = QString::fromUtf8(res.session_token);
    }
    
    emit loginResponse(res.status, QString::fromUtf8(res.message), res.user_id, QString::fromUtf8(res.session_token));
}

void NetworkClient::handleRegisterResponse(const char *payload, uint32_t length) {
    if (length < sizeof(RegisterRes)) return;
    
    RegisterRes res;
    memcpy(&res, payload, sizeof(RegisterRes));
    
    emit registerResponse(res.status, QString::fromUtf8(res.message));
}

void NetworkClient::handleDepositResponse(const char *payload, uint32_t length) {
    if (length < sizeof(MoneyRes)) return;
    
    MoneyRes res;
    memcpy(&res, payload, sizeof(MoneyRes));
    
    emit depositResponse(res.status, QString::fromUtf8(res.message), res.new_balance);
}

void NetworkClient::handleRedeemResponse(const char *payload, uint32_t length) {
    if (length < sizeof(MoneyRes)) return;
    
    MoneyRes res;
    memcpy(&res, payload, sizeof(MoneyRes));
    
    emit redeemResponse(res.status, QString::fromUtf8(res.message), res.new_balance);
}

void NetworkClient::handleCreateRoomResponse(const char *payload, uint32_t length) {
    if (length < sizeof(CreateRoomRes)) return;
    
    CreateRoomRes res;
    memcpy(&res, payload, sizeof(CreateRoomRes));
    
    emit createRoomResponse(res.status, QString::fromUtf8(res.message), res.room_id);
}

void NetworkClient::handleJoinRoomResponse(const char *payload, uint32_t length) {
    if (length < sizeof(JoinRoomRes)) return;
    
    JoinRoomRes res;
    memcpy(&res, payload, sizeof(JoinRoomRes));
    
    emit joinRoomResponse(res.status, QString::fromUtf8(res.message));
}

void NetworkClient::handleListRoomsResponse(const char *payload, uint32_t length) {
    if (length < sizeof(ListRoomsRes)) return;
    
    ListRoomsRes res;
    memcpy(&res, payload, sizeof(ListRoomsRes));
    
    QVector<RoomInfo> rooms;
    const char *ptr = payload + sizeof(ListRoomsRes);
    for (int i = 0; i < res.count && ptr + sizeof(RoomInfo) <= payload + length; i++) {
        RoomInfo room;
        memcpy(&room, ptr, sizeof(RoomInfo));
        rooms.append(room);
        ptr += sizeof(RoomInfo);
    }
    
    emit listRoomsResponse(res.status, QString::fromUtf8(res.message), res.count, rooms);
}

void NetworkClient::handleBidResponse(const char *payload, uint32_t length) {
    if (length < sizeof(BidRes)) return;
    
    BidRes res;
    memcpy(&res, payload, sizeof(BidRes));
    
    emit bidResponse(res.status, QString::fromUtf8(res.message));
}

void NetworkClient::handleBuyNowResponse(const char *payload, uint32_t length) {
    if (length < sizeof(BuyNowRes)) return;
    
    BuyNowRes res;
    memcpy(&res, payload, sizeof(BuyNowRes));
    
    emit buyNowResponse(res.status, QString::fromUtf8(res.message));
}

void NetworkClient::handleViewItemsResponse(const char *payload, uint32_t length) {
    if (length < sizeof(ViewItemsRes)) return;
    
    ViewItemsRes res;
    memcpy(&res, payload, sizeof(ViewItemsRes));
    
    QVector<ItemInfo> items;
    const char *ptr = payload + sizeof(ViewItemsRes);
    for (int i = 0; i < res.count && ptr + sizeof(ItemInfo) <= payload + length; i++) {
        ItemInfo item;
        memcpy(&item, ptr, sizeof(ItemInfo));
        items.append(item);
        ptr += sizeof(ItemInfo);
    }
    
    emit viewItemsResponse(res.status, QString::fromUtf8(res.message), res.count, items);
}

void NetworkClient::handleBidNotify(const char *payload, uint32_t length) {
    if (length < sizeof(BidNotify)) return;
    
    BidNotify notify;
    memcpy(&notify, payload, sizeof(BidNotify));
    
    emit bidNotify(notify.item_id, notify.new_price, notify.winner_id, QString::fromUtf8(notify.winner_name));
}

void NetworkClient::handleChatNotify(const char *payload, uint32_t length) {
    if (length < sizeof(ChatNotify)) return;
    
    ChatNotify notify;
    memcpy(&notify, payload, sizeof(ChatNotify));
    
    emit chatNotify(notify.sender_id, QString::fromUtf8(notify.sender_name), QString::fromUtf8(notify.text));
}

void NetworkClient::handleTimerUpdate(const char *payload, uint32_t length) {
    if (length < sizeof(TimerUpdate)) return;
    
    TimerUpdate update;
    memcpy(&update, payload, sizeof(TimerUpdate));
    
    emit timerUpdate(update.item_id, update.remaining_sec);
}

void NetworkClient::handleItemSold(const char *payload, uint32_t length) {
    if (length < sizeof(ItemSold)) return;
    
    ItemSold sold;
    memcpy(&sold, payload, sizeof(ItemSold));
    
    emit itemSold(sold.item_id, sold.winner_id, QString::fromUtf8(sold.winner_name), sold.final_price);
}

uint32_t NetworkClient::getNextRequestId() {
    return nextRequestId++;
}
