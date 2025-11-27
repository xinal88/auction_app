#include <QApplication>
#include <QMessageBox>
#include "network_client.h"
#include "login_window.h"
#include "main_window.h"
#include "client_logger.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    // Initialize client logger
    ClientLogger::instance().init("client.log");
    
    // Create network client
    NetworkClient *networkClient = new NetworkClient();
    
    // Try to connect to server
    QString serverHost = "127.0.0.1";
    quint16 serverPort = 5500;
    
    qDebug() << "Connecting to server at" << serverHost << ":" << serverPort;
    
    if (!networkClient->connectToServer(serverHost, serverPort)) {
        QMessageBox::critical(nullptr, "Connection Error", 
            "Failed to connect to server at " + serverHost + ":" + QString::number(serverPort) + 
            "\n\nPlease make sure the server is running.");
        return 1;
    }
    
    qDebug() << "Connected to server successfully";
    
    // Create and show login window
    LoginWindow *loginWindow = new LoginWindow(networkClient);
    
    // When login successful, show main window
    MainWindow *mainWindow = nullptr;
    QObject::connect(loginWindow, &LoginWindow::loginSuccessful, 
        [&](uint32_t userId, const QString &username, const QString &token) {
            mainWindow = new MainWindow(networkClient, userId, username);
            mainWindow->show();
        });
    
    loginWindow->show();
    
    int result = app.exec();
    
    // Cleanup
    ClientLogger::instance().cleanup();
    delete networkClient;
    
    return result;
}
