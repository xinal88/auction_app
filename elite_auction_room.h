#ifndef ELITE_AUCTION_ROOM_H
#define ELITE_AUCTION_ROOM_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QListWidget>
#include <QTimer>
#include <QVBoxLayout>
#include <QNetworkAccessManager>

class EliteAuctionRoom : public QWidget
{
    Q_OBJECT

public:
    explicit EliteAuctionRoom(QWidget *parent = nullptr);
    ~EliteAuctionRoom();
    
    void setRoomName(const QString &name);
    void setRoomId(int roomId);

private slots:
    void onBackClicked();
    void onPlaceBidClicked();
    void onBuyNowClicked();
    void onSendMessageClicked();
    void updateTimer();
    void onQuickBidClicked();

private:
    void setupUI();
    QString getStyleSheet();
    QWidget* createUpcomingItemCard(const QString &name, const QString &price, const QString &imageUrl);
    void loadRoomData();
    void loadCurrentItem();
    void loadUpcomingItems();
    void loadImageForLabel(QLabel *label, const QString &url);
    
    // Header
    QPushButton *backButton;
    QLabel *roomNameLabel;
    QLabel *statusLabel;
    
    // Left panel - Upcoming items
    QWidget *leftPanel;
    QVBoxLayout *upcomingLayout;
    
    // Center panel - Current item
    QWidget *centerPanel;
    QLabel *itemImageLabel;
    QLabel *itemTitleLabel;
    QLabel *itemDescLabel;
    QLabel *startPriceLabel;
    QLabel *currentPriceLabel;
    QLabel *timerLabel;
    QWidget *timerWidget;
    QLineEdit *bidInput;
    QPushButton *bid50kBtn;
    QPushButton *bid100kBtn;
    QPushButton *bid500kBtn;
    QPushButton *placeBidBtn;
    QPushButton *buyNowBtn;
    
    // Right panel - Chat
    QWidget *rightPanel;
    QTextEdit *chatDisplay;
    QLineEdit *chatInput;
    QPushButton *sendButton;
    QListWidget *participantsList;
    
    // Timer
    QTimer *countdownTimer;
    int remainingSeconds;
    
    QString currentRoomName;
    int currentRoomId;
    int currentItemId;
    double currentBidAmount;
    double buyNowPrice;
    QNetworkAccessManager *networkManager;
};

#endif // ELITE_AUCTION_ROOM_H
