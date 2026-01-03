#include "elite_network_client.h"

EliteNetworkClient::EliteNetworkClient(QObject *parent)
    : QObject(parent)
{
    // Network client implementation
}

EliteNetworkClient::~EliteNetworkClient()
{
}

void EliteNetworkClient::connectToServer(const QString &host, int port)
{
    Q_UNUSED(host);
    Q_UNUSED(port);
    // Connect to server - TODO: Implement
}

void EliteNetworkClient::sendMessage(const QString &message)
{
    Q_UNUSED(message);
    // Send message to server - TODO: Implement
}
