#ifndef CLIENT_LOGGER_H
#define CLIENT_LOGGER_H

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QMutex>

class ClientLogger {
public:
    static ClientLogger& instance();
    
    void init(const QString &filename);
    void log(const QString &message);
    void logLogin(const QString &username, bool success);
    void logLogout(const QString &username);
    void logRoomJoin(const QString &roomName, uint32_t roomId);
    void logRoomLeave(const QString &roomName);
    void logChat(const QString &roomName, const QString &message);
    void logBid(uint32_t itemId, int64_t amount, bool success);
    void logDeposit(int64_t amount, bool success);
    void logRedeem(int64_t amount, bool success);
    void cleanup();

private:
    ClientLogger() = default;
    ~ClientLogger();
    ClientLogger(const ClientLogger&) = delete;
    ClientLogger& operator=(const ClientLogger&) = delete;

    QFile logFile;
    QTextStream logStream;
    QMutex mutex;
    
    QString getTimestamp();
};

#endif // CLIENT_LOGGER_H
