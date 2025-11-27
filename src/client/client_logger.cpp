#include "client_logger.h"

ClientLogger& ClientLogger::instance() {
    static ClientLogger instance;
    return instance;
}

ClientLogger::~ClientLogger() {
    cleanup();
}

void ClientLogger::init(const QString &filename) {
    QMutexLocker locker(&mutex);
    
    if (logFile.isOpen()) {
        logFile.close();
    }
    
    logFile.setFileName(filename);
    if (logFile.open(QIODevice::Append | QIODevice::Text)) {
        logStream.setDevice(&logFile);
        log("=== Client Logger Initialized ===");
    }
}

void ClientLogger::log(const QString &message) {
    QMutexLocker locker(&mutex);
    
    if (logFile.isOpen()) {
        logStream << getTimestamp() << " " << message << "\n";
        logStream.flush();
    }
}

void ClientLogger::logLogin(const QString &username, bool success) {
    QString msg = QString("LOGIN: User '%1' - %2")
                    .arg(username)
                    .arg(success ? "SUCCESS" : "FAILED");
    log(msg);
}

void ClientLogger::logLogout(const QString &username) {
    QString msg = QString("LOGOUT: User '%1'").arg(username);
    log(msg);
}

void ClientLogger::logRoomJoin(const QString &roomName, uint32_t roomId) {
    QString msg = QString("ROOM_JOIN: Joined room '%1' (ID: %2)")
                    .arg(roomName)
                    .arg(roomId);
    log(msg);
}

void ClientLogger::logRoomLeave(const QString &roomName) {
    QString msg = QString("ROOM_LEAVE: Left room '%1'").arg(roomName);
    log(msg);
}

void ClientLogger::logChat(const QString &roomName, const QString &message) {
    QString msg = QString("CHAT: [%1] %2")
                    .arg(roomName)
                    .arg(message);
    log(msg);
}

void ClientLogger::logBid(uint32_t itemId, int64_t amount, bool success) {
    QString msg = QString("BID: Item %1, Amount %2 VND - %3")
                    .arg(itemId)
                    .arg(amount)
                    .arg(success ? "SUCCESS" : "FAILED");
    log(msg);
}

void ClientLogger::logDeposit(int64_t amount, bool success) {
    QString msg = QString("DEPOSIT: %1 VND - %2")
                    .arg(amount)
                    .arg(success ? "SUCCESS" : "FAILED");
    log(msg);
}

void ClientLogger::logRedeem(int64_t amount, bool success) {
    QString msg = QString("REDEEM: %1 VND - %2")
                    .arg(amount)
                    .arg(success ? "SUCCESS" : "FAILED");
    log(msg);
}

void ClientLogger::cleanup() {
    QMutexLocker locker(&mutex);
    
    if (logFile.isOpen()) {
        log("=== Client Logger Shutdown ===");
        logFile.close();
    }
}

QString ClientLogger::getTimestamp() {
    return QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
}
