#include "elite_main_window.h"
#include "elite_auction_room.h"
#include "elite_account_window.h"
#include "elite_network_client.h"
#include "elite_dialogs.h"
#include "elite_database.h"
#include <QGraphicsDropShadowEffect>
#include <QScrollBar>
#include <QEvent>
#include <QMouseEvent>
#include <QColor>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPixmap>

EliteMainWindow::EliteMainWindow(QWidget *parent)
    : QMainWindow(parent), currentFilter("all"), currentUserId(1)
{
    networkClient = new EliteNetworkClient(this);
    networkManager = new QNetworkAccessManager(this);
    
    // Setup UI first (so window can display even if database fails)
    setupUI();
    setStyleSheet(getStyleSheet());
    
    // Enable maximize and fullscreen
    setWindowFlags(Qt::Window);
    
    // Try to connect to database (non-blocking)
    EliteDatabase *db = EliteDatabase::instance();
    if (db->connectToDatabase("localhost", "auction_db", "postgres", "72488")) {
        qDebug() << "Database connected successfully!";
        qDebug() << "Loading rooms and user data...";
        loadUserBalance();
        loadRoomsFromDatabase();
    } else {
        qDebug() << "Database connection failed:" << db->lastError();
        // Show warning but don't block the UI
        QMessageBox::warning(this, "Database Connection", 
            QString("Could not connect to database:\n%1\n\n"
                   "The app will run in demo mode without database.\n\n"
                   "To fix this:\n"
                   "1. Make sure PostgreSQL is running\n"
                   "2. Check database 'auction_db' exists\n"
                   "3. Verify password in elite_main_window.cpp line 25 (currently: 72488)\n"
                   "4. Ensure user 'postgres' has access").arg(db->lastError()));
        
        // Load demo data instead
        loadDemoRooms();
    }
}

EliteMainWindow::~EliteMainWindow()
{
}

void EliteMainWindow::setupUI()
{
    setWindowTitle("AuctionHub - Discover Auctions");
    resize(1400, 900);
    
    QWidget *centralWidget = new QWidget();
    setCentralWidget(centralWidget);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    
    // Navigation bar
    setupNavigationBar();
    mainLayout->addWidget(navBar);
    
    // Stacked widget for pages
    stackedWidget = new QStackedWidget();
    
    setupExplorePage();
    setupRoomsPage();
    
    accountPage = new EliteAccountWindow();
    auctionRoomPage = new EliteAuctionRoom();
    
    stackedWidget->addWidget(explorePage);
    stackedWidget->addWidget(roomsPage);
    stackedWidget->addWidget(accountPage);
    stackedWidget->addWidget(auctionRoomPage);
    
    mainLayout->addWidget(stackedWidget);
}

void EliteMainWindow::setupNavigationBar()
{
    navBar = new QWidget();
    navBar->setObjectName("navBar");
    navBar->setFixedHeight(70);
    
    QHBoxLayout *navLayout = new QHBoxLayout(navBar);
    navLayout->setContentsMargins(30, 0, 30, 0);
    
    // Logo
    QLabel *logoLabel = new QLabel("🔨 AuctionHub");
    logoLabel->setObjectName("logoLabel");
    
    navLayout->addWidget(logoLabel);
    navLayout->addSpacing(50);
    
    // Navigation buttons
    exploreBtn = new QPushButton("Explore");
    exploreBtn->setObjectName("navButton");
    exploreBtn->setProperty("active", true);
    exploreBtn->setCursor(Qt::PointingHandCursor);
    
    roomsBtn = new QPushButton("Rooms");
    roomsBtn->setObjectName("navButton");
    roomsBtn->setCursor(Qt::PointingHandCursor);
    
    accountBtn = new QPushButton("Account");
    accountBtn->setObjectName("navButton");
    accountBtn->setCursor(Qt::PointingHandCursor);
    
    navLayout->addWidget(exploreBtn);
    navLayout->addWidget(roomsBtn);
    navLayout->addWidget(accountBtn);
    navLayout->addStretch();
    
    // Balance display
    balanceLabel = new QLabel("💰 10,000,000 đ");
    balanceLabel->setObjectName("balanceLabel");
    
    // Create room button
    createRoomBtn = new QPushButton("+ Create Room");
    createRoomBtn->setObjectName("primaryButton");
    createRoomBtn->setFixedHeight(40);
    createRoomBtn->setCursor(Qt::PointingHandCursor);
    
    navLayout->addWidget(balanceLabel);
    navLayout->addSpacing(20);
    navLayout->addWidget(createRoomBtn);
    
    // Connect signals
    connect(exploreBtn, &QPushButton::clicked, this, &EliteMainWindow::onExploreClicked);
    connect(roomsBtn, &QPushButton::clicked, this, &EliteMainWindow::onRoomsClicked);
    connect(accountBtn, &QPushButton::clicked, this, &EliteMainWindow::onAccountClicked);
    connect(createRoomBtn, &QPushButton::clicked, this, &EliteMainWindow::onCreateRoomClicked);
}

void EliteMainWindow::setupExplorePage()
{
    explorePage = new QWidget();
    explorePage->setObjectName("explorePage");
    
    QVBoxLayout *pageLayout = new QVBoxLayout(explorePage);
    pageLayout->setContentsMargins(40, 40, 40, 40);
    pageLayout->setSpacing(30);
    
    // Header
    QLabel *headerLabel = new QLabel("Discover Auctions");
    headerLabel->setObjectName("pageHeader");
    
    QLabel *subheaderLabel = new QLabel("Join live auctions and bid on exclusive items");
    subheaderLabel->setObjectName("pageSubheader");
    
    pageLayout->addWidget(headerLabel);
    pageLayout->addWidget(subheaderLabel);
    
    // Search and filters
    QWidget *searchWidget = new QWidget();
    QHBoxLayout *searchLayout = new QHBoxLayout(searchWidget);
    searchLayout->setContentsMargins(0, 0, 0, 0);
    searchLayout->setSpacing(15);
    
    searchInput = new QLineEdit();
    searchInput->setObjectName("searchInput");
    searchInput->setPlaceholderText("🔍 Search auction rooms...");
    searchInput->setFixedHeight(48);
    
    liveFilterBtn = new QPushButton("🔴 Live");
    liveFilterBtn->setObjectName("filterButton");
    liveFilterBtn->setFixedHeight(48);
    liveFilterBtn->setCheckable(true);
    liveFilterBtn->setCursor(Qt::PointingHandCursor);
    
    upcomingFilterBtn = new QPushButton("📅 Upcoming");
    upcomingFilterBtn->setObjectName("filterButton");
    upcomingFilterBtn->setFixedHeight(48);
    upcomingFilterBtn->setCheckable(true);
    upcomingFilterBtn->setCursor(Qt::PointingHandCursor);
    
    searchLayout->addWidget(searchInput, 1);
    searchLayout->addWidget(liveFilterBtn);
    searchLayout->addWidget(upcomingFilterBtn);
    
    pageLayout->addWidget(searchWidget);
    
    // Rooms scroll area
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setObjectName("scrollArea");
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    
    roomsContainer = new QWidget();
    roomsLayout = new QVBoxLayout(roomsContainer);
    roomsLayout->setSpacing(20);
    roomsLayout->setContentsMargins(0, 0, 0, 0);
    
    // Rooms will be loaded from database
    roomsLayout->addStretch();
    
    scrollArea->setWidget(roomsContainer);
    pageLayout->addWidget(scrollArea);
    
    connect(searchInput, &QLineEdit::textChanged, this, &EliteMainWindow::onSearchTextChanged);
    connect(liveFilterBtn, &QPushButton::clicked, [this]() {
        currentFilter = liveFilterBtn->isChecked() ? "live" : "all";
        loadRoomsFromDatabase();
    });
    connect(upcomingFilterBtn, &QPushButton::clicked, [this]() {
        currentFilter = upcomingFilterBtn->isChecked() ? "upcoming" : "all";
        loadRoomsFromDatabase();
    });
}

void EliteMainWindow::setupRoomsPage()
{
    roomsPage = new QWidget();
    roomsPage->setObjectName("roomsPage");
    
    QVBoxLayout *pageLayout = new QVBoxLayout(roomsPage);
    pageLayout->setContentsMargins(40, 40, 40, 40);
    
    QLabel *headerLabel = new QLabel("My Rooms");
    headerLabel->setObjectName("pageHeader");
    
    pageLayout->addWidget(headerLabel);
    pageLayout->addStretch();
}

QWidget* EliteMainWindow::createRoomCard(int roomId, const QString &title, const QString &description,
                                         const QString &host, int participants, const QString &status,
                                         const QString &imageUrl)
{
    QWidget *card = new QWidget();
    card->setObjectName("roomCard");
    card->setFixedHeight(180);
    card->setCursor(Qt::PointingHandCursor);
    
    QHBoxLayout *cardLayout = new QHBoxLayout(card);
    cardLayout->setContentsMargins(0, 0, 0, 0);
    cardLayout->setSpacing(0);
    
    // Image
    QLabel *imageLabel = new QLabel();
    imageLabel->setObjectName("roomImage");
    imageLabel->setFixedSize(240, 180);
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setScaledContents(true);
    
    // Load image from URL
    if (!imageUrl.isEmpty()) {
        loadImageForLabel(imageLabel, imageUrl);
    } else {
        imageLabel->setText("🖼️");
        imageLabel->setStyleSheet("font-size: 48px; background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #667eea, stop:1 #764ba2);");
    }
    
    // Content
    QWidget *contentWidget = new QWidget();
    QVBoxLayout *contentLayout = new QVBoxLayout(contentWidget);
    contentLayout->setContentsMargins(25, 20, 25, 20);
    contentLayout->setSpacing(10);
    
    // Status badge
    QString statusText = (status == "active") ? "LIVE" : "UPCOMING";
    QLabel *statusBadge = new QLabel(statusText);
    statusBadge->setObjectName((status == "active") ? "liveBadge" : "upcomingBadge");
    statusBadge->setFixedWidth(80);
    statusBadge->setAlignment(Qt::AlignCenter);
    
    // Title
    QLabel *titleLabel = new QLabel(title);
    titleLabel->setObjectName("roomTitle");
    
    // Description
    QLabel *descLabel = new QLabel(description);
    descLabel->setObjectName("roomDescription");
    descLabel->setWordWrap(true);
    
    // Host and participants
    QWidget *metaWidget = new QWidget();
    QHBoxLayout *metaLayout = new QHBoxLayout(metaWidget);
    metaLayout->setContentsMargins(0, 0, 0, 0);
    metaLayout->setSpacing(20);
    
    QLabel *hostLabel = new QLabel("Host: " + host);
    hostLabel->setObjectName("roomMeta");
    
    QLabel *participantsLabel = new QLabel(QString("👥 %1 participants").arg(participants));
    participantsLabel->setObjectName("roomMeta");
    
    metaLayout->addWidget(hostLabel);
    metaLayout->addWidget(participantsLabel);
    metaLayout->addStretch();
    
    contentLayout->addWidget(statusBadge);
    contentLayout->addWidget(titleLabel);
    contentLayout->addWidget(descLabel);
    contentLayout->addStretch();
    contentLayout->addWidget(metaWidget);
    
    cardLayout->addWidget(imageLabel);
    cardLayout->addWidget(contentWidget, 1);
    
    // Shadow effect
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();
    shadow->setBlurRadius(20);
    shadow->setXOffset(0);
    shadow->setYOffset(4);
    shadow->setColor(QColor(0, 0, 0, 20));
    card->setGraphicsEffect(shadow);
    
    // Make clickable
    card->installEventFilter(this);
    card->setProperty("roomId", roomId);
    card->setProperty("roomName", title);
    
    return card;
}



void EliteMainWindow::onExploreClicked()
{
    exploreBtn->setProperty("active", true);
    roomsBtn->setProperty("active", false);
    accountBtn->setProperty("active", false);
    
    exploreBtn->style()->unpolish(exploreBtn);
    exploreBtn->style()->polish(exploreBtn);
    roomsBtn->style()->unpolish(roomsBtn);
    roomsBtn->style()->polish(roomsBtn);
    accountBtn->style()->unpolish(accountBtn);
    accountBtn->style()->polish(accountBtn);
    
    stackedWidget->setCurrentWidget(explorePage);
}

void EliteMainWindow::onRoomsClicked()
{
    exploreBtn->setProperty("active", false);
    roomsBtn->setProperty("active", true);
    accountBtn->setProperty("active", false);
    
    exploreBtn->style()->unpolish(exploreBtn);
    exploreBtn->style()->polish(exploreBtn);
    roomsBtn->style()->unpolish(roomsBtn);
    roomsBtn->style()->polish(roomsBtn);
    accountBtn->style()->unpolish(accountBtn);
    accountBtn->style()->polish(accountBtn);
    
    stackedWidget->setCurrentWidget(roomsPage);
}

void EliteMainWindow::onAccountClicked()
{
    exploreBtn->setProperty("active", false);
    roomsBtn->setProperty("active", false);
    accountBtn->setProperty("active", true);
    
    exploreBtn->style()->unpolish(exploreBtn);
    exploreBtn->style()->polish(exploreBtn);
    roomsBtn->style()->unpolish(roomsBtn);
    roomsBtn->style()->polish(roomsBtn);
    accountBtn->style()->unpolish(accountBtn);
    accountBtn->style()->polish(accountBtn);
    
    stackedWidget->setCurrentWidget(accountPage);
}

void EliteMainWindow::onCreateRoomClicked()
{
    CreateRoomDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QString roomName = dialog.getRoomName();
        QString description = dialog.getDescription();
        bool isPublic = dialog.isPublic();
        Q_UNUSED(isPublic);
        
        if (!roomName.isEmpty()) {
            QMessageBox::information(this, "Success", 
                QString("Room '%1' created successfully!").arg(roomName));
            // TODO: Send to server to create room
        }
    }
}

void EliteMainWindow::onRoomCardClicked(const QString &roomName)
{
    QWidget *card = qobject_cast<QWidget*>(sender());
    int roomId = 1; // Default
    
    if (card) {
        roomId = card->property("roomId").toInt();
    }
    
    auctionRoomPage->setRoomName(roomName);
    auctionRoomPage->setRoomId(roomId);
    stackedWidget->setCurrentWidget(auctionRoomPage);
}

void EliteMainWindow::onSearchTextChanged(const QString &text)
{
    QString searchText = text.toLower().trimmed();
    
    // Clear existing rooms
    while (roomsLayout->count() > 1) {
        QLayoutItem *item = roomsLayout->takeAt(0);
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }
    
    // Load rooms from database
    EliteDatabase *db = EliteDatabase::instance();
    if (!db->isConnected()) {
        loadDemoRooms();
        return;
    }
    
    QList<QVariantMap> rooms = db->getAuctionRooms(currentFilter);
    
    // Filter by search text
    bool hasResults = false;
    for (const QVariantMap &room : rooms) {
        QString roomName = room["room_name"].toString().toLower();
        QString description = room["description"].toString().toLower();
        
        if (searchText.isEmpty() || roomName.contains(searchText) || description.contains(searchText)) {
            QWidget *card = createRoomCard(
                room["room_id"].toInt(),
                room["room_name"].toString(),
                room["description"].toString(),
                room["host_name"].toString(),
                room["participant_count"].toInt(),
                room["status"].toString(),
                room["image_url"].toString()
            );
            roomsLayout->insertWidget(roomsLayout->count() - 1, card);
            hasResults = true;
        }
    }
    
    if (!hasResults) {
        QLabel *emptyLabel = new QLabel(QString("No rooms found matching '%1'").arg(text));
        emptyLabel->setAlignment(Qt::AlignCenter);
        emptyLabel->setStyleSheet("font-size: 16px; color: #718096; padding: 40px;");
        roomsLayout->insertWidget(0, emptyLabel);
    }
}

bool EliteMainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        QWidget *widget = qobject_cast<QWidget*>(obj);
        if (widget && widget->objectName() == "roomCard") {
            QString roomName = widget->property("roomName").toString();
            int roomId = widget->property("roomId").toInt();
            
            auctionRoomPage->setRoomName(roomName);
            auctionRoomPage->setRoomId(roomId);
            stackedWidget->setCurrentWidget(auctionRoomPage);
            return true;
        }
    }
    return QMainWindow::eventFilter(obj, event);
}

void EliteMainWindow::loadRoomsFromDatabase()
{
    // Clear existing rooms
    while (roomsLayout->count() > 1) {
        QLayoutItem *item = roomsLayout->takeAt(0);
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }
    
    // Load rooms from database
    EliteDatabase *db = EliteDatabase::instance();
    if (!db->isConnected()) {
        loadDemoRooms();
        return;
    }
    
    QList<QVariantMap> rooms = db->getAuctionRooms(currentFilter);
    
    if (rooms.isEmpty()) {
        QLabel *emptyLabel = new QLabel("No auction rooms found. Create one to get started!");
        emptyLabel->setAlignment(Qt::AlignCenter);
        emptyLabel->setStyleSheet("font-size: 16px; color: #718096; padding: 40px;");
        roomsLayout->insertWidget(0, emptyLabel);
    } else {
        for (const QVariantMap &room : rooms) {
            QWidget *card = createRoomCard(
                room["room_id"].toInt(),
                room["room_name"].toString(),
                room["description"].toString(),
                room["host_name"].toString(),
                room["participant_count"].toInt(),
                room["status"].toString(),
                room["image_url"].toString()
            );
            roomsLayout->insertWidget(roomsLayout->count() - 1, card);
        }
    }
}

void EliteMainWindow::loadDemoRooms()
{
    // Clear existing rooms
    while (roomsLayout->count() > 1) {
        QLayoutItem *item = roomsLayout->takeAt(0);
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }
    
    // Add demo rooms for testing without database
    QList<QVariantMap> demoRooms;
    
    QVariantMap room1;
    room1["room_id"] = 1;
    room1["room_name"] = "Luxury Watches Auction";
    room1["description"] = "Premium timepieces from renowned brands";
    room1["host_name"] = "Demo Host";
    room1["participant_count"] = 24;
    room1["status"] = "active";
    room1["image_url"] = "https://images.unsplash.com/photo-1523170335258-f5ed11844a49?w=400";
    demoRooms.append(room1);
    
    QVariantMap room2;
    room2["room_id"] = 2;
    room2["room_name"] = "Vintage Electronics";
    room2["description"] = "Rare collectible electronics and gadgets";
    room2["host_name"] = "Demo Host";
    room2["participant_count"] = 18;
    room2["status"] = "active";
    room2["image_url"] = "https://images.unsplash.com/photo-1550009158-9ebf69173e03?w=400";
    demoRooms.append(room2);
    
    QVariantMap room3;
    room3["room_id"] = 3;
    room3["room_name"] = "Art & Collectibles";
    room3["description"] = "Fine art and unique collectible items";
    room3["host_name"] = "Demo Host";
    room3["participant_count"] = 32;
    room3["status"] = "upcoming";
    room3["image_url"] = "https://images.unsplash.com/photo-1561214115-f2f134cc4912?w=400";
    demoRooms.append(room3);
    
    // Filter based on current filter
    for (const QVariantMap &room : demoRooms) {
        if (currentFilter == "all" || 
            (currentFilter == "live" && room["status"].toString() == "active") ||
            (currentFilter == "upcoming" && room["status"].toString() == "upcoming")) {
            
            QWidget *card = createRoomCard(
                room["room_id"].toInt(),
                room["room_name"].toString(),
                room["description"].toString(),
                room["host_name"].toString(),
                room["participant_count"].toInt(),
                room["status"].toString(),
                room["image_url"].toString()
            );
            roomsLayout->insertWidget(roomsLayout->count() - 1, card);
        }
    }
}

void EliteMainWindow::loadUserBalance()
{
    EliteDatabase *db = EliteDatabase::instance();
    double balance = db->getUserBalance(currentUserId);
    balanceLabel->setText(QString("💰 %L1 đ").arg(balance, 0, 'f', 0));
}

void EliteMainWindow::loadImageForLabel(QLabel *label, const QString &url)
{
    QNetworkRequest request(url);
    QNetworkReply *reply = networkManager->get(request);
    
    connect(reply, &QNetworkReply::finished, [this, reply, label]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray data = reply->readAll();
            QPixmap pixmap;
            if (pixmap.loadFromData(data)) {
                label->setPixmap(pixmap.scaled(240, 180, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
            }
        } else {
            // Fallback to emoji if image fails to load
            label->setText("🖼️");
            label->setStyleSheet("font-size: 48px; background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #667eea, stop:1 #764ba2);");
        }
        reply->deleteLater();
    });
}

QString EliteMainWindow::getStyleSheet()
{
    return R"(
        * {
            font-family: 'Segoe UI', sans-serif;
        }
        
        QMainWindow {
            background-color: #F8F9FA;
        }
        
        QWidget {
            background-color: transparent;
            color: #1A202C;
            border: none;
        }
        
        #navBar {
            background-color: white;
            border: none;
            border-bottom: 1px solid #E2E8F0;
        }
        
        #logoLabel {
            font-size: 20px;
            font-weight: 700;
            color: #1A202C;
        }
        
        #navButton {
            background-color: transparent;
            border: none;
            color: #718096;
            font-size: 15px;
            font-weight: 500;
            padding: 8px 20px;
            border-radius: 6px;
        }
        
        #navButton:hover {
            background-color: #F7FAFC;
            color: #2D3748;
        }
        
        #navButton[active="true"] {
            color: #4F46E5;
            background-color: #EEF2FF;
        }
        
        #balanceLabel {
            font-size: 15px;
            font-weight: 600;
            color: #2D3748;
            background-color: #F7FAFC;
            padding: 10px 20px;
            border-radius: 8px;
            border: none;
        }
        
        #primaryButton {
            background-color: #4F46E5;
            color: white;
            border: none;
            border-radius: 8px;
            font-size: 14px;
            font-weight: 600;
            padding: 0 24px;
        }
        
        #primaryButton:hover {
            background-color: #4338CA;
        }
        
        #explorePage, #roomsPage {
            background-color: #F8F9FA;
        }
        
        #pageHeader {
            font-size: 36px;
            font-weight: 700;
            color: #1A202C;
        }
        
        #pageSubheader {
            font-size: 16px;
            color: #718096;
            margin-top: -15px;
        }
        
        #searchInput {
            border: 2px solid #E2E8F0;
            border-radius: 12px;
            padding: 0 20px;
            font-size: 15px;
            background-color: white;
            color: #1A202C;
        }
        
        #searchInput:focus {
            border: 2px solid #4F46E5;
            outline: none;
        }
        
        #filterButton {
            background-color: white;
            border: 2px solid #E2E8F0;
            border-radius: 12px;
            color: #2D3748;
            font-size: 14px;
            font-weight: 600;
            padding: 0 24px;
        }
        
        #filterButton:hover {
            border-color: #CBD5E0;
            background-color: #F7FAFC;
        }
        
        #filterButton:checked {
            background-color: #4F46E5;
            border-color: #4F46E5;
            color: white;
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
        
        #roomCard {
            background-color: white;
            border-radius: 16px;
            border: none;
        }
        
        #roomCard:hover {
            background-color: #FAFAFA;
        }
        
        #roomImage {
            border-radius: 16px 0 0 16px;
            border: none;
        }
        
        #liveBadge {
            background-color: #FEE2E2;
            color: #DC2626;
            font-size: 12px;
            font-weight: 700;
            padding: 6px 14px;
            border-radius: 6px;
            border: none;
        }
        
        #upcomingBadge {
            background-color: #FEF3C7;
            color: #D97706;
            font-size: 12px;
            font-weight: 700;
            padding: 6px 14px;
            border-radius: 6px;
            border: none;
        }
        
        #roomTitle {
            font-size: 20px;
            font-weight: 700;
            color: #1A202C;
            border: none;
        }
        
        #roomDescription {
            font-size: 14px;
            color: #718096;
            border: none;
        }
        
        #roomMeta {
            font-size: 13px;
            color: #A0AEC0;
            border: none;
        }
        
        QLabel {
            border: none;
        }
    )";
}
