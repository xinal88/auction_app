#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QListWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include "network_client.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(NetworkClient *client, uint32_t userId, const QString &username, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Account tab
    void onDepositClicked();
    void onRedeemClicked();
    void onViewHistoryClicked();
    void onDepositResponse(int32_t status, const QString &message, int64_t newBalance);
    void onRedeemResponse(int32_t status, const QString &message, int64_t newBalance);
    
    // Rooms tab
    void onCreateRoomClicked();
    void onRefreshRoomsClicked();
    void onJoinRoomClicked();
    void onLeaveRoomClicked();
    void onRoomItemDoubleClicked(QListWidgetItem *item);
    void onCreateRoomResponse(int32_t status, const QString &message, uint32_t roomId);
    void onJoinRoomResponse(int32_t status, const QString &message);
    void onListRoomsResponse(int32_t status, const QString &message, uint16_t count, const QVector<RoomInfo> &rooms);
    
    // Auction tab
    void onRefreshItemsClicked();
    void onBidClicked();
    void onBuyNowClicked();
    void onSendChatClicked();
    void onViewItemsResponse(int32_t status, const QString &message, uint16_t count, const QVector<ItemInfo> &items);
    void onBidResponse(int32_t status, const QString &message);
    void onBuyNowResponse(int32_t status, const QString &message);
    void onBidNotify(uint32_t itemId, int64_t newPrice, uint32_t winnerId, const QString &winnerName);
    void onChatNotify(uint32_t senderId, const QString &senderName, const QString &text);
    void onTimerUpdate(uint32_t itemId, uint32_t remainingSec);
    
    // Connection
    void onDisconnected();
    void onLogoutClicked();

private:
    NetworkClient *networkClient;
    uint32_t currentUserId;
    QString currentUsername;
    uint32_t currentRoomId;
    QString currentRoomName;
    int64_t currentBalance;
    
    QTabWidget *tabWidget;
    
    // Account tab widgets
    QLabel *balanceLabel;
    QLineEdit *depositAmountEdit;
    QLineEdit *redeemAmountEdit;
    QTextEdit *historyTextEdit;
    
    // Rooms tab widgets
    QLineEdit *roomNameEdit;
    QLineEdit *roomDescEdit;
    QListWidget *roomsListWidget;
    QPushButton *joinRoomButton;
    QPushButton *leaveRoomButton;
    QLabel *currentRoomLabel;
    
    // Auction tab widgets
    QTableWidget *itemsTableWidget;
    QLineEdit *bidAmountEdit;
    QPushButton *bidButton;
    QPushButton *buyNowButton;
    QTextEdit *chatDisplayEdit;
    QLineEdit *chatInputEdit;
    QPushButton *sendChatButton;
    
    void setupUI();
    void setupAccountTab();
    void setupRoomsTab();
    void setupAuctionTab();
    void connectSignals();
    void updateBalanceDisplay();
    void updateCurrentRoomDisplay();
    void addChatMessage(const QString &sender, const QString &message);
};

#endif // MAIN_WINDOW_H
