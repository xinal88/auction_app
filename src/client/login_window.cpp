#include "login_window.h"
#include "client_logger.h"

LoginWindow::LoginWindow(NetworkClient *client, QWidget *parent)
    : QWidget(parent)
    , networkClient(client)
{
    setupUI();
    connectSignals();
    setWindowTitle("Auction App - Login");
    resize(500, 600);
}

LoginWindow::~LoginWindow() {
}

void LoginWindow::setupUI() {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    // Title
    QLabel *titleLabel = new QLabel("AUCTION APPLICATION", this);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(18);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);
    
    mainLayout->addSpacing(20);
    
    // Login Group
    QGroupBox *loginGroup = new QGroupBox("Login", this);
    QVBoxLayout *loginLayout = new QVBoxLayout(loginGroup);
    
    QLabel *loginUserLabel = new QLabel("Username:", this);
    loginUsernameEdit = new QLineEdit(this);
    loginUsernameEdit->setPlaceholderText("Enter username");
    
    QLabel *loginPassLabel = new QLabel("Password:", this);
    loginPasswordEdit = new QLineEdit(this);
    loginPasswordEdit->setEchoMode(QLineEdit::Password);
    loginPasswordEdit->setPlaceholderText("Enter password");
    
    loginButton = new QPushButton("Login", this);
    loginButton->setStyleSheet("QPushButton { background-color: #4CAF50; color: white; padding: 10px; font-size: 14px; }");
    
    loginLayout->addWidget(loginUserLabel);
    loginLayout->addWidget(loginUsernameEdit);
    loginLayout->addWidget(loginPassLabel);
    loginLayout->addWidget(loginPasswordEdit);
    loginLayout->addWidget(loginButton);
    
    mainLayout->addWidget(loginGroup);
    mainLayout->addSpacing(20);
    
    // Register Group
    QGroupBox *registerGroup = new QGroupBox("Register New Account", this);
    QVBoxLayout *regLayout = new QVBoxLayout(registerGroup);
    
    QLabel *regUserLabel = new QLabel("Username:", this);
    regUsernameEdit = new QLineEdit(this);
    regUsernameEdit->setPlaceholderText("Choose username");
    
    QLabel *regPassLabel = new QLabel("Password:", this);
    regPasswordEdit = new QLineEdit(this);
    regPasswordEdit->setEchoMode(QLineEdit::Password);
    regPasswordEdit->setPlaceholderText("Choose password");
    
    QLabel *regEmailLabel = new QLabel("Email:", this);
    regEmailEdit = new QLineEdit(this);
    regEmailEdit->setPlaceholderText("your.email@example.com");
    
    QLabel *regBankAccLabel = new QLabel("Bank Account:", this);
    regBankAccountEdit = new QLineEdit(this);
    regBankAccountEdit->setPlaceholderText("Bank account number");
    
    QLabel *regBankNameLabel = new QLabel("Bank Name:", this);
    regBankNameEdit = new QLineEdit(this);
    regBankNameEdit->setPlaceholderText("e.g., Vietcombank");
    
    registerButton = new QPushButton("Register", this);
    registerButton->setStyleSheet("QPushButton { background-color: #2196F3; color: white; padding: 10px; font-size: 14px; }");
    
    regLayout->addWidget(regUserLabel);
    regLayout->addWidget(regUsernameEdit);
    regLayout->addWidget(regPassLabel);
    regLayout->addWidget(regPasswordEdit);
    regLayout->addWidget(regEmailLabel);
    regLayout->addWidget(regEmailEdit);
    regLayout->addWidget(regBankAccLabel);
    regLayout->addWidget(regBankAccountEdit);
    regLayout->addWidget(regBankNameLabel);
    regLayout->addWidget(regBankNameEdit);
    regLayout->addWidget(registerButton);
    
    mainLayout->addWidget(registerGroup);
    
    // Status Label
    statusLabel = new QLabel("", this);
    statusLabel->setAlignment(Qt::AlignCenter);
    statusLabel->setStyleSheet("QLabel { color: red; font-weight: bold; }");
    mainLayout->addWidget(statusLabel);
    
    mainLayout->addStretch();
}

void LoginWindow::connectSignals() {
    connect(loginButton, &QPushButton::clicked, this, &LoginWindow::onLoginClicked);
    connect(registerButton, &QPushButton::clicked, this, &LoginWindow::onRegisterClicked);
    connect(networkClient, &NetworkClient::loginResponse, this, &LoginWindow::onLoginResponse);
    connect(networkClient, &NetworkClient::registerResponse, this, &LoginWindow::onRegisterResponse);
    
    // Enter key shortcuts
    connect(loginPasswordEdit, &QLineEdit::returnPressed, this, &LoginWindow::onLoginClicked);
}

void LoginWindow::onLoginClicked() {
    if (!validateLoginInput()) {
        return;
    }
    
    statusLabel->setText("Logging in...");
    statusLabel->setStyleSheet("QLabel { color: blue; font-weight: bold; }");
    
    QString username = loginUsernameEdit->text();
    QString password = loginPasswordEdit->text();
    
    if (!networkClient->sendLogin(username, password)) {
        statusLabel->setText("Failed to send login request");
        statusLabel->setStyleSheet("QLabel { color: red; font-weight: bold; }");
    }
}

void LoginWindow::onRegisterClicked() {
    if (!validateRegisterInput()) {
        return;
    }
    
    statusLabel->setText("Registering...");
    statusLabel->setStyleSheet("QLabel { color: blue; font-weight: bold; }");
    
    QString username = regUsernameEdit->text();
    QString password = regPasswordEdit->text();
    QString email = regEmailEdit->text();
    QString bankAccount = regBankAccountEdit->text();
    QString bankName = regBankNameEdit->text();
    
    if (!networkClient->sendRegister(username, password, email, bankAccount, bankName)) {
        statusLabel->setText("Failed to send register request");
        statusLabel->setStyleSheet("QLabel { color: red; font-weight: bold; }");
    }
}

void LoginWindow::onLoginResponse(int32_t status, const QString &message, uint32_t userId, const QString &token) {
    if (status == 1) {
        statusLabel->setText("Login successful!");
        statusLabel->setStyleSheet("QLabel { color: green; font-weight: bold; }");
        
        QString username = loginUsernameEdit->text();
        ClientLogger::instance().logLogin(username, true);
        
        emit loginSuccessful(userId, username, token);
        hide();
    } else {
        statusLabel->setText("Login failed: " + message);
        statusLabel->setStyleSheet("QLabel { color: red; font-weight: bold; }");
        ClientLogger::instance().logLogin(loginUsernameEdit->text(), false);
    }
}

void LoginWindow::onRegisterResponse(int32_t status, const QString &message) {
    if (status == 1) {
        statusLabel->setText("Registration successful! You can now login.");
        statusLabel->setStyleSheet("QLabel { color: green; font-weight: bold; }");
        
        // Clear register fields
        regUsernameEdit->clear();
        regPasswordEdit->clear();
        regEmailEdit->clear();
        regBankAccountEdit->clear();
        regBankNameEdit->clear();
    } else {
        statusLabel->setText("Registration failed: " + message);
        statusLabel->setStyleSheet("QLabel { color: red; font-weight: bold; }");
    }
}

bool LoginWindow::validateLoginInput() {
    if (loginUsernameEdit->text().trimmed().isEmpty()) {
        statusLabel->setText("Please enter username");
        statusLabel->setStyleSheet("QLabel { color: red; font-weight: bold; }");
        return false;
    }
    
    if (loginPasswordEdit->text().isEmpty()) {
        statusLabel->setText("Please enter password");
        statusLabel->setStyleSheet("QLabel { color: red; font-weight: bold; }");
        return false;
    }
    
    return true;
}

bool LoginWindow::validateRegisterInput() {
    if (regUsernameEdit->text().trimmed().isEmpty()) {
        statusLabel->setText("Please enter username");
        statusLabel->setStyleSheet("QLabel { color: red; font-weight: bold; }");
        return false;
    }
    
    if (regPasswordEdit->text().length() < 3) {
        statusLabel->setText("Password must be at least 3 characters");
        statusLabel->setStyleSheet("QLabel { color: red; font-weight: bold; }");
        return false;
    }
    
    if (regEmailEdit->text().trimmed().isEmpty() || !regEmailEdit->text().contains("@")) {
        statusLabel->setText("Please enter a valid email");
        statusLabel->setStyleSheet("QLabel { color: red; font-weight: bold; }");
        return false;
    }
    
    if (regBankAccountEdit->text().trimmed().isEmpty()) {
        statusLabel->setText("Please enter bank account");
        statusLabel->setStyleSheet("QLabel { color: red; font-weight: bold; }");
        return false;
    }
    
    if (regBankNameEdit->text().trimmed().isEmpty()) {
        statusLabel->setText("Please enter bank name");
        statusLabel->setStyleSheet("QLabel { color: red; font-weight: bold; }");
        return false;
    }
    
    return true;
}
