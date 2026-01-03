#include "elite_database.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include <QCryptographicHash>
#include <QDateTime>

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

bool EliteDatabase::connectToDatabase(const QString &host, const QString &dbName,
                                      const QString &user, const QString &password)
{
    m_db = QSqlDatabase::addDatabase("QPSQL");
    m_db.setHostName(host);
    m_db.setDatabaseName(dbName);
    m_db.setUserName(user);
    m_db.setPassword(password);

    if (!m_db.open()) {
        m_lastError = m_db.lastError().text();
        emit errorOccurred(m_lastError);
        emit connectionStatusChanged(false);
        return false;
    }

    emit connectionStatusChanged(true);
    return true;
}

void EliteDatabase::disconnect()
{
    if (m_db.isOpen()) {
        m_db.close();
        emit connectionStatusChanged(false);
    }
}

bool EliteDatabase::isConnected()
{
    return m_db.isOpen();
}

QString EliteDatabase::lastError()
{
    return m_lastError;
}

QString EliteDatabase::hashPassword(const QString &password)
{
    return QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex());
}

bool EliteDatabase::loginUser(const QString &email, const QString &password, int &userId, QString &username)
{
    QSqlQuery query(m_db);
    query.prepare("SELECT user_id, username FROM users WHERE email = :email AND password_hash = :password");
    query.bindValue(":email", email);
    query.bindValue(":password", password); // In production, use hashPassword(password)

    if (query.exec() && query.next()) {
        userId = query.value(0).toInt();
        username = query.value(1).toString();
        return true;
    }

    m_lastError = query.lastError().text();
    return false;
}

bool EliteDatabase::registerUser(const QString &username, const QString &email, const QString &password)
{
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO users (username, email, password_hash, balance) "
                  "VALUES (:username, :email, :password, 10000000)");
    query.bindValue(":username", username);
    query.bindValue(":email", email);
    query.bindValue(":password", password); // In production, use hashPassword(password)

    if (query.exec()) {
        return true;
    }

    m_lastError = query.lastError().text();
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

QVariantMap EliteDatabase::getUserInfo(int userId)
{
    QVariantMap userInfo;
    QSqlQuery query(m_db);
    query.prepare("SELECT user_id, username, email, balance, bank_name, bank_account "
                  "FROM users WHERE user_id = :userId");
    query.bindValue(":userId", userId);

    if (query.exec() && query.next()) {
        userInfo["user_id"] = query.value(0).toInt();
        userInfo["username"] = query.value(1).toString();
        userInfo["email"] = query.value(2).toString();
        userInfo["balance"] = query.value(3).toDouble();
        userInfo["bank_name"] = query.value(4).toString();
        userInfo["bank_account"] = query.value(5).toString();
    }

    return userInfo;
}

QList<QVariantMap> EliteDatabase::getAuctionRooms(const QString &filter)
{
    QList<QVariantMap> rooms;
    QSqlQuery query(m_db);

    QString sql = "SELECT r.room_id, r.room_name, r.description, r.status, "
                  "r.participant_count, r.image_url, u.username as host_name "
                  "FROM auction_rooms r "
                  "JOIN users u ON r.created_by = u.user_id ";

    if (filter == "live") {
        sql += "WHERE r.status = 'active' ";
    } else if (filter == "upcoming") {
        sql += "WHERE r.status = 'upcoming' ";
    }

    sql += "ORDER BY r.created_at DESC";

    if (query.exec(sql)) {
        while (query.next()) {
            QVariantMap room;
            room["room_id"] = query.value(0).toInt();
            room["room_name"] = query.value(1).toString();
            room["description"] = query.value(2).toString();
            room["status"] = query.value(3).toString();
            room["participant_count"] = query.value(4).toInt();
            room["image_url"] = query.value(5).toString();
            room["host_name"] = query.value(6).toString();
            rooms.append(room);
        }
    } else {
        m_lastError = query.lastError().text();
    }

    return rooms;
}

int EliteDatabase::createAuctionRoom(const QString &name, const QString &description,
                                     int hostUserId, bool isPublic)
{
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO auction_rooms (room_name, description, created_by, status) "
                  "VALUES (:name, :description, :userId, 'active') RETURNING room_id");
    query.bindValue(":name", name);
    query.bindValue(":description", description);
    query.bindValue(":userId", hostUserId);

    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    }

    m_lastError = query.lastError().text();
    return -1;
}

QVariantMap EliteDatabase::getRoomDetails(int roomId)
{
    QVariantMap roomDetails;
    QSqlQuery query(m_db);
    query.prepare("SELECT r.room_id, r.room_name, r.description, r.status, "
                  "r.participant_count, r.image_url, u.username as host_name "
                  "FROM auction_rooms r "
                  "JOIN users u ON r.created_by = u.user_id "
                  "WHERE r.room_id = :roomId");
    query.bindValue(":roomId", roomId);

    if (query.exec() && query.next()) {
        roomDetails["room_id"] = query.value(0).toInt();
        roomDetails["room_name"] = query.value(1).toString();
        roomDetails["description"] = query.value(2).toString();
        roomDetails["status"] = query.value(3).toString();
        roomDetails["participant_count"] = query.value(4).toInt();
        roomDetails["image_url"] = query.value(5).toString();
        roomDetails["host_name"] = query.value(6).toString();
    }

    return roomDetails;
}

QList<QVariantMap> EliteDatabase::getRoomItems(int roomId)
{
    QList<QVariantMap> items;
    QSqlQuery query(m_db);
    query.prepare("SELECT item_id, item_name, description, starting_price, "
                  "current_price, buy_now_price, status, queue_position, image_url "
                  "FROM auction_items "
                  "WHERE room_id = :roomId "
                  "ORDER BY queue_position ASC");
    query.bindValue(":roomId", roomId);

    if (query.exec()) {
        while (query.next()) {
            QVariantMap item;
            item["item_id"] = query.value(0).toInt();
            item["item_name"] = query.value(1).toString();
            item["description"] = query.value(2).toString();
            item["starting_price"] = query.value(3).toDouble();
            item["current_price"] = query.value(4).toDouble();
            item["buy_now_price"] = query.value(5).toDouble();
            item["status"] = query.value(6).toString();
            item["queue_position"] = query.value(7).toInt();
            item["image_url"] = query.value(8).toString();
            items.append(item);
        }
    } else {
        m_lastError = query.lastError().text();
    }

    return items;
}

QVariantMap EliteDatabase::getCurrentItem(int roomId)
{
    QVariantMap item;
    QSqlQuery query(m_db);
    query.prepare("SELECT item_id, item_name, description, starting_price, "
                  "current_price, buy_now_price, auction_duration, image_url "
                  "FROM auction_items "
                  "WHERE room_id = :roomId AND status = 'active' "
                  "ORDER BY queue_position ASC LIMIT 1");
    query.bindValue(":roomId", roomId);

    if (query.exec() && query.next()) {
        item["item_id"] = query.value(0).toInt();
        item["item_name"] = query.value(1).toString();
        item["description"] = query.value(2).toString();
        item["starting_price"] = query.value(3).toDouble();
        item["current_price"] = query.value(4).toDouble();
        item["buy_now_price"] = query.value(5).toDouble();
        item["auction_duration"] = query.value(6).toInt();
        item["image_url"] = query.value(7).toString();
    }

    return item;
}

bool EliteDatabase::updateItemPrice(int itemId, double newPrice, int bidderId)
{
    QSqlQuery query(m_db);

    // Start transaction
    m_db.transaction();

    // Update item price
    query.prepare("UPDATE auction_items SET current_price = :price WHERE item_id = :itemId");
    query.bindValue(":price", newPrice);
    query.bindValue(":itemId", itemId);

    if (!query.exec()) {
        m_db.rollback();
        m_lastError = query.lastError().text();
        return false;
    }

    // Insert bid record
    query.prepare("INSERT INTO bids (item_id, user_id, bid_amount) "
                  "VALUES (:itemId, :userId, :amount)");
    query.bindValue(":itemId", itemId);
    query.bindValue(":userId", bidderId);
    query.bindValue(":amount", newPrice);

    if (!query.exec()) {
        m_db.rollback();
        m_lastError = query.lastError().text();
        return false;
    }

    m_db.commit();
    return true;
}

bool EliteDatabase::addTransaction(int userId, const QString &type, double amount,
                                   const QString &description)
{
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO activity_logs (user_id, action, details) "
                  "VALUES (:userId, :action, :details)");
    query.bindValue(":userId", userId);
    query.bindValue(":action", type);
    query.bindValue(":details", description + " - Amount: " + QString::number(amount));

    return query.exec();
}

QList<QVariantMap> EliteDatabase::getUserTransactions(int userId, int limit)
{
    QList<QVariantMap> transactions;
    QSqlQuery query(m_db);
    query.prepare("SELECT log_id, action, details, timestamp "
                  "FROM activity_logs "
                  "WHERE user_id = :userId "
                  "ORDER BY timestamp DESC LIMIT :limit");
    query.bindValue(":userId", userId);
    query.bindValue(":limit", limit);

    if (query.exec()) {
        while (query.next()) {
            QVariantMap transaction;
            transaction["log_id"] = query.value(0).toInt();
            transaction["action"] = query.value(1).toString();
            transaction["details"] = query.value(2).toString();
            transaction["timestamp"] = query.value(3).toDateTime();
            transactions.append(transaction);
        }
    }

    return transactions;
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
    query.prepare("SELECT c.message_id, c.message, c.created_at, u.username "
                  "FROM chat_messages c "
                  "JOIN users u ON c.user_id = u.user_id "
                  "WHERE c.room_id = :roomId "
                  "ORDER BY c.created_at DESC LIMIT :limit");
    query.bindValue(":roomId", roomId);
    query.bindValue(":limit", limit);

    if (query.exec()) {
        while (query.next()) {
            QVariantMap msg;
            msg["message_id"] = query.value(0).toInt();
            msg["message"] = query.value(1).toString();
            msg["created_at"] = query.value(2).toDateTime();
            msg["username"] = query.value(3).toString();
            messages.append(msg);
        }
    }

    return messages;
}

bool EliteDatabase::updateBankInfo(int userId, const QString &bankName,
                                   const QString &accountNumber, const QString &accountHolder)
{
    QSqlQuery query(m_db);
    query.prepare("UPDATE users SET bank_name = :bankName, bank_account = :accountNumber "
                  "WHERE user_id = :userId");
    query.bindValue(":bankName", bankName);
    query.bindValue(":accountNumber", accountNumber);
    query.bindValue(":userId", userId);

    return query.exec();
}

QVariantMap EliteDatabase::getBankInfo(int userId)
{
    QVariantMap bankInfo;
    QSqlQuery query(m_db);
    query.prepare("SELECT bank_name, bank_account FROM users WHERE user_id = :userId");
    query.bindValue(":userId", userId);

    if (query.exec() && query.next()) {
        bankInfo["bank_name"] = query.value(0).toString();
        bankInfo["bank_account"] = query.value(1).toString();
    }

    return bankInfo;
}
