#ifndef NETWORK_CLIENT_H
#define NETWORK_CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QByteArray>
#include "../common/protocol.h"

class NetworkClient : public QObject {
    Q_OBJECT

public:
    explicit NetworkClient(QObject *parent = nullptr);
    ~NetworkClient();

    // Connection management
    bool connectToServer(const QString &host, quint16 port);
    void disconnectFromServer();
    bool isConnected() const;

    // Send messages
    bool sendMessage(const Message &msg);
    bool sendLogin(const QString &username, const QString &password);
    bool sendRegister(const QString &username, const QString &password, 
                     const QString &email, const QString &bankAccount, const QString &bankName);
    bool sendDeposit(int64_t amount);
    bool sendRedeem(int64_t amount);
    bool sendCreateRoom(const QString &name, const QString &description);
    bool sendJoinRoom(uint32_t roomId);
    bool sendLeaveRoom();
    bool sendListRooms(const QString &query = "");
    bool sendBid(uint32_t itemId, int64_t bidAmount);
    bool sendBuyNow(uint32_t itemId);
    bool sendChat(const QString &text, uint32_t roomId);
    bool sendViewItems();
    bool sendViewHistory();

signals:
    void connected();
    void disconnected();
    void connectionError(const QString &error);
    
    // Response signals
    void loginResponse(int32_t status, const QString &message, uint32_t userId, const QString &token);
    void registerResponse(int32_t status, const QString &message);
    void depositResponse(int32_t status, const QString &message, int64_t newBalance);
    void redeemResponse(int32_t status, const QString &message, int64_t newBalance);
    void createRoomResponse(int32_t status, const QString &message, uint32_t roomId);
    void joinRoomResponse(int32_t status, const QString &message);
    void listRoomsResponse(int32_t status, const QString &message, uint16_t count, const QVector<RoomInfo> &rooms);
    void bidResponse(int32_t status, const QString &message);
    void buyNowResponse(int32_t status, const QString &message);
    void viewItemsResponse(int32_t status, const QString &message, uint16_t count, const QVector<ItemInfo> &items);
    void viewHistoryResponse(int32_t status, const QString &message, uint16_t count);
    
    // Notification signals
    void bidNotify(uint32_t itemId, int64_t newPrice, uint32_t winnerId, const QString &winnerName);
    void chatNotify(uint32_t senderId, const QString &senderName, const QString &text);
    void timerUpdate(uint32_t itemId, uint32_t remainingSec);
    void itemSold(uint32_t itemId, uint32_t winnerId, const QString &winnerName, int64_t finalPrice);

private slots:
    void onConnected();
    void onDisconnected();
    void onReadyRead();
    void onError(QAbstractSocket::SocketError socketError);

private:
    QTcpSocket *socket;
    QByteArray receiveBuffer;
    uint32_t nextRequestId;
    QString sessionToken;
    uint32_t currentUserId;
    uint32_t currentRoomId;

    void processMessage(const Message &msg);
    void handleLoginResponse(const char *payload, uint32_t length);
    void handleRegisterResponse(const char *payload, uint32_t length);
    void handleDepositResponse(const char *payload, uint32_t length);
    void handleRedeemResponse(const char *payload, uint32_t length);
    void handleCreateRoomResponse(const char *payload, uint32_t length);
    void handleJoinRoomResponse(const char *payload, uint32_t length);
    void handleListRoomsResponse(const char *payload, uint32_t length);
    void handleBidResponse(const char *payload, uint32_t length);
    void handleBuyNowResponse(const char *payload, uint32_t length);
    void handleViewItemsResponse(const char *payload, uint32_t length);
    void handleBidNotify(const char *payload, uint32_t length);
    void handleChatNotify(const char *payload, uint32_t length);
    void handleTimerUpdate(const char *payload, uint32_t length);
    void handleItemSold(const char *payload, uint32_t length);

    uint32_t getNextRequestId();
};

#endif // NETWORK_CLIENT_H
