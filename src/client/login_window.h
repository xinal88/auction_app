#ifndef LOGIN_WINDOW_H
#define LOGIN_WINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QMessageBox>
#include "network_client.h"

class LoginWindow : public QWidget {
    Q_OBJECT

public:
    explicit LoginWindow(NetworkClient *client, QWidget *parent = nullptr);
    ~LoginWindow();

signals:
    void loginSuccessful(uint32_t userId, const QString &username, const QString &token);

private slots:
    void onLoginClicked();
    void onRegisterClicked();
    void onLoginResponse(int32_t status, const QString &message, uint32_t userId, const QString &token);
    void onRegisterResponse(int32_t status, const QString &message);

private:
    NetworkClient *networkClient;
    
    // Login widgets
    QLineEdit *loginUsernameEdit;
    QLineEdit *loginPasswordEdit;
    QPushButton *loginButton;
    
    // Register widgets
    QLineEdit *regUsernameEdit;
    QLineEdit *regPasswordEdit;
    QLineEdit *regEmailEdit;
    QLineEdit *regBankAccountEdit;
    QLineEdit *regBankNameEdit;
    QPushButton *registerButton;
    
    QLabel *statusLabel;
    
    void setupUI();
    void connectSignals();
    bool validateLoginInput();
    bool validateRegisterInput();
};

#endif // LOGIN_WINDOW_H
