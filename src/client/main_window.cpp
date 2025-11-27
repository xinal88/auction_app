#include "main_window.h"
#include "client_logger.h"
#include <QMenuBar>
#include <QMessageBox>
#include <QHeaderView>
#include <QApplication>

MainWindow::MainWindow(NetworkClient *client, uint32_t userId, const QString &username, QWidget *parent)
    : QMainWindow(parent)
    , networkClient(client)
    , currentUserId(userId)
    , currentUsername(username)
    , currentRoomId(0)
    , currentBalance(0)
{
    setupUI();
    connectSignals();
    setWindowTitle("Auction App - " + username);
    resize(900, 700);
    
    // Auto refresh rooms list
    networkClient->sendListRooms();
}

MainWindow::~MainWindow() {
}

void MainWindow::setupUI() {
    // Menu bar
    QMenu *fileMenu = menuBar()->addMenu("&File");
    QAction *logoutAction = fileMenu->addAction("&Logout");
    connect(logoutAction, &QAction::triggered, this, &MainWindow::onLogoutClicked);
    QAction *exitAction = fileMenu->addAction("E&xit");
    connect(exitAction, &QAction::triggered, qApp, &QApplication::quit);
    
    // Central widget with tabs
    tabWidget = new QTabWidget(this);
    setCentralWidget(tabWidget);
    
    setupAccountTab();
    setupRoomsTab();
    setupAuctionTab();
}

void MainWindow::setupAccountTab() {
    QWidget *accountWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(accountWidget);
    
    // Balance display
    QGroupBox *balanceGroup = new QGroupBox("Account Balance", this);
    QVBoxLayout *balanceLayout = new QVBoxLayout(balanceGroup);
    balanceLabel = new QLabel("Balance: 0 VND", this);
    QFont balanceFont = balanceLabel->font();
    balanceFont.setPointSize(16);
    balanceFont.setBold(true);
    balanceLabel->setFont(balanceFont);
    balanceLabel->setStyleSheet("QLabel { color: #2E7D32; }");
    balanceLayout->addWidget(balanceLabel);
    layout->addWidget(balanceGroup);
    
    // Deposit section
    QGroupBox *depositGroup = new QGroupBox("Deposit Money", this);
    QHBoxLayout *depositLayout = new QHBoxLayout(depositGroup);
    depositAmountEdit = new QLineEdit(this);
    depositAmountEdit->setPlaceholderText("Enter amount (VND)");
    QPushButton *depositButton = new QPushButton("Deposit", this);
    depositButton->setStyleSheet("QPushButton { background-color: #4CAF50; color: white; padding: 8px; }");
    connect(depositButton, &QPushButton::clicked, this, &MainWindow::onDepositClicked);
    depositLayout->addWidget(depositAmountEdit);
    depositLayout->addWidget(depositButton);
    layout->addWidget(depositGroup);
    
    // Redeem section
    QGroupBox *redeemGroup = new QGroupBox("Redeem Money", this);
    QHBoxLayout *redeemLayout = new QHBoxLayout(redeemGroup);
    redeemAmountEdit = new QLineEdit(this);
    redeemAmountEdit->setPlaceholderText("Enter amount (VND)");
    QPushButton *redeemButton = new QPushButton("Redeem", this);
    redeemButton->setStyleSheet("QPushButton { background-color: #FF9800; color: white; padding: 8px; }");
    connect(redeemButton, &QPushButton::clicked, this, &MainWindow::onRedeemClicked);
    redeemLayout->addWidget(redeemAmountEdit);
    redeemLayout->addWidget(redeemButton);
    layout->addWidget(redeemGroup);
    
    // History section
    QGroupBox *historyGroup = new QGroupBox("Transaction History", this);
    QVBoxLayout *historyLayout = new QVBoxLayout(historyGroup);
    historyTextEdit = new QTextEdit(this);
    historyTextEdit->setReadOnly(true);
    QPushButton *viewHistoryButton = new QPushButton("Refresh History", this);
    connect(viewHistoryButton, &QPushButton::clicked, this, &MainWindow::onViewHistoryClicked);
    historyLayout->addWidget(historyTextEdit);
    historyLayout->addWidget(viewHistoryButton);
    layout->addWidget(historyGroup);
    
    tabWidget->addTab(accountWidget, "Account");
}

void MainWindow::setupRoomsTab() {
    QWidget *roomsWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(roomsWidget);
    
    // Current room display
    currentRoomLabel = new QLabel("Not in any room", this);
    currentRoomLabel->setStyleSheet("QLabel { background-color: #E3F2FD; padding: 10px; font-weight: bold; }");
    layout->addWidget(currentRoomLabel);
    
    // Create room section
    QGroupBox *createGroup = new QGroupBox("Create New Room", this);
    QVBoxLayout *createLayout = new QVBoxLayout(createGroup);
    QHBoxLayout *nameLayout = new QHBoxLayout();
    nameLayout->addWidget(new QLabel("Room Name:", this));
    roomNameEdit = new QLineEdit(this);
    roomNameEdit->setPlaceholderText("Enter room name");
    nameLayout->addWidget(roomNameEdit);
    createLayout->addLayout(nameLayout);
    
    QHBoxLayout *descLayout = new QHBoxLayout();
    descLayout->addWidget(new QLabel("Description:", this));
    roomDescEdit = new QLineEdit(this);
    roomDescEdit->setPlaceholderText("Enter description");
    descLayout->addWidget(roomDescEdit);
    createLayout->addLayout(descLayout);
    
    QPushButton *createRoomButton = new QPushButton("Create Room", this);
    createRoomButton->setStyleSheet("QPushButton { background-color: #2196F3; color: white; padding: 8px; }");
    connect(createRoomButton, &QPushButton::clicked, this, &MainWindow::onCreateRoomClicked);
    createLayout->addWidget(createRoomButton);
    layout->addWidget(createGroup);
    
    // Rooms list
    QGroupBox *listGroup = new QGroupBox("Available Rooms", this);
    QVBoxLayout *listLayout = new QVBoxLayout(listGroup);
    roomsListWidget = new QListWidget(this);
    connect(roomsListWidget, &QListWidget::itemDoubleClicked, this, &MainWindow::onRoomItemDoubleClicked);
    listLayout->addWidget(roomsListWidget);
    
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *refreshButton = new QPushButton("Refresh", this);
    connect(refreshButton, &QPushButton::clicked, this, &MainWindow::onRefreshRoomsClicked);
    joinRoomButton = new QPushButton("Join Room", this);
    joinRoomButton->setStyleSheet("QPushButton { background-color: #4CAF50; color: white; padding: 8px; }");
    connect(joinRoomButton, &QPushButton::clicked, this, &MainWindow::onJoinRoomClicked);
    leaveRoomButton = new QPushButton("Leave Room", this);
    leaveRoomButton->setStyleSheet("QPushButton { background-color: #F44336; color: white; padding: 8px; }");
    leaveRoomButton->setEnabled(false);
    connect(leaveRoomButton, &QPushButton::clicked, this, &MainWindow::onLeaveRoomClicked);
    
    buttonLayout->addWidget(refreshButton);
    buttonLayout->addWidget(joinRoomButton);
    buttonLayout->addWidget(leaveRoomButton);
    listLayout->addLayout(buttonLayout);
    layout->addWidget(listGroup);
    
    tabWidget->addTab(roomsWidget, "Rooms");
}

void MainWindow::setupAuctionTab() {
    QWidget *auctionWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(auctionWidget);
    
    // Items table
    QGroupBox *itemsGroup = new QGroupBox("Auction Items", this);
    QVBoxLayout *itemsLayout = new QVBoxLayout(itemsGroup);
    
    itemsTableWidget = new QTableWidget(this);
    itemsTableWidget->setColumnCount(6);
    itemsTableWidget->setHorizontalHeaderLabels({"ID", "Name", "Current Price", "Buy Now", "Time Left", "Status"});
    itemsTableWidget->horizontalHeader()->setStretchLastSection(true);
    itemsTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    itemsTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    itemsLayout->addWidget(itemsTableWidget);
    
    QPushButton *refreshItemsButton = new QPushButton("Refresh Items", this);
    connect(refreshItemsButton, &QPushButton::clicked, this, &MainWindow::onRefreshItemsClicked);
    itemsLayout->addWidget(refreshItemsButton);
    layout->addWidget(itemsGroup);
    
    // Bidding section
    QGroupBox *bidGroup = new QGroupBox("Place Bid", this);
    QHBoxLayout *bidLayout = new QHBoxLayout(bidGroup);
    bidAmountEdit = new QLineEdit(this);
    bidAmountEdit->setPlaceholderText("Enter bid amount (VND)");
    bidButton = new QPushButton("Place Bid", this);
    bidButton->setStyleSheet("QPushButton { background-color: #FF9800; color: white; padding: 8px; }");
    connect(bidButton, &QPushButton::clicked, this, &MainWindow::onBidClicked);
    buyNowButton = new QPushButton("Buy Now", this);
    buyNowButton->setStyleSheet("QPushButton { background-color: #F44336; color: white; padding: 8px; }");
    connect(buyNowButton, &QPushButton::clicked, this, &MainWindow::onBuyNowClicked);
    bidLayout->addWidget(bidAmountEdit);
    bidLayout->addWidget(bidButton);
    bidLayout->addWidget(buyNowButton);
    layout->addWidget(bidGroup);
    
    // Chat section
    QGroupBox *chatGroup = new QGroupBox("Room Chat", this);
    QVBoxLayout *chatLayout = new QVBoxLayout(chatGroup);
    chatDisplayEdit = new QTextEdit(this);
    chatDisplayEdit->setReadOnly(true);
    chatDisplayEdit->setMaximumHeight(150);
    chatLayout->addWidget(chatDisplayEdit);
    
    QHBoxLayout *chatInputLayout = new QHBoxLayout();
    chatInputEdit = new QLineEdit(this);
    chatInputEdit->setPlaceholderText("Type your message...");
    sendChatButton = new QPushButton("Send", this);
    sendChatButton->setStyleSheet("QPushButton { background-color: #2196F3; color: white; padding: 8px; }");
    connect(sendChatButton, &QPushButton::clicked, this, &MainWindow::onSendChatClicked);
    connect(chatInputEdit, &QLineEdit::returnPressed, this, &MainWindow::onSendChatClicked);
    chatInputLayout->addWidget(chatInputEdit);
    chatInputLayout->addWidget(sendChatButton);
    chatLayout->addLayout(chatInputLayout);
    layout->addWidget(chatGroup);
    
    tabWidget->addTab(auctionWidget, "Auction");
}

void MainWindow::connectSignals() {
    connect(networkClient, &NetworkClient::depositResponse, this, &MainWindow::onDepositResponse);
    connect(networkClient, &NetworkClient::redeemResponse, this, &MainWindow::onRedeemResponse);
    connect(networkClient, &NetworkClient::createRoomResponse, this, &MainWindow::onCreateRoomResponse);
    connect(networkClient, &NetworkClient::joinRoomResponse, this, &MainWindow::onJoinRoomResponse);
    connect(networkClient, &NetworkClient::listRoomsResponse, this, &MainWindow::onListRoomsResponse);
    connect(networkClient, &NetworkClient::viewItemsResponse, this, &MainWindow::onViewItemsResponse);
    connect(networkClient, &NetworkClient::bidResponse, this, &MainWindow::onBidResponse);
    connect(networkClient, &NetworkClient::buyNowResponse, this, &MainWindow::onBuyNowResponse);
    connect(networkClient, &NetworkClient::bidNotify, this, &MainWindow::onBidNotify);
    connect(networkClient, &NetworkClient::chatNotify, this, &MainWindow::onChatNotify);
    connect(networkClient, &NetworkClient::timerUpdate, this, &MainWindow::onTimerUpdate);
    connect(networkClient, &NetworkClient::disconnected, this, &MainWindow::onDisconnected);
}

// Account tab slots
void MainWindow::onDepositClicked() {
    bool ok;
    int64_t amount = depositAmountEdit->text().toLongLong(&ok);
    
    if (!ok || amount <= 0) {
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid positive amount");
        return;
    }
    
    if (networkClient->sendDeposit(amount)) {
        depositAmountEdit->clear();
    }
}

void MainWindow::onRedeemClicked() {
    bool ok;
    int64_t amount = redeemAmountEdit->text().toLongLong(&ok);
    
    if (!ok || amount <= 0) {
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid positive amount");
        return;
    }
    
    if (networkClient->sendRedeem(amount)) {
        redeemAmountEdit->clear();
    }
}

void MainWindow::onViewHistoryClicked() {
    networkClient->sendViewHistory();
}

void MainWindow::onDepositResponse(int32_t status, const QString &message, int64_t newBalance) {
    if (status == 1) {
        currentBalance = newBalance;
        updateBalanceDisplay();
        QMessageBox::information(this, "Success", "Deposit successful!");
        ClientLogger::instance().logDeposit(newBalance - currentBalance, true);
    } else {
        QMessageBox::warning(this, "Failed", "Deposit failed: " + message);
        ClientLogger::instance().logDeposit(0, false);
    }
}

void MainWindow::onRedeemResponse(int32_t status, const QString &message, int64_t newBalance) {
    if (status == 1) {
        currentBalance = newBalance;
        updateBalanceDisplay();
        QMessageBox::information(this, "Success", "Redeem successful!");
        ClientLogger::instance().logRedeem(currentBalance - newBalance, true);
    } else {
        QMessageBox::warning(this, "Failed", "Redeem failed: " + message);
        ClientLogger::instance().logRedeem(0, false);
    }
}

// Rooms tab slots
void MainWindow::onCreateRoomClicked() {
    QString name = roomNameEdit->text().trimmed();
    QString desc = roomDescEdit->text().trimmed();
    
    if (name.isEmpty()) {
        QMessageBox::warning(this, "Invalid Input", "Please enter room name");
        return;
    }
    
    networkClient->sendCreateRoom(name, desc);
}

void MainWindow::onRefreshRoomsClicked() {
    networkClient->sendListRooms();
}

void MainWindow::onJoinRoomClicked() {
    QListWidgetItem *item = roomsListWidget->currentItem();
    if (!item) {
        QMessageBox::warning(this, "No Selection", "Please select a room to join");
        return;
    }
    
    uint32_t roomId = item->data(Qt::UserRole).toUInt();
    networkClient->sendJoinRoom(roomId);
}

void MainWindow::onLeaveRoomClicked() {
    if (currentRoomId == 0) {
        return;
    }
    
    networkClient->sendLeaveRoom();
    ClientLogger::instance().logRoomLeave(currentRoomName);
    currentRoomId = 0;
    currentRoomName.clear();
    updateCurrentRoomDisplay();
}

void MainWindow::onRoomItemDoubleClicked(QListWidgetItem *item) {
    onJoinRoomClicked();
}

void MainWindow::onCreateRoomResponse(int32_t status, const QString &message, uint32_t roomId) {
    if (status == 1) {
        QMessageBox::information(this, "Success", "Room created successfully!");
        roomNameEdit->clear();
        roomDescEdit->clear();
        networkClient->sendListRooms();
    } else {
        QMessageBox::warning(this, "Failed", "Failed to create room: " + message);
    }
}

void MainWindow::onJoinRoomResponse(int32_t status, const QString &message) {
    if (status == 1) {
        QListWidgetItem *item = roomsListWidget->currentItem();
        if (item) {
            currentRoomId = item->data(Qt::UserRole).toUInt();
            currentRoomName = item->text().split(" - ")[0];
            updateCurrentRoomDisplay();
            ClientLogger::instance().logRoomJoin(currentRoomName, currentRoomId);
            
            // Switch to auction tab and refresh items
            tabWidget->setCurrentIndex(2);
            networkClient->sendViewItems();
        }
        QMessageBox::information(this, "Success", "Joined room successfully!");
    } else {
        QMessageBox::warning(this, "Failed", "Failed to join room: " + message);
    }
}

void MainWindow::onListRoomsResponse(int32_t status, const QString &message, uint16_t count, const QVector<RoomInfo> &rooms) {
    roomsListWidget->clear();
    
    for (const RoomInfo &room : rooms) {
        QString itemText = QString("%1 - %2")
                            .arg(QString::fromUtf8(room.room_name))
                            .arg(QString::fromUtf8(room.description));
        QListWidgetItem *item = new QListWidgetItem(itemText);
        item->setData(Qt::UserRole, room.room_id);
        roomsListWidget->addItem(item);
    }
}

// Auction tab slots
void MainWindow::onRefreshItemsClicked() {
    if (currentRoomId == 0) {
        QMessageBox::warning(this, "Not in Room", "Please join a room first");
        return;
    }
    networkClient->sendViewItems();
}

void MainWindow::onBidClicked() {
    int row = itemsTableWidget->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "No Selection", "Please select an item to bid on");
        return;
    }
    
    bool ok;
    int64_t amount = bidAmountEdit->text().toLongLong(&ok);
    if (!ok || amount <= 0) {
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid bid amount");
        return;
    }
    
    uint32_t itemId = itemsTableWidget->item(row, 0)->text().toUInt();
    networkClient->sendBid(itemId, amount);
}

void MainWindow::onBuyNowClicked() {
    int row = itemsTableWidget->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "No Selection", "Please select an item to buy");
        return;
    }
    
    uint32_t itemId = itemsTableWidget->item(row, 0)->text().toUInt();
    
    int ret = QMessageBox::question(this, "Confirm", "Are you sure you want to buy this item now?");
    if (ret == QMessageBox::Yes) {
        networkClient->sendBuyNow(itemId);
    }
}

void MainWindow::onSendChatClicked() {
    QString text = chatInputEdit->text().trimmed();
    if (text.isEmpty() || currentRoomId == 0) {
        return;
    }
    
    networkClient->sendChat(text, currentRoomId);
    chatInputEdit->clear();
    ClientLogger::instance().logChat(currentRoomName, text);
}

void MainWindow::onViewItemsResponse(int32_t status, const QString &message, uint16_t count, const QVector<ItemInfo> &items) {
    itemsTableWidget->setRowCount(0);
    
    for (const ItemInfo &item : items) {
        int row = itemsTableWidget->rowCount();
        itemsTableWidget->insertRow(row);
        
        itemsTableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(item.item_id)));
        itemsTableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromUtf8(item.item_name)));
        itemsTableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(item.current_price) + " VND"));
        itemsTableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(item.buy_now_price) + " VND"));
        itemsTableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(item.remaining_sec) + "s"));
        itemsTableWidget->setItem(row, 5, new QTableWidgetItem(QString::fromUtf8(item.status)));
    }
}

void MainWindow::onBidResponse(int32_t status, const QString &message) {
    if (status == 1) {
        QMessageBox::information(this, "Success", "Bid placed successfully!");
        bidAmountEdit->clear();
        ClientLogger::instance().logBid(0, bidAmountEdit->text().toLongLong(), true);
    } else {
        QMessageBox::warning(this, "Failed", "Bid failed: " + message);
        ClientLogger::instance().logBid(0, 0, false);
    }
}

void MainWindow::onBuyNowResponse(int32_t status, const QString &message) {
    if (status == 1) {
        QMessageBox::information(this, "Success", "Item purchased successfully!");
        networkClient->sendViewItems();
    } else {
        QMessageBox::warning(this, "Failed", "Purchase failed: " + message);
    }
}

void MainWindow::onBidNotify(uint32_t itemId, int64_t newPrice, uint32_t winnerId, const QString &winnerName) {
    // Update item in table
    for (int row = 0; row < itemsTableWidget->rowCount(); ++row) {
        if (itemsTableWidget->item(row, 0)->text().toUInt() == itemId) {
            itemsTableWidget->item(row, 2)->setText(QString::number(newPrice) + " VND");
            break;
        }
    }
    
    addChatMessage("SYSTEM", QString("New bid on item %1: %2 VND by %3")
                   .arg(itemId).arg(newPrice).arg(winnerName));
}

void MainWindow::onChatNotify(uint32_t senderId, const QString &senderName, const QString &text) {
    addChatMessage(senderName, text);
}

void MainWindow::onTimerUpdate(uint32_t itemId, uint32_t remainingSec) {
    // Update timer in table
    for (int row = 0; row < itemsTableWidget->rowCount(); ++row) {
        if (itemsTableWidget->item(row, 0)->text().toUInt() == itemId) {
            itemsTableWidget->item(row, 4)->setText(QString::number(remainingSec) + "s");
            break;
        }
    }
}

void MainWindow::onDisconnected() {
    QMessageBox::warning(this, "Disconnected", "Connection to server lost");
    close();
}

void MainWindow::onLogoutClicked() {
    ClientLogger::instance().logLogout(currentUsername);
    networkClient->disconnectFromServer();
    close();
}

void MainWindow::updateBalanceDisplay() {
    balanceLabel->setText(QString("Balance: %1 VND").arg(currentBalance));
}

void MainWindow::updateCurrentRoomDisplay() {
    if (currentRoomId == 0) {
        currentRoomLabel->setText("Not in any room");
        leaveRoomButton->setEnabled(false);
    } else {
        currentRoomLabel->setText(QString("Current Room: %1 (ID: %2)")
                                  .arg(currentRoomName).arg(currentRoomId));
        leaveRoomButton->setEnabled(true);
    }
}

void MainWindow::addChatMessage(const QString &sender, const QString &message) {
    QString timestamp = QDateTime::currentDateTime().toString("HH:mm:ss");
    chatDisplayEdit->append(QString("[%1] %2: %3").arg(timestamp).arg(sender).arg(message));
}
