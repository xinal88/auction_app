#ifndef ELITE_NETWORK_CLIENT_H
#define ELITE_NETWORK_CLIENT_H

#include <QObject>
#include <QString>

class EliteNetworkClient : public QObject
{
    Q_OBJECT

public:
    explicit EliteNetworkClient(QObject *parent = nullptr);
    ~EliteNetworkClient();
    
    void connectToServer(const QString &host, int port);
    void sendMessage(const QString &message);

signals:
    void messageReceived(const QString &message);
    void connected();
    void disconnected();

private:
    // Network implementation
};

#endif // ELITE_NETWORK_CLIENT_H
