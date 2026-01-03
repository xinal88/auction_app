#ifndef ELITE_DATABASE_H
#define ELITE_DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <QVariantMap>
#include <QList>

class EliteDatabase : public QObject
{
    Q_OBJECT

public:
    static EliteDatabase* instance();
    
    // Connection
    bool connectToDatabase(const QString &host = "localhost", 
                          const QString &dbName = "auction_db",
                          const QString &user = "root", 
                          const QString &password = "");
    void disconnect();
    bool isConnected();
    QString lastError();
    
    // User operations
    bool loginUser(const QString &email, const QString &password, int &userId, QString &username);
    bool registerUser(const QString &username, const QString &email, const QString &password);
    double getUserBalance(int userId);
    bool updateUserBalance(int userId, double newBalance);
    QVariantMap getUserInfo(int userId);
    
    // Room operations
    QList<QVariantMap> getAuctionRooms(const QString &filter = "all");
    int createAuctionRoom(const QString &name, const QString &description, 
                          int hostUserId, bool isPublic);
    QVariantMap getRoomDetails(int roomId);
    
    // Item operations
    QList<QVariantMap> getRoomItems(int roomId);
    QVariantMap getCurrentItem(int roomId);
    bool updateItemPrice(int itemId, double newPrice, int bidderId);
    
    // Transaction operations
    bool addTransaction(int userId, const QString &type, double amount, 
                       const QString &description);
    QList<QVariantMap> getUserTransactions(int userId, int limit = 10);
    
    // Chat operations
    bool sendChatMessage(int roomId, int userId, const QString &message);
    QList<QVariantMap> getChatMessages(int roomId, int limit = 50);
    
    // Bank operations
    bool updateBankInfo(int userId, const QString &bankName, 
                       const QString &accountNumber, const QString &accountHolder);
    QVariantMap getBankInfo(int userId);

signals:
    void connectionStatusChanged(bool connected);
    void errorOccurred(const QString &error);

private:
    explicit EliteDatabase(QObject *parent = nullptr);
    static EliteDatabase *m_instance;
    QSqlDatabase m_db;
    QString m_lastError;
    
    QString hashPassword(const QString &password);
};

#endif // ELITE_DATABASE_H
