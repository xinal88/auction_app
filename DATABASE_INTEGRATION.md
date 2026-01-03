# Database Integration Guide - Elite Auction UI

## Tổng quan

Hướng dẫn kết nối Elite Auction UI với database hiện tại của bạn.

---

## 🗄️ Database Structure

### Tables cần thiết:

```sql
-- Users table
CREATE TABLE users (
    user_id INT PRIMARY KEY AUTO_INCREMENT,
    username VARCHAR(50) UNIQUE NOT NULL,
    email VARCHAR(100) UNIQUE NOT NULL,
    password_hash VARCHAR(255) NOT NULL,
    balance DECIMAL(15,2) DEFAULT 0,
    bank_name VARCHAR(100),
    bank_account VARCHAR(50),
    account_holder VARCHAR(100),
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Auction Rooms table
CREATE TABLE auction_rooms (
    room_id INT PRIMARY KEY AUTO_INCREMENT,
    room_name VARCHAR(100) NOT NULL,
    description TEXT,
    host_user_id INT,
    is_public BOOLEAN DEFAULT TRUE,
    status ENUM('UPCOMING', 'LIVE', 'ENDED') DEFAULT 'UPCOMING',
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (host_user_id) REFERENCES users(user_id)
);

-- Items table
CREATE TABLE items (
    item_id INT PRIMARY KEY AUTO_INCREMENT,
    room_id INT,
    item_name VARCHAR(100) NOT NULL,
    description TEXT,
    start_price DECIMAL(15,2) NOT NULL,
    current_price DECIMAL(15,2),
    buy_now_price DECIMAL(15,2),
    duration_seconds INT DEFAULT 180,
    status ENUM('UPCOMING', 'ACTIVE', 'SOLD') DEFAULT 'UPCOMING',
    winner_user_id INT,
    FOREIGN KEY (room_id) REFERENCES auction_rooms(room_id),
    FOREIGN KEY (winner_user_id) REFERENCES users(user_id)
);

-- Bids table
CREATE TABLE bids (
    bid_id INT PRIMARY KEY AUTO_INCREMENT,
    item_id INT,
    user_id INT,
    bid_amount DECIMAL(15,2) NOT NULL,
    bid_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (item_id) REFERENCES items(item_id),
    FOREIGN KEY (user_id) REFERENCES users(user_id)
);

-- Transactions table
CREATE TABLE transactions (
    transaction_id INT PRIMARY KEY AUTO_INCREMENT,
    user_id INT,
    type ENUM('DEPOSIT', 'WITHDRAW', 'BID', 'WIN', 'REFUND'),
    amount DECIMAL(15,2) NOT NULL,
    description TEXT,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (user_id) REFERENCES users(user_id)
);

-- Chat Messages table
CREATE TABLE chat_messages (
    message_id INT PRIMARY KEY AUTO_INCREMENT,
    room_id INT,
    user_id INT,
    message TEXT NOT NULL,
    sent_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (room_id) REFERENCES auction_rooms(room_id),
    FOREIGN KEY (user_id) REFERENCES users(user_id)
);
```

---

## 📦 Cài đặt Qt SQL Module

### 1. Thêm vào .pro file:

```qmake
QT += core gui widgets network sql
```

### 2. Kiểm tra SQL drivers:

```cpp
#include <QSqlDatabase>
#include <QDebug>

qDebug() << "Available drivers:" << QSqlDatabase::drivers();
// Should show: QSQLITE, QMYSQL, QPSQL, etc.
```

---

## 🔌 Kết nối Database

### Tạo Database Manager class:

```cpp
// elite_database.h
#ifndef ELITE_DATABASE_H
#define ELITE_DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>

class EliteDatabase : public QObject
{
    Q_OBJECT

public:
    static EliteDatabase* instance();
    
    bool connect(const QString &host, const QString &dbName, 
                 const QString &user, const QString &password);
    void disconnect();
    bool isConnected();
    
    // User operations
    bool loginUser(const QString &email, const QString &password, int &userId);
    bool registerUser(const QString &username, const QString &email, const QString &password);
    double getUserBalance(int userId);
    bool updateUserBalance(int userId, double newBalance);
    
    // Room operations
    QList<QVariantMap> getAuctionRooms(const QString &filter = "all");
    int createAuctionRoom(const QString &name, const QString &description, 
                          int hostUserId, bool isPublic);
    
    // Transaction operations
    bool addTransaction(int userId, const QString &type, double amount, const QString &description);
    
    // Chat operations
    bool sendChatMessage(int roomId, int userId, const QString &message);
    QList<QVariantMap> getChatMessages(int roomId, int limit = 50);

private:
    explicit EliteDatabase(QObject *parent = nullptr);
    static EliteDatabase *m_instance;
    QSqlDatabase m_db;
};

#endif
```

### Implementation:

```cpp
// elite_database.cpp
#include "elite_database.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include <QCryptographicHash>

EliteDatabase* EliteDatabase::m_instance = nullptr;

EliteDatabase* EliteDatabase::instance()
{
    if (!m_instance) {
        m_instance = new EliteDatabase();
    }
    return m_instance;
}

EliteDatabase::EliteDatabase(QObject *parent)
    : QObject(parent)
{
}

bool EliteDatabase::connect(const QString &host, const QString &dbName,
                            const QString &user, const QString &password)
{
    m_db = QSqlDatabase::addDatabase("QMYSQL");
    m_db.setHostName(host);
    m_db.setDatabaseName(dbName);
    m_db.setUserName(user);
    m_db.setPassword(password);
    
    if (!m_db.open()) {
        qDebug() << "Database connection failed:" << m_db.lastError().text();
        return false;
    }
    
    qDebug() << "Database connected successfully!";
    return true;
}

void EliteDatabase::disconnect()
{
    if (m_db.isOpen()) {
        m_db.close();
    }
}

bool EliteDatabase::isConnected()
{
    return m_db.isOpen();
}

bool EliteDatabase::loginUser(const QString &email, const QString &password, int &userId)
{
    QSqlQuery query(m_db);
    query.prepare("SELECT user_id, password_hash FROM users WHERE email = :email");
    query.bindValue(":email", email);
    
    if (query.exec() && query.next()) {
        QString storedHash = query.value(1).toString();
        QString inputHash = QString(QCryptographicHash::hash(
            password.toUtf8(), QCryptographicHash::Sha256).toHex());
        
        if (storedHash == inputHash) {
            userId = query.value(0).toInt();
            return true;
        }
    }
    return false;
}

double EliteDatabase::getUserBalance(int userId)
{
    QSqlQuery query(m_db);
    query.prepare("SELECT balance FROM users WHERE user_id = :userId");
    query.bindValue(":userId", userId);
    
    if (query.exec() && query.next()) {
        return query.value(0).toDouble();
    }
    return 0.0;
}

bool EliteDatabase::updateUserBalance(int userId, double newBalance)
{
    QSqlQuery query(m_db);
    query.prepare("UPDATE users SET balance = :balance WHERE user_id = :userId");
    query.bindValue(":balance", newBalance);
    query.bindValue(":userId", userId);
    
    return query.exec();
}

QList<QVariantMap> EliteDatabase::getAuctionRooms(const QString &filter)
{
    QList<QVariantMap> rooms;
    QSqlQuery query(m_db);
    
    QString sql = "SELECT r.room_id, r.room_name, r.description, r.status, "
                  "u.username as host, COUNT(DISTINCT p.user_id) as participants "
                  "FROM auction_rooms r "
                  "LEFT JOIN users u ON r.host_user_id = u.user_id "
                  "LEFT JOIN room_participants p ON r.room_id = p.room_id "
                  "WHERE 1=1 ";
    
    if (filter == "live") {
        sql += "AND r.status = 'LIVE' ";
    } else if (filter == "upcoming") {
        sql += "AND r.status = 'UPCOMING' ";
    }
    
    sql += "GROUP BY r.room_id ORDER BY r.created_at DESC";
    
    if (query.exec(sql)) {
        while (query.next()) {
            QVariantMap room;
            room["room_id"] = query.value(0);
            room["room_name"] = query.value(1);
            room["description"] = query.value(2);
            room["status"] = query.value(3);
            room["host"] = query.value(4);
            room["participants"] = query.value(5);
            rooms.append(room);
        }
    }
    
    return rooms;
}

int EliteDatabase::createAuctionRoom(const QString &name, const QString &description,
                                     int hostUserId, bool isPublic)
{
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO auction_rooms (room_name, description, host_user_id, is_public) "
                  "VALUES (:name, :desc, :host, :public)");
    query.bindValue(":name", name);
    query.bindValue(":desc", description);
    query.bindValue(":host", hostUserId);
    query.bindValue(":public", isPublic);
    
    if (query.exec()) {
        return query.lastInsertId().toInt();
    }
    return -1;
}

bool EliteDatabase::addTransaction(int userId, const QString &type, 
                                   double amount, const QString &description)
{
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO transactions (user_id, type, amount, description) "
                  "VALUES (:userId, :type, :amount, :desc)");
    query.bindValue(":userId", userId);
    query.bindValue(":type", type);
    query.bindValue(":amount", amount);
    query.bindValue(":desc", description);
    
    return query.exec();
}

bool EliteDatabase::sendChatMessage(int roomId, int userId, const QString &message)
{
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO chat_messages (room_id, user_id, message) "
                  "VALUES (:roomId, :userId, :message)");
    query.bindValue(":roomId", roomId);
    query.bindValue(":userId", userId);
    query.bindValue(":message", message);
    
    return query.exec();
}

QList<QVariantMap> EliteDatabase::getChatMessages(int roomId, int limit)
{
    QList<QVariantMap> messages;
    QSqlQuery query(m_db);
    
    query.prepare("SELECT u.username, m.message, m.sent_at "
                  "FROM chat_messages m "
                  "JOIN users u ON m.user_id = u.user_id "
                  "WHERE m.room_id = :roomId "
                  "ORDER BY m.sent_at DESC LIMIT :limit");
    query.bindValue(":roomId", roomId);
    query.bindValue(":limit", limit);
    
    if (query.exec()) {
        while (query.next()) {
            QVariantMap msg;
            msg["username"] = query.value(0);
            msg["message"] = query.value(1);
            msg["sent_at"] = query.value(2);
            messages.append(msg);
        }
    }
    
    return messages;
}
```

---

## 🔗 Tích hợp vào UI

### 1. Kết nối database khi khởi động:

```cpp
// elite_auction_main.cpp
#include <QApplication>
#include "elite_login_window.h"
#include "elite_database.h"
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    // Connect to database
    EliteDatabase *db = EliteDatabase::instance();
    if (!db->connect("localhost", "auction_db", "root", "password")) {
        QMessageBox::critical(nullptr, "Database Error", 
            "Failed to connect to database!");
        return 1;
    }
    
    EliteLoginWindow loginWindow;
    loginWindow.show();
    
    int result = app.exec();
    
    db->disconnect();
    return result;
}
```

### 2. Update Login Window:

```cpp
void EliteLoginWindow::onLoginClicked()
{
    QString email = emailInput->text();
    QString password = passwordInput->text();
    
    int userId;
    if (EliteDatabase::instance()->loginUser(email, password, userId)) {
        // Store userId for session
        if (!mainWindow) {
            mainWindow = new EliteMainWindow();
            mainWindow->setUserId(userId);
        }
        mainWindow->show();
        this->hide();
    } else {
        QMessageBox::warning(this, "Login Failed", 
            "Invalid email or password!");
    }
}
```

### 3. Load Auction Rooms:

```cpp
void EliteMainWindow::loadAuctionRooms()
{
    // Clear existing rooms
    QLayoutItem *item;
    while ((item = roomsLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }
    
    // Load from database
    QList<QVariantMap> rooms = EliteDatabase::instance()->getAuctionRooms(currentFilter);
    
    for (const QVariantMap &room : rooms) {
        QString title = room["room_name"].toString();
        QString description = room["description"].toString();
        QString host = room["host"].toString();
        int participants = room["participants"].toInt();
        QString status = room["status"].toString();
        
        roomsLayout->addWidget(createRoomCard(title, description, host, participants, status));
    }
    
    roomsLayout->addStretch();
}
```

### 4. Create Room with Database:

```cpp
void EliteMainWindow::onCreateRoomClicked()
{
    CreateRoomDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QString roomName = dialog.getRoomName();
        QString description = dialog.getDescription();
        bool isPublic = dialog.isPublic();
        
        if (!roomName.isEmpty()) {
            int roomId = EliteDatabase::instance()->createAuctionRoom(
                roomName, description, currentUserId, isPublic);
            
            if (roomId > 0) {
                QMessageBox::information(this, "Success", 
                    QString("Room '%1' created successfully!").arg(roomName));
                loadAuctionRooms(); // Refresh list
            } else {
                QMessageBox::warning(this, "Error", "Failed to create room!");
            }
        }
    }
}
```

### 5. Deposit/Withdraw with Database:

```cpp
void EliteAccountWindow::onDepositClicked()
{
    DepositMoneyDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        double amount = dialog.getAmount();
        
        // Get current balance
        double currentBalance = EliteDatabase::instance()->getUserBalance(currentUserId);
        double newBalance = currentBalance + amount;
        
        // Update database
        if (EliteDatabase::instance()->updateUserBalance(currentUserId, newBalance)) {
            EliteDatabase::instance()->addTransaction(currentUserId, "DEPOSIT", 
                amount, "Deposit to account");
            
            QMessageBox::information(this, "Success", 
                QString("Deposited %1 đ successfully!").arg(amount, 0, 'f', 0));
            
            balanceLabel->setText(QString("%1 đ").arg(newBalance, 0, 'f', 0));
        } else {
            QMessageBox::warning(this, "Error", "Failed to deposit money!");
        }
    }
}
```

---

## 📝 Configuration File

Tạo file config để lưu database credentials:

```ini
# database.ini
[Database]
host=localhost
port=3306
database=auction_db
username=root
password=your_password
```

Load config:

```cpp
#include <QSettings>

void loadDatabaseConfig()
{
    QSettings settings("database.ini", QSettings::IniFormat);
    settings.beginGroup("Database");
    
    QString host = settings.value("host", "localhost").toString();
    QString dbName = settings.value("database", "auction_db").toString();
    QString user = settings.value("username", "root").toString();
    QString password = settings.value("password", "").toString();
    
    settings.endGroup();
    
    EliteDatabase::instance()->connect(host, dbName, user, password);
}
```

---

## ✅ Checklist Integration

- [ ] Tạo database schema
- [ ] Thêm Qt SQL module vào .pro
- [ ] Tạo EliteDatabase class
- [ ] Kết nối database khi khởi động
- [ ] Update Login với database
- [ ] Load auction rooms từ database
- [ ] Create room lưu vào database
- [ ] Deposit/Withdraw update database
- [ ] Chat messages lưu vào database
- [ ] Bid history lưu vào database

---

## 🚀 Next Steps

1. Tạo database schema
2. Test connection
3. Implement từng feature một
4. Test thoroughly
5. Add error handling
6. Optimize queries

---

**Good luck with database integration!** 🎉
