#include "elite_auction_room.h"
#include "elite_database.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QGraphicsDropShadowEffect>
#include <QStackedWidget>
#include <QColor>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPixmap>

EliteAuctionRoom::EliteAuctionRoom(QWidget *parent)
    : QWidget(parent), remainingSeconds(180), currentRoomId(1), currentItemId(0), 
      currentBidAmount(0), buyNowPrice(0)
{
    networkManager = new QNetworkAccessManager(this);
    setupUI();
    setStyleSheet(getStyleSheet());
    
    countdownTimer = new QTimer(this);
    connect(countdownTimer, &QTimer::timeout, this, &EliteAuctionRoom::updateTimer);
    countdownTimer->start(1000);
}

EliteAuctionRoom::~EliteAuctionRoom()
{
}

void EliteAuctionRoom::setRoomName(const QString &name)
{
    currentRoomName = name;
    roomNameLabel->setText(name);
}

void EliteAuctionRoom::setRoomId(int roomId)
{
    currentRoomId = roomId;
    loadRoomData();
}

void EliteAuctionRoom::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    
    // Header
    QWidget *header = new QWidget();
    header->setObjectName("roomHeader");
    header->setFixedHeight(70);
    
    QHBoxLayout *headerLayout = new QHBoxLayout(header);
    headerLayout->setContentsMargins(30, 0, 30, 0);
    
    backButton = new QPushButton("← Leave Room");
    backButton->setObjectName("backButton");
    backButton->setCursor(Qt::PointingHandCursor);
    
    roomNameLabel = new QLabel("Luxury Watches Auction");
    roomNameLabel->setObjectName("roomNameLabel");
    
    statusLabel = new QLabel("🔴 LIVE");
    statusLabel->setObjectName("liveStatusLabel");
    
    headerLayout->addWidget(backButton);
    headerLayout->addSpacing(20);
    headerLayout->addWidget(roomNameLabel);
    headerLayout->addWidget(statusLabel);
    headerLayout->addStretch();
    
    mainLayout->addWidget(header);
    
    // Three-column layout
    QWidget *contentWidget = new QWidget();
    QHBoxLayout *contentLayout = new QHBoxLayout(contentWidget);
    contentLayout->setContentsMargins(20, 20, 20, 20);
    contentLayout->setSpacing(20);
    
    // LEFT PANEL - Upcoming Items
    leftPanel = new QWidget();
    leftPanel->setObjectName("sidePanel");
    leftPanel->setFixedWidth(280);
    
    QVBoxLayout *leftLayout = new QVBoxLayout(leftPanel);
    leftLayout->setContentsMargins(20, 20, 20, 20);
    leftLayout->setSpacing(15);
    
    QLabel *upcomingHeader = new QLabel("Upcoming Items");
    upcomingHeader->setObjectName("panelHeader");
    
    QScrollArea *upcomingScroll = new QScrollArea();
    upcomingScroll->setWidgetResizable(true);
    upcomingScroll->setObjectName("scrollArea");
    upcomingScroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    
    QWidget *upcomingContainer = new QWidget();
    upcomingLayout = new QVBoxLayout(upcomingContainer);
    upcomingLayout->setSpacing(10);
    
    // Items will be loaded from database
    upcomingLayout->addStretch();
    
    upcomingScroll->setWidget(upcomingContainer);
    
    leftLayout->addWidget(upcomingHeader);
    leftLayout->addWidget(upcomingScroll);
    
    // CENTER PANEL - Current Item
    centerPanel = new QWidget();
    centerPanel->setObjectName("centerPanel");
    
    QVBoxLayout *centerLayout = new QVBoxLayout(centerPanel);
    centerLayout->setContentsMargins(30, 30, 30, 30);
    centerLayout->setSpacing(20);
    
    // Item image
    itemImageLabel = new QLabel();
    itemImageLabel->setObjectName("itemImage");
    itemImageLabel->setFixedHeight(350);
    itemImageLabel->setAlignment(Qt::AlignCenter);
    itemImageLabel->setText("⌚");
    itemImageLabel->setStyleSheet("font-size: 120px; background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #667eea, stop:1 #764ba2); border-radius: 16px;");
    
    // Item title
    itemTitleLabel = new QLabel("Rolex Submariner");
    itemTitleLabel->setObjectName("itemTitle");
    
    // Item description
    itemDescLabel = new QLabel("Vintage 1960s Rolex Submariner in excellent condition");
    itemDescLabel->setObjectName("itemDesc");
    itemDescLabel->setWordWrap(true);
    
    // Price info
    QWidget *priceWidget = new QWidget();
    QHBoxLayout *priceLayout = new QHBoxLayout(priceWidget);
    priceLayout->setContentsMargins(0, 0, 0, 0);
    priceLayout->setSpacing(40);
    
    QWidget *startPriceWidget = new QWidget();
    QVBoxLayout *startPriceLayout = new QVBoxLayout(startPriceWidget);
    startPriceLayout->setContentsMargins(0, 0, 0, 0);
    startPriceLayout->setSpacing(5);
    
    QLabel *startLabel = new QLabel("Start Price");
    startLabel->setObjectName("priceLabel");
    startPriceLabel = new QLabel("50,000,000 đ");
    startPriceLabel->setObjectName("priceValue");
    
    startPriceLayout->addWidget(startLabel);
    startPriceLayout->addWidget(startPriceLabel);
    
    QWidget *currentPriceWidget = new QWidget();
    QVBoxLayout *currentPriceLayout = new QVBoxLayout(currentPriceWidget);
    currentPriceLayout->setContentsMargins(0, 0, 0, 0);
    currentPriceLayout->setSpacing(5);
    
    QLabel *currentLabel = new QLabel("Current Bid");
    currentLabel->setObjectName("priceLabel");
    currentPriceLabel = new QLabel("75,000,000 đ");
    currentPriceLabel->setObjectName("currentPriceValue");
    
    currentPriceLayout->addWidget(currentLabel);
    currentPriceLayout->addWidget(currentPriceLabel);
    
    priceLayout->addWidget(startPriceWidget);
    priceLayout->addWidget(currentPriceWidget);
    priceLayout->addStretch();
    
    // Timer
    timerWidget = new QWidget();
    timerWidget->setObjectName("timerWidget");
    QVBoxLayout *timerLayout = new QVBoxLayout(timerWidget);
    timerLayout->setContentsMargins(20, 15, 20, 15);
    timerLayout->setSpacing(5);
    
    QLabel *timerHeaderLabel = new QLabel("Time Remaining");
    timerHeaderLabel->setObjectName("timerHeader");
    timerHeaderLabel->setAlignment(Qt::AlignCenter);
    
    timerLabel = new QLabel("0:46");
    timerLabel->setObjectName("timerValue");
    timerLabel->setAlignment(Qt::AlignCenter);
    
    timerLayout->addWidget(timerHeaderLabel);
    timerLayout->addWidget(timerLabel);
    
    // Bid input
    QLabel *bidLabel = new QLabel("Your Bid (Min: 75,010,000 đ)");
    bidLabel->setObjectName("bidLabel");
    
    bidInput = new QLineEdit();
    bidInput->setObjectName("bidInput");
    bidInput->setPlaceholderText("75010000");
    bidInput->setFixedHeight(50);
    
    // Quick bid buttons
    QWidget *quickBidWidget = new QWidget();
    QHBoxLayout *quickBidLayout = new QHBoxLayout(quickBidWidget);
    quickBidLayout->setContentsMargins(0, 0, 0, 0);
    quickBidLayout->setSpacing(10);
    
    bid50kBtn = new QPushButton("+50K");
    bid50kBtn->setObjectName("quickBidButton");
    bid50kBtn->setCursor(Qt::PointingHandCursor);
    
    bid100kBtn = new QPushButton("+100K");
    bid100kBtn->setObjectName("quickBidButton");
    bid100kBtn->setCursor(Qt::PointingHandCursor);
    
    bid500kBtn = new QPushButton("+500K");
    bid500kBtn->setObjectName("quickBidButton");
    bid500kBtn->setCursor(Qt::PointingHandCursor);
    
    quickBidLayout->addWidget(bid50kBtn);
    quickBidLayout->addWidget(bid100kBtn);
    quickBidLayout->addWidget(bid500kBtn);
    
    // Action buttons
    placeBidBtn = new QPushButton("Place Bid");
    placeBidBtn->setObjectName("placeBidButton");
    placeBidBtn->setFixedHeight(50);
    placeBidBtn->setCursor(Qt::PointingHandCursor);
    
    buyNowBtn = new QPushButton("🛒 Buy Now - 120,000,000 đ");
    buyNowBtn->setObjectName("buyNowButton");
    buyNowBtn->setFixedHeight(50);
    buyNowBtn->setCursor(Qt::PointingHandCursor);
    
    centerLayout->addWidget(itemImageLabel);
    centerLayout->addWidget(itemTitleLabel);
    centerLayout->addWidget(itemDescLabel);
    centerLayout->addWidget(priceWidget);
    centerLayout->addWidget(timerWidget);
    centerLayout->addWidget(bidLabel);
    centerLayout->addWidget(bidInput);
    centerLayout->addWidget(quickBidWidget);
    centerLayout->addWidget(placeBidBtn);
    centerLayout->addWidget(buyNowBtn);
    
    // RIGHT PANEL - Chat & Participants
    rightPanel = new QWidget();
    rightPanel->setObjectName("sidePanel");
    rightPanel->setFixedWidth(320);
    
    QVBoxLayout *rightLayout = new QVBoxLayout(rightPanel);
    rightLayout->setContentsMargins(20, 20, 20, 20);
    rightLayout->setSpacing(15);
    
    QLabel *chatHeader = new QLabel("Chat & Participants");
    chatHeader->setObjectName("panelHeader");
    
    // Participants count
    QLabel *participantsLabel = new QLabel("👥 3 participants");
    participantsLabel->setObjectName("participantsLabel");
    
    // Chat display
    chatDisplay = new QTextEdit();
    chatDisplay->setObjectName("chatDisplay");
    chatDisplay->setReadOnly(true);
    chatDisplay->setPlaceholderText("No messages yet. Start the conversation!");
    
    // Chat input
    QWidget *chatInputWidget = new QWidget();
    QHBoxLayout *chatInputLayout = new QHBoxLayout(chatInputWidget);
    chatInputLayout->setContentsMargins(0, 0, 0, 0);
    chatInputLayout->setSpacing(10);
    
    chatInput = new QLineEdit();
    chatInput->setObjectName("chatInput");
    chatInput->setPlaceholderText("Type a message...");
    chatInput->setFixedHeight(40);
    
    sendButton = new QPushButton("📤");
    sendButton->setObjectName("sendButton");
    sendButton->setFixedSize(40, 40);
    sendButton->setCursor(Qt::PointingHandCursor);
    
    chatInputLayout->addWidget(chatInput);
    chatInputLayout->addWidget(sendButton);
    
    rightLayout->addWidget(chatHeader);
    rightLayout->addWidget(participantsLabel);
    rightLayout->addWidget(chatDisplay, 1);
    rightLayout->addWidget(chatInputWidget);
    
    // Add panels to content
    contentLayout->addWidget(leftPanel);
    contentLayout->addWidget(centerPanel, 1);
    contentLayout->addWidget(rightPanel);
    
    mainLayout->addWidget(contentWidget);
    
    // Connect signals
    connect(backButton, &QPushButton::clicked, this, &EliteAuctionRoom::onBackClicked);
    connect(placeBidBtn, &QPushButton::clicked, this, &EliteAuctionRoom::onPlaceBidClicked);
    connect(buyNowBtn, &QPushButton::clicked, this, &EliteAuctionRoom::onBuyNowClicked);
    connect(sendButton, &QPushButton::clicked, this, &EliteAuctionRoom::onSendMessageClicked);
    connect(bid50kBtn, &QPushButton::clicked, this, &EliteAuctionRoom::onQuickBidClicked);
    connect(bid100kBtn, &QPushButton::clicked, this, &EliteAuctionRoom::onQuickBidClicked);
    connect(bid500kBtn, &QPushButton::clicked, this, &EliteAuctionRoom::onQuickBidClicked);
}

QWidget* EliteAuctionRoom::createUpcomingItemCard(const QString &name, const QString &price, const QString &imageUrl)
{
    QWidget *card = new QWidget();
    card->setObjectName("upcomingCard");
    
    QHBoxLayout *cardLayout = new QHBoxLayout(card);
    cardLayout->setContentsMargins(8, 8, 8, 8);
    cardLayout->setSpacing(10);
    
    // Small thumbnail
    QLabel *thumbLabel = new QLabel();
    thumbLabel->setFixedSize(50, 50);
    thumbLabel->setScaledContents(true);
    thumbLabel->setStyleSheet("border-radius: 6px;");
    
    if (!imageUrl.isEmpty()) {
        loadImageForLabel(thumbLabel, imageUrl);
    } else {
        thumbLabel->setText("📦");
        thumbLabel->setAlignment(Qt::AlignCenter);
        thumbLabel->setStyleSheet("font-size: 24px; background: #F7FAFC; border-radius: 6px;");
    }
    
    QVBoxLayout *textLayout = new QVBoxLayout();
    textLayout->setSpacing(4);
    
    QLabel *nameLabel = new QLabel(name);
    nameLabel->setObjectName("upcomingItemName");
    nameLabel->setWordWrap(true);
    
    QLabel *priceLabel = new QLabel(price);
    priceLabel->setObjectName("upcomingItemPrice");
    
    textLayout->addWidget(nameLabel);
    textLayout->addWidget(priceLabel);
    
    cardLayout->addWidget(thumbLabel);
    cardLayout->addLayout(textLayout, 1);
    
    return card;
}

void EliteAuctionRoom::updateTimer()
{
    if (remainingSeconds > 0) {
        remainingSeconds--;
        int minutes = remainingSeconds / 60;
        int seconds = remainingSeconds % 60;
        timerLabel->setText(QString("%1:%2").arg(minutes).arg(seconds, 2, 10, QChar('0')));
        
        // Warning state for last 30 seconds
        if (remainingSeconds <= 30) {
            timerWidget->setStyleSheet("#timerWidget { background-color: #FEF3C7; border: 2px solid #F59E0B; border-radius: 12px; }");
            timerLabel->setStyleSheet("#timerValue { font-size: 48px; font-weight: 700; color: #D97706; }");
        }
    }
}

void EliteAuctionRoom::onBackClicked()
{
    // Return to main window
    if (parentWidget() && parentWidget()->parentWidget()) {
        QStackedWidget *stack = qobject_cast<QStackedWidget*>(parentWidget());
        if (stack) {
            stack->setCurrentIndex(0);
        }
    }
}

void EliteAuctionRoom::onPlaceBidClicked()
{
    QString bidText = bidInput->text().trimmed();
    if (bidText.isEmpty()) {
        QMessageBox::warning(this, "Invalid Bid", "Please enter a bid amount!");
        return;
    }
    
    double bidAmount = bidText.toDouble();
    double minBid = currentBidAmount + 10000;
    
    if (bidAmount < minBid) {
        QMessageBox::warning(this, "Invalid Bid", 
            QString("Your bid must be at least %L1 đ\n(Current bid + 10,000 đ minimum increment)")
            .arg(minBid, 0, 'f', 0));
        return;
    }
    
    // Check user balance (assuming user ID 1 for demo)
    EliteDatabase *db = EliteDatabase::instance();
    if (db->isConnected()) {
        double userBalance = db->getUserBalance(1);
        if (bidAmount > userBalance) {
            QMessageBox::warning(this, "Insufficient Balance", 
                QString("Your balance (%L1 đ) is not enough for this bid.\n\n"
                       "Please deposit more funds to continue.")
                .arg(userBalance, 0, 'f', 0));
            return;
        }
        
        // Update bid in database
        if (db->updateItemPrice(currentItemId, bidAmount, 1)) {
            currentBidAmount = bidAmount;
            currentPriceLabel->setText(QString("%L1 đ").arg(bidAmount, 0, 'f', 0));
            
            // Add to chat
            chatDisplay->append(QString("<span style='color: #10B981; font-weight: 600;'>✓ You:</span> "
                                       "<span style='color: #1A202C;'>Placed bid of <b>%L1 đ</b></span>")
                .arg(bidAmount, 0, 'f', 0));
            
            bidInput->clear();
            
            // Update minimum bid label
            double newMinBid = bidAmount + 10000;
            bidInput->setPlaceholderText(QString::number(newMinBid, 'f', 0));
            
            // Show success notification
            QMessageBox msgBox(this);
            msgBox.setWindowTitle("Bid Placed Successfully");
            msgBox.setIcon(QMessageBox::Information);
            msgBox.setText("<h3 style='color: #10B981;'>✓ Bid Placed!</h3>");
            msgBox.setInformativeText(QString("<p>Your bid of <b>%L1 đ</b> has been placed successfully!</p>"
                                             "<p style='color: #718096;'>You are currently the highest bidder.</p>")
                .arg(bidAmount, 0, 'f', 0));
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.button(QMessageBox::Ok)->setStyleSheet(
                "background-color: #10B981; color: white; padding: 8px 24px; "
                "border-radius: 6px; font-weight: 600; min-width: 80px;");
            msgBox.exec();
        } else {
            QMessageBox::critical(this, "Bid Failed", 
                QString("Failed to place bid:\n%1").arg(db->lastError()));
        }
    } else {
        // Demo mode
        currentBidAmount = bidAmount;
        currentPriceLabel->setText(QString("%L1 đ").arg(bidAmount, 0, 'f', 0));
        
        chatDisplay->append(QString("<span style='color: #10B981; font-weight: 600;'>✓ You:</span> "
                                   "<span style='color: #1A202C;'>Placed bid of <b>%L1 đ</b> (Demo Mode)</span>")
            .arg(bidAmount, 0, 'f', 0));
        
        bidInput->clear();
        
        QMessageBox::information(this, "Bid Placed (Demo)", 
            QString("Your bid of %L1 đ has been placed!\n\n"
                   "Note: Running in demo mode. Connect database for real bidding.")
            .arg(bidAmount, 0, 'f', 0));
    }
}

void EliteAuctionRoom::onBuyNowClicked()
{
    if (buyNowPrice <= 0) {
        QMessageBox::warning(this, "Not Available", "Buy Now is not available for this item.");
        return;
    }
    
    // Check user balance first
    EliteDatabase *db = EliteDatabase::instance();
    if (db->isConnected()) {
        double userBalance = db->getUserBalance(1);
        if (buyNowPrice > userBalance) {
            QMessageBox::warning(this, "Insufficient Balance", 
                QString("Your balance (%L1 đ) is not enough to buy this item.\n\n"
                       "Item price: %L2 đ\n"
                       "Please deposit more funds to continue.")
                .arg(userBalance, 0, 'f', 0)
                .arg(buyNowPrice, 0, 'f', 0));
            return;
        }
    }
    
    // Enhanced confirmation dialog with better styling
    QMessageBox confirmBox(this);
    confirmBox.setWindowTitle("Buy Now Confirmation");
    confirmBox.setIcon(QMessageBox::Question);
    confirmBox.setStyleSheet(R"(
        QMessageBox {
            background-color: white;
        }
        QLabel {
            color: #1A202C;
            font-size: 14px;
        }
    )");
    
    confirmBox.setText(QString("<h2 style='color: #1A202C; margin-bottom: 10px;'>🛒 Confirm Purchase</h2>"));
    confirmBox.setInformativeText(
        QString("<div style='color: #2D3748; font-size: 15px;'>"
                "<p><b>Item:</b> %1</p>"
                "<p><b>Price:</b> <span style='color: #10B981; font-size: 18px; font-weight: 700;'>%L2 đ</span></p>"
                "<p style='color: #DC2626; margin-top: 15px;'><b>⚠️ This action cannot be undone.</b></p>"
                "<p style='color: #718096;'>The amount will be deducted from your balance immediately.</p>"
                "</div>")
        .arg(itemTitleLabel->text())
        .arg(buyNowPrice, 0, 'f', 0)
    );
    confirmBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    confirmBox.setDefaultButton(QMessageBox::No);
    
    QPushButton *yesButton = qobject_cast<QPushButton*>(confirmBox.button(QMessageBox::Yes));
    if (yesButton) {
        yesButton->setText("✓ Confirm Purchase");
        yesButton->setStyleSheet(
            "QPushButton {"
            "   background-color: #10B981;"
            "   color: white;"
            "   padding: 10px 20px;"
            "   border-radius: 8px;"
            "   font-weight: 700;"
            "   font-size: 15px;"
            "   min-width: 140px;"
            "}"
            "QPushButton:hover {"
            "   background-color: #059669;"
            "}"
        );
    }
    
    QPushButton *noButton = qobject_cast<QPushButton*>(confirmBox.button(QMessageBox::No));
    if (noButton) {
        noButton->setText("Cancel");
        noButton->setStyleSheet(
            "QPushButton {"
            "   background-color: #F7FAFC;"
            "   color: #2D3748;"
            "   border: 2px solid #E2E8F0;"
            "   padding: 10px 20px;"
            "   border-radius: 8px;"
            "   font-weight: 600;"
            "   font-size: 15px;"
            "   min-width: 100px;"
            "}"
            "QPushButton:hover {"
            "   background-color: #EDF2F7;"
            "   border-color: #CBD5E0;"
            "}"
        );
    }
    
    if (confirmBox.exec() == QMessageBox::Yes) {
        // Process purchase
        if (db->isConnected()) {
            // Update user balance
            double currentBalance = db->getUserBalance(1);
            double newBalance = currentBalance - buyNowPrice;
            
            if (db->updateUserBalance(1, newBalance)) {
                // Add transaction record
                db->addTransaction(1, "purchase", buyNowPrice, 
                    QString("Bought item: %1").arg(itemTitleLabel->text()));
                
                // Add to chat
                chatDisplay->append(QString("<span style='color: #10B981; font-weight: 700;'>🎉 System:</span> "
                                           "<span style='color: #1A202C;'>You bought <b>%1</b> for <b>%L2 đ</b>!</span>")
                    .arg(itemTitleLabel->text())
                    .arg(buyNowPrice, 0, 'f', 0));
                
                // Show success message
                QMessageBox successBox(this);
                successBox.setWindowTitle("Purchase Successful");
                successBox.setIcon(QMessageBox::Information);
                successBox.setStyleSheet("QMessageBox { background-color: white; } QLabel { color: #1A202C; }");
                successBox.setText("<h2 style='color: #10B981;'>🎉 Purchase Successful!</h2>");
                successBox.setInformativeText(
                    QString("<div style='color: #2D3748; font-size: 15px;'>"
                           "<p>Congratulations! You have successfully purchased:</p>"
                           "<p><b>Item:</b> %1</p>"
                           "<p><b>Amount:</b> <span style='color: #10B981; font-weight: 700;'>%L2 đ</span></p>"
                           "<p style='color: #718096; margin-top: 10px;'>Your new balance: <b>%L3 đ</b></p>"
                           "</div>")
                    .arg(itemTitleLabel->text())
                    .arg(buyNowPrice, 0, 'f', 0)
                    .arg(newBalance, 0, 'f', 0));
                successBox.setStandardButtons(QMessageBox::Ok);
                successBox.button(QMessageBox::Ok)->setStyleSheet(
                    "background-color: #10B981; color: white; padding: 8px 24px; "
                    "border-radius: 6px; font-weight: 600; min-width: 80px;");
                successBox.exec();
                
                // Load next item
                loadCurrentItem();
            } else {
                QMessageBox::critical(this, "Purchase Failed", 
                    QString("Failed to process purchase:\n%1").arg(db->lastError()));
            }
        } else {
            // Demo mode
            chatDisplay->append(QString("<span style='color: #10B981; font-weight: 700;'>🎉 System:</span> "
                                       "<span style='color: #1A202C;'>You bought <b>%1</b> for <b>%L2 đ</b>! (Demo Mode)</span>")
                .arg(itemTitleLabel->text())
                .arg(buyNowPrice, 0, 'f', 0));
            
            QMessageBox::information(this, "Purchase Successful (Demo)", 
                QString("Congratulations! You have successfully purchased this item.\n\n"
                       "Item: %1\n"
                       "Amount: %L2 đ\n\n"
                       "Note: Running in demo mode. Connect database for real purchases.")
                .arg(itemTitleLabel->text())
                .arg(buyNowPrice, 0, 'f', 0));
        }
    }
}

void EliteAuctionRoom::onSendMessageClicked()
{
    QString message = chatInput->text().trimmed();
    if (!message.isEmpty()) {
        // Add to chat with proper styling
        chatDisplay->append(QString("<span style='color: #4F46E5; font-weight: 600;'>You:</span> "
                                   "<span style='color: #1A202C;'>%1</span>")
            .arg(message));
        
        // Save to database if connected
        EliteDatabase *db = EliteDatabase::instance();
        if (db->isConnected()) {
            db->sendChatMessage(currentRoomId, 1, message);
        }
        
        chatInput->clear();
    }
}

void EliteAuctionRoom::onQuickBidClicked()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (btn) {
        double currentBid = currentBidAmount;
        int increment = 0;
        
        if (btn == bid50kBtn) increment = 50000;
        else if (btn == bid100kBtn) increment = 100000;
        else if (btn == bid500kBtn) increment = 500000;
        
        double newBid = currentBid + increment;
        bidInput->setText(QString::number(newBid, 'f', 0));
    }
}

QString EliteAuctionRoom::getStyleSheet()
{
    return R"(
        QWidget {
            background-color: #F8F9FA;
            font-family: 'Segoe UI', 'Inter', sans-serif;
            color: #1A202C;
        }
        
        #roomHeader {
            background-color: white;
            border-bottom: 1px solid #E2E8F0;
        }
        
        #backButton {
            background-color: transparent;
            border: 2px solid #E2E8F0;
            border-radius: 8px;
            color: #2D3748;
            font-size: 14px;
            font-weight: 600;
            padding: 10px 20px;
        }
        
        #backButton:hover {
            background-color: #F7FAFC;
            border-color: #CBD5E0;
        }
        
        #roomNameLabel {
            font-size: 20px;
            font-weight: 700;
            color: #1A202C;
        }
        
        #liveStatusLabel {
            background-color: #FEE2E2;
            color: #DC2626;
            font-size: 13px;
            font-weight: 700;
            padding: 8px 16px;
            border-radius: 8px;
        }
        
        #sidePanel {
            background-color: white;
            border-radius: 16px;
        }
        
        #centerPanel {
            background-color: white;
            border-radius: 16px;
        }
        
        #panelHeader {
            font-size: 16px;
            font-weight: 700;
            color: #1A202C;
        }
        
        #upcomingCard {
            background-color: #F7FAFC;
            border-radius: 10px;
            border: 1px solid #E2E8F0;
        }
        
        #upcomingCard:hover {
            background-color: #EDF2F7;
        }
        
        #upcomingItemName {
            font-size: 13px;
            font-weight: 600;
            color: #2D3748;
        }
        
        #upcomingItemPrice {
            font-size: 12px;
            color: #4F46E5;
            font-weight: 600;
        }
        
        #itemImage {
            border-radius: 16px;
        }
        
        #itemTitle {
            font-size: 28px;
            font-weight: 700;
            color: #1A202C;
        }
        
        #itemDesc {
            font-size: 15px;
            color: #718096;
        }
        
        #priceLabel {
            font-size: 13px;
            color: #718096;
            font-weight: 500;
        }
        
        #priceValue {
            font-size: 18px;
            font-weight: 600;
            color: #2D3748;
        }
        
        #currentPriceValue {
            font-size: 24px;
            font-weight: 700;
            color: #4F46E5;
        }
        
        #timerWidget {
            background-color: #EEF2FF;
            border: 2px solid #4F46E5;
            border-radius: 12px;
        }
        
        #timerHeader {
            font-size: 14px;
            color: #4F46E5;
            font-weight: 600;
        }
        
        #timerValue {
            font-size: 48px;
            font-weight: 700;
            color: #4F46E5;
        }
        
        #bidLabel {
            font-size: 14px;
            font-weight: 600;
            color: #2D3748;
        }
        
        #bidInput {
            border: 2px solid #E2E8F0;
            border-radius: 10px;
            padding: 0 16px;
            font-size: 16px;
            font-weight: 600;
            color: #2D3748;
        }
        
        #bidInput:focus {
            border: 2px solid #4F46E5;
        }
        
        #quickBidButton {
            background-color: #F7FAFC;
            border: 2px solid #E2E8F0;
            border-radius: 8px;
            color: #2D3748;
            font-size: 14px;
            font-weight: 600;
            padding: 10px;
        }
        
        #quickBidButton:hover {
            background-color: #EDF2F7;
            border-color: #CBD5E0;
        }
        
        #placeBidButton {
            background-color: #4F46E5;
            color: white;
            border: none;
            border-radius: 10px;
            font-size: 16px;
            font-weight: 700;
        }
        
        #placeBidButton:hover {
            background-color: #4338CA;
        }
        
        #buyNowButton {
            background-color: #10B981;
            color: white;
            border: none;
            border-radius: 10px;
            font-size: 16px;
            font-weight: 700;
        }
        
        #buyNowButton:hover {
            background-color: #059669;
        }
        
        #participantsLabel {
            font-size: 13px;
            color: #718096;
            font-weight: 500;
        }
        
        #chatDisplay {
            border: 1px solid #E2E8F0;
            border-radius: 10px;
            padding: 12px;
            font-size: 14px;
            background-color: white;
            color: #1A202C;
        }
        
        QTextEdit {
            color: #1A202C;
            background-color: white;
        }
        
        #chatInput {
            border: 2px solid #E2E8F0;
            border-radius: 8px;
            padding: 0 12px;
            font-size: 14px;
            color: #1A202C;
            background-color: white;
        }
        
        #chatInput:focus {
            border: 2px solid #4F46E5;
        }
        
        QLineEdit {
            color: #1A202C;
            background-color: white;
        }
        
        #sendButton {
            background-color: #4F46E5;
            color: white;
            border: none;
            border-radius: 8px;
            font-size: 16px;
        }
        
        #sendButton:hover {
            background-color: #4338CA;
        }
        
        #scrollArea {
            border: none;
            background-color: transparent;
        }
        
        QScrollArea {
            border: none;
            background-color: transparent;
        }
        
        QScrollBar:vertical {
            border: none;
            background: #F7FAFC;
            width: 8px;
            border-radius: 4px;
        }
        
        QScrollBar::handle:vertical {
            background: #CBD5E0;
            border-radius: 4px;
            min-height: 20px;
        }
        
        QScrollBar::handle:vertical:hover {
            background: #A0AEC0;
        }
        
        QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
            height: 0px;
        }
    )";
}

void EliteAuctionRoom::loadRoomData()
{
    EliteDatabase *db = EliteDatabase::instance();
    QVariantMap roomDetails = db->getRoomDetails(currentRoomId);
    
    if (!roomDetails.isEmpty()) {
        roomNameLabel->setText(roomDetails["room_name"].toString());
        
        QString status = roomDetails["status"].toString();
        if (status == "active") {
            statusLabel->setText("🔴 LIVE");
            statusLabel->setObjectName("liveStatusLabel");
        } else {
            statusLabel->setText("📅 UPCOMING");
            statusLabel->setObjectName("upcomingStatusLabel");
        }
        
        // Refresh style
        statusLabel->style()->unpolish(statusLabel);
        statusLabel->style()->polish(statusLabel);
    }
    
    loadCurrentItem();
    loadUpcomingItems();
}

void EliteAuctionRoom::loadCurrentItem()
{
    EliteDatabase *db = EliteDatabase::instance();
    QVariantMap item = db->getCurrentItem(currentRoomId);
    
    if (!item.isEmpty()) {
        currentItemId = item["item_id"].toInt();
        currentBidAmount = item["current_price"].toDouble();
        buyNowPrice = item["buy_now_price"].toDouble();
        
        itemTitleLabel->setText(item["item_name"].toString());
        itemDescLabel->setText(item["description"].toString());
        startPriceLabel->setText(QString("%L1 đ").arg(item["starting_price"].toDouble(), 0, 'f', 0));
        currentPriceLabel->setText(QString("%L1 đ").arg(currentBidAmount, 0, 'f', 0));
        
        // Update bid input placeholder
        double minBid = currentBidAmount + 10000;
        bidInput->setPlaceholderText(QString::number(minBid, 'f', 0));
        
        // Update Buy Now button
        if (buyNowPrice > 0) {
            buyNowBtn->setText(QString("🛒 Buy Now - %L1 đ").arg(buyNowPrice, 0, 'f', 0));
            buyNowBtn->setEnabled(true);
        } else {
            buyNowBtn->setText("🛒 Buy Now - Not Available");
            buyNowBtn->setEnabled(false);
        }
        
        // Load image
        QString imageUrl = item["image_url"].toString();
        if (!imageUrl.isEmpty()) {
            loadImageForLabel(itemImageLabel, imageUrl);
        } else {
            itemImageLabel->setText("⌚");
            itemImageLabel->setStyleSheet("font-size: 120px; background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #667eea, stop:1 #764ba2); border-radius: 16px;");
        }
        
        // Reset timer
        remainingSeconds = item["auction_duration"].toInt();
    } else {
        itemTitleLabel->setText("No Active Item");
        itemDescLabel->setText("Waiting for next item to start...");
        buyNowBtn->setEnabled(false);
        placeBidBtn->setEnabled(false);
    }
}

void EliteAuctionRoom::loadUpcomingItems()
{
    // Clear existing items
    while (upcomingLayout->count() > 1) {
        QLayoutItem *item = upcomingLayout->takeAt(0);
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }
    
    EliteDatabase *db = EliteDatabase::instance();
    QList<QVariantMap> items = db->getRoomItems(currentRoomId);
    
    for (const QVariantMap &item : items) {
        if (item["status"].toString() == "available") {
            QWidget *card = createUpcomingItemCard(
                item["item_name"].toString(),
                QString("%L1 đ").arg(item["starting_price"].toDouble(), 0, 'f', 0),
                item["image_url"].toString()
            );
            upcomingLayout->insertWidget(upcomingLayout->count() - 1, card);
        }
    }
}

void EliteAuctionRoom::loadImageForLabel(QLabel *label, const QString &url)
{
    QNetworkRequest request(url);
    QNetworkReply *reply = networkManager->get(request);
    
    connect(reply, &QNetworkReply::finished, [this, reply, label]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray data = reply->readAll();
            QPixmap pixmap;
            if (pixmap.loadFromData(data)) {
                QSize labelSize = label->size();
                label->setPixmap(pixmap.scaled(labelSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
            }
        }
        reply->deleteLater();
    });
}
