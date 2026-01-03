#include "elite_dialogs.h"
#include "elite_database.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QGraphicsDropShadowEffect>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QCheckBox>

// ============================================================================
// CREATE ROOM DIALOG
// ============================================================================

CreateRoomDialog::CreateRoomDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUI();
    setStyleSheet(getStyleSheet());
}

QString CreateRoomDialog::getRoomName() const
{
    return roomNameInput->text();
}

QString CreateRoomDialog::getDescription() const
{
    return descriptionInput->toPlainText();
}

bool CreateRoomDialog::isPublic() const
{
    return publicCheckbox->isChecked();
}

void CreateRoomDialog::setupUI()
{
    setWindowTitle("Create Auction Room");
    setFixedSize(500, 450);
    setModal(true);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(30, 30, 30, 30);
    mainLayout->setSpacing(20);
    
    // Header
    QLabel *headerLabel = new QLabel("Create New Auction Room");
    headerLabel->setObjectName("dialogHeader");
    
    // Room name
    QLabel *nameLabel = new QLabel("Room Name *");
    nameLabel->setObjectName("fieldLabel");
    
    roomNameInput = new QLineEdit();
    roomNameInput->setObjectName("dialogInput");
    roomNameInput->setPlaceholderText("Enter room name");
    roomNameInput->setFixedHeight(45);
    
    // Description
    QLabel *descLabel = new QLabel("Description");
    descLabel->setObjectName("fieldLabel");
    
    descriptionInput = new QTextEdit();
    descriptionInput->setObjectName("dialogTextEdit");
    descriptionInput->setPlaceholderText("Enter room description (optional)");
    descriptionInput->setFixedHeight(100);
    
    // Public checkbox
    publicCheckbox = new QCheckBox("Public Room (anyone can join)");
    publicCheckbox->setObjectName("dialogCheckbox");
    publicCheckbox->setChecked(true);
    
    // Buttons
    QWidget *buttonWidget = new QWidget();
    QHBoxLayout *buttonLayout = new QHBoxLayout(buttonWidget);
    buttonLayout->setContentsMargins(0, 0, 0, 0);
    buttonLayout->setSpacing(15);
    
    cancelButton = new QPushButton("Cancel");
    cancelButton->setObjectName("secondaryButton");
    cancelButton->setFixedHeight(45);
    cancelButton->setCursor(Qt::PointingHandCursor);
    
    createButton = new QPushButton("Create Room");
    createButton->setObjectName("primaryButton");
    createButton->setFixedHeight(45);
    createButton->setCursor(Qt::PointingHandCursor);
    
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(createButton);
    
    // Add to layout
    mainLayout->addWidget(headerLabel);
    mainLayout->addWidget(nameLabel);
    mainLayout->addWidget(roomNameInput);
    mainLayout->addWidget(descLabel);
    mainLayout->addWidget(descriptionInput);
    mainLayout->addWidget(publicCheckbox);
    mainLayout->addStretch();
    mainLayout->addWidget(buttonWidget);
    
    // Connect signals
    connect(createButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

QString CreateRoomDialog::getStyleSheet()
{
    return R"(
        QDialog {
            background-color: white;
        }
        #dialogHeader {
            font-size: 24px;
            font-weight: 700;
            color: #1A202C;
        }
        #fieldLabel {
            font-size: 14px;
            font-weight: 600;
            color: #2D3748;
        }
        #dialogInput {
            border: 2px solid #E2E8F0;
            border-radius: 8px;
            padding: 0 16px;
            font-size: 14px;
            background-color: white;
            color: #2D3748;
        }
        #dialogInput:focus {
            border: 2px solid #4F46E5;
        }
        #dialogTextEdit {
            border: 2px solid #E2E8F0;
            border-radius: 8px;
            padding: 12px;
            font-size: 14px;
            background-color: white;
            color: #2D3748;
        }
        #dialogTextEdit:focus {
            border: 2px solid #4F46E5;
        }
        #dialogCheckbox {
            font-size: 14px;
            color: #2D3748;
        }
        #primaryButton {
            background-color: #4F46E5;
            color: white;
            border: none;
            border-radius: 8px;
            font-size: 15px;
            font-weight: 600;
        }
        #primaryButton:hover {
            background-color: #4338CA;
        }
        #secondaryButton {
            background-color: white;
            color: #2D3748;
            border: 2px solid #E2E8F0;
            border-radius: 8px;
            font-size: 15px;
            font-weight: 600;
        }
        #secondaryButton:hover {
            background-color: #F7FAFC;
        }
    )";
}

// ============================================================================
// DEPOSIT MONEY DIALOG
// ============================================================================

DepositMoneyDialog::DepositMoneyDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUI();
    setStyleSheet(getStyleSheet());
}

double DepositMoneyDialog::getAmount() const
{
    return amountInput->text().toDouble();
}

void DepositMoneyDialog::onQuickAmountClicked()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (btn == amount1MBtn) {
        amountInput->setText("1000000");
    } else if (btn == amount5MBtn) {
        amountInput->setText("5000000");
    } else if (btn == amount10MBtn) {
        amountInput->setText("10000000");
    }
}

void DepositMoneyDialog::onDepositClicked()
{
    double amount = getAmount();
    if (amount <= 0) {
        QMessageBox::warning(this, "Invalid Amount", "Please enter a valid amount!");
        return;
    }
    accept();
}

void DepositMoneyDialog::setupUI()
{
    setWindowTitle("Deposit Money");
    setFixedSize(450, 400);
    setModal(true);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(30, 30, 30, 30);
    mainLayout->setSpacing(20);
    
    // Header
    QLabel *headerLabel = new QLabel("💰 Deposit Money");
    headerLabel->setObjectName("dialogHeader");
    
    // Current balance
    currentBalanceLabel = new QLabel("Current Balance: 10,000,000 đ");
    currentBalanceLabel->setObjectName("balanceLabel");
    
    // Amount input
    QLabel *amountLabel = new QLabel("Amount (VND) *");
    amountLabel->setObjectName("fieldLabel");
    
    amountInput = new QLineEdit();
    amountInput->setObjectName("dialogInput");
    amountInput->setPlaceholderText("Enter amount");
    amountInput->setFixedHeight(45);
    
    // Quick amount buttons
    QLabel *quickLabel = new QLabel("Quick Select:");
    quickLabel->setObjectName("fieldLabel");
    
    QWidget *quickWidget = new QWidget();
    QHBoxLayout *quickLayout = new QHBoxLayout(quickWidget);
    quickLayout->setContentsMargins(0, 0, 0, 0);
    quickLayout->setSpacing(10);
    
    amount1MBtn = new QPushButton("1,000,000 đ");
    amount1MBtn->setObjectName("quickButton");
    amount1MBtn->setFixedHeight(40);
    amount1MBtn->setCursor(Qt::PointingHandCursor);
    
    amount5MBtn = new QPushButton("5,000,000 đ");
    amount5MBtn->setObjectName("quickButton");
    amount5MBtn->setFixedHeight(40);
    amount5MBtn->setCursor(Qt::PointingHandCursor);
    
    amount10MBtn = new QPushButton("10,000,000 đ");
    amount10MBtn->setObjectName("quickButton");
    amount10MBtn->setFixedHeight(40);
    amount10MBtn->setCursor(Qt::PointingHandCursor);
    
    quickLayout->addWidget(amount1MBtn);
    quickLayout->addWidget(amount5MBtn);
    quickLayout->addWidget(amount10MBtn);
    
    // Buttons
    QWidget *buttonWidget = new QWidget();
    QHBoxLayout *buttonLayout = new QHBoxLayout(buttonWidget);
    buttonLayout->setContentsMargins(0, 0, 0, 0);
    buttonLayout->setSpacing(15);
    
    cancelButton = new QPushButton("Cancel");
    cancelButton->setObjectName("secondaryButton");
    cancelButton->setFixedHeight(45);
    cancelButton->setCursor(Qt::PointingHandCursor);
    
    depositButton = new QPushButton("Deposit");
    depositButton->setObjectName("primaryButton");
    depositButton->setFixedHeight(45);
    depositButton->setCursor(Qt::PointingHandCursor);
    
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(depositButton);
    
    // Add to layout
    mainLayout->addWidget(headerLabel);
    mainLayout->addWidget(currentBalanceLabel);
    mainLayout->addWidget(amountLabel);
    mainLayout->addWidget(amountInput);
    mainLayout->addWidget(quickLabel);
    mainLayout->addWidget(quickWidget);
    mainLayout->addStretch();
    mainLayout->addWidget(buttonWidget);
    
    // Connect signals
    connect(amount1MBtn, &QPushButton::clicked, this, &DepositMoneyDialog::onQuickAmountClicked);
    connect(amount5MBtn, &QPushButton::clicked, this, &DepositMoneyDialog::onQuickAmountClicked);
    connect(amount10MBtn, &QPushButton::clicked, this, &DepositMoneyDialog::onQuickAmountClicked);
    connect(depositButton, &QPushButton::clicked, this, &DepositMoneyDialog::onDepositClicked);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

QString DepositMoneyDialog::getStyleSheet()
{
    return R"(
        QDialog { background-color: white; }
        #dialogHeader { font-size: 24px; font-weight: 700; color: #1A202C; }
        #balanceLabel { font-size: 16px; font-weight: 600; color: #4F46E5; }
        #fieldLabel { font-size: 14px; font-weight: 600; color: #2D3748; }
        #dialogInput {
            border: 2px solid #E2E8F0; border-radius: 8px; padding: 0 16px;
            font-size: 14px; background-color: white; color: #2D3748;
        }
        #dialogInput:focus { border: 2px solid #4F46E5; }
        #quickButton {
            background-color: #F7FAFC; border: 2px solid #E2E8F0; border-radius: 8px;
            color: #2D3748; font-size: 13px; font-weight: 600;
        }
        #quickButton:hover { background-color: #EDF2F7; }
        #primaryButton {
            background-color: #4F46E5; color: white; border: none;
            border-radius: 8px; font-size: 15px; font-weight: 600;
        }
        #primaryButton:hover { background-color: #4338CA; }
        #secondaryButton {
            background-color: white; color: #2D3748; border: 2px solid #E2E8F0;
            border-radius: 8px; font-size: 15px; font-weight: 600;
        }
        #secondaryButton:hover { background-color: #F7FAFC; }
    )";
}

// ============================================================================
// WITHDRAW MONEY DIALOG
// ============================================================================

WithdrawMoneyDialog::WithdrawMoneyDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUI();
    setStyleSheet(getStyleSheet());
}

double WithdrawMoneyDialog::getAmount() const
{
    return amountInput->text().toDouble();
}

void WithdrawMoneyDialog::onWithdrawClicked()
{
    double amount = getAmount();
    if (amount <= 0) {
        QMessageBox::warning(this, "Invalid Amount", "Please enter a valid amount!");
        return;
    }
    accept();
}

void WithdrawMoneyDialog::setupUI()
{
    setWindowTitle("Withdraw Money");
    setFixedSize(450, 400);
    setModal(true);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(30, 30, 30, 30);
    mainLayout->setSpacing(20);
    
    // Header
    QLabel *headerLabel = new QLabel("💸 Withdraw Money");
    headerLabel->setObjectName("dialogHeader");
    
    // Current balance
    currentBalanceLabel = new QLabel("Available Balance: 10,000,000 đ");
    currentBalanceLabel->setObjectName("balanceLabel");
    
    // Bank info
    bankInfoLabel = new QLabel("Bank: Not set - Please update bank information first");
    bankInfoLabel->setObjectName("warningLabel");
    bankInfoLabel->setWordWrap(true);
    
    // Amount input
    QLabel *amountLabel = new QLabel("Amount (VND) *");
    amountLabel->setObjectName("fieldLabel");
    
    amountInput = new QLineEdit();
    amountInput->setObjectName("dialogInput");
    amountInput->setPlaceholderText("Enter amount to withdraw");
    amountInput->setFixedHeight(45);
    
    // Buttons
    QWidget *buttonWidget = new QWidget();
    QHBoxLayout *buttonLayout = new QHBoxLayout(buttonWidget);
    buttonLayout->setContentsMargins(0, 0, 0, 0);
    buttonLayout->setSpacing(15);
    
    cancelButton = new QPushButton("Cancel");
    cancelButton->setObjectName("secondaryButton");
    cancelButton->setFixedHeight(45);
    cancelButton->setCursor(Qt::PointingHandCursor);
    
    withdrawButton = new QPushButton("Withdraw");
    withdrawButton->setObjectName("withdrawButton");
    withdrawButton->setFixedHeight(45);
    withdrawButton->setCursor(Qt::PointingHandCursor);
    
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(withdrawButton);
    
    // Add to layout
    mainLayout->addWidget(headerLabel);
    mainLayout->addWidget(currentBalanceLabel);
    mainLayout->addWidget(bankInfoLabel);
    mainLayout->addWidget(amountLabel);
    mainLayout->addWidget(amountInput);
    mainLayout->addStretch();
    mainLayout->addWidget(buttonWidget);
    
    // Connect signals
    connect(withdrawButton, &QPushButton::clicked, this, &WithdrawMoneyDialog::onWithdrawClicked);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

QString WithdrawMoneyDialog::getStyleSheet()
{
    return R"(
        QDialog { background-color: white; }
        #dialogHeader { font-size: 24px; font-weight: 700; color: #1A202C; }
        #balanceLabel { font-size: 16px; font-weight: 600; color: #4F46E5; }
        #warningLabel { font-size: 13px; color: #D97706; background-color: #FEF3C7; padding: 10px; border-radius: 6px; }
        #fieldLabel { font-size: 14px; font-weight: 600; color: #2D3748; }
        #dialogInput {
            border: 2px solid #E2E8F0; border-radius: 8px; padding: 0 16px;
            font-size: 14px; background-color: white; color: #2D3748;
        }
        #dialogInput:focus { border: 2px solid #4F46E5; }
        #withdrawButton {
            background-color: #F59E0B; color: white; border: none;
            border-radius: 8px; font-size: 15px; font-weight: 600;
        }
        #withdrawButton:hover { background-color: #D97706; }
        #secondaryButton {
            background-color: white; color: #2D3748; border: 2px solid #E2E8F0;
            border-radius: 8px; font-size: 15px; font-weight: 600;
        }
        #secondaryButton:hover { background-color: #F7FAFC; }
    )";
}

// ============================================================================
// BANK INFO DIALOG
// ============================================================================

BankInfoDialog::BankInfoDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUI();
    setStyleSheet(getStyleSheet());
}

QString BankInfoDialog::getBankName() const
{
    return bankNameInput->text();
}

QString BankInfoDialog::getAccountNumber() const
{
    return accountNumberInput->text();
}

QString BankInfoDialog::getAccountHolder() const
{
    return accountHolderInput->text();
}

void BankInfoDialog::setupUI()
{
    setWindowTitle("Bank Information");
    setFixedSize(450, 450);
    setModal(true);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(30, 30, 30, 30);
    mainLayout->setSpacing(20);
    
    // Header
    QLabel *headerLabel = new QLabel("🏦 Bank Information");
    headerLabel->setObjectName("dialogHeader");
    
    QLabel *infoLabel = new QLabel("Update your banking details for withdrawals");
    infoLabel->setObjectName("infoLabel");
    
    // Bank name
    QLabel *bankLabel = new QLabel("Bank Name *");
    bankLabel->setObjectName("fieldLabel");
    
    bankNameInput = new QLineEdit();
    bankNameInput->setObjectName("dialogInput");
    bankNameInput->setPlaceholderText("e.g., Vietcombank, Techcombank");
    bankNameInput->setFixedHeight(45);
    
    // Account number
    QLabel *accountLabel = new QLabel("Account Number *");
    accountLabel->setObjectName("fieldLabel");
    
    accountNumberInput = new QLineEdit();
    accountNumberInput->setObjectName("dialogInput");
    accountNumberInput->setPlaceholderText("Enter account number");
    accountNumberInput->setFixedHeight(45);
    
    // Account holder
    QLabel *holderLabel = new QLabel("Account Holder Name *");
    holderLabel->setObjectName("fieldLabel");
    
    accountHolderInput = new QLineEdit();
    accountHolderInput->setObjectName("dialogInput");
    accountHolderInput->setPlaceholderText("Enter account holder name");
    accountHolderInput->setFixedHeight(45);
    
    // Buttons
    QWidget *buttonWidget = new QWidget();
    QHBoxLayout *buttonLayout = new QHBoxLayout(buttonWidget);
    buttonLayout->setContentsMargins(0, 0, 0, 0);
    buttonLayout->setSpacing(15);
    
    cancelButton = new QPushButton("Cancel");
    cancelButton->setObjectName("secondaryButton");
    cancelButton->setFixedHeight(45);
    cancelButton->setCursor(Qt::PointingHandCursor);
    
    saveButton = new QPushButton("Save");
    saveButton->setObjectName("primaryButton");
    saveButton->setFixedHeight(45);
    saveButton->setCursor(Qt::PointingHandCursor);
    
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(saveButton);
    
    // Add to layout
    mainLayout->addWidget(headerLabel);
    mainLayout->addWidget(infoLabel);
    mainLayout->addWidget(bankLabel);
    mainLayout->addWidget(bankNameInput);
    mainLayout->addWidget(accountLabel);
    mainLayout->addWidget(accountNumberInput);
    mainLayout->addWidget(holderLabel);
    mainLayout->addWidget(accountHolderInput);
    mainLayout->addStretch();
    mainLayout->addWidget(buttonWidget);
    
    // Connect signals
    connect(saveButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

QString BankInfoDialog::getStyleSheet()
{
    return R"(
        QDialog { background-color: white; }
        #dialogHeader { font-size: 24px; font-weight: 700; color: #1A202C; }
        #infoLabel { font-size: 14px; color: #718096; }
        #fieldLabel { font-size: 14px; font-weight: 600; color: #2D3748; }
        #dialogInput {
            border: 2px solid #E2E8F0; border-radius: 8px; padding: 0 16px;
            font-size: 14px; background-color: white; color: #2D3748;
        }
        #dialogInput:focus { border: 2px solid #4F46E5; }
        #primaryButton {
            background-color: #4F46E5; color: white; border: none;
            border-radius: 8px; font-size: 15px; font-weight: 600;
        }
        #primaryButton:hover { background-color: #4338CA; }
        #secondaryButton {
            background-color: white; color: #2D3748; border: 2px solid #E2E8F0;
            border-radius: 8px; font-size: 15px; font-weight: 600;
        }
        #secondaryButton:hover { background-color: #F7FAFC; }
    )";
}


// ============================================================================
// Sign Up Dialog
// ============================================================================

SignUpDialog::SignUpDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUI();
    setStyleSheet(getStyleSheet());
}

QString SignUpDialog::getUsername() const
{
    return usernameInput->text();
}

QString SignUpDialog::getEmail() const
{
    return emailInput->text();
}

QString SignUpDialog::getPassword() const
{
    return passwordInput->text();
}

void SignUpDialog::setupUI()
{
    setWindowTitle("Create Account");
    setFixedSize(500, 600);
    setModal(true);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(40, 40, 40, 40);
    mainLayout->setSpacing(25);
    
    // Header
    QLabel *headerLabel = new QLabel("Create Your Account");
    headerLabel->setObjectName("dialogHeader");
    headerLabel->setAlignment(Qt::AlignCenter);
    
    QLabel *subheaderLabel = new QLabel("Join AuctionHub and start bidding!");
    subheaderLabel->setObjectName("dialogSubheader");
    subheaderLabel->setAlignment(Qt::AlignCenter);
    
    mainLayout->addWidget(headerLabel);
    mainLayout->addWidget(subheaderLabel);
    mainLayout->addSpacing(10);
    
    // Username
    QLabel *usernameLabel = new QLabel("Username");
    usernameLabel->setObjectName("inputLabel");
    
    usernameInput = new QLineEdit();
    usernameInput->setObjectName("dialogInput");
    usernameInput->setPlaceholderText("Choose a username");
    usernameInput->setFixedHeight(48);
    
    // Email
    QLabel *emailLabel = new QLabel("Email");
    emailLabel->setObjectName("inputLabel");
    
    emailInput = new QLineEdit();
    emailInput->setObjectName("dialogInput");
    emailInput->setPlaceholderText("your.email@example.com");
    emailInput->setFixedHeight(48);
    
    // Password
    QLabel *passwordLabel = new QLabel("Password");
    passwordLabel->setObjectName("inputLabel");
    
    passwordInput = new QLineEdit();
    passwordInput->setObjectName("dialogInput");
    passwordInput->setPlaceholderText("Create a strong password");
    passwordInput->setEchoMode(QLineEdit::Password);
    passwordInput->setFixedHeight(48);
    
    // Confirm Password
    QLabel *confirmLabel = new QLabel("Confirm Password");
    confirmLabel->setObjectName("inputLabel");
    
    confirmPasswordInput = new QLineEdit();
    confirmPasswordInput->setObjectName("dialogInput");
    confirmPasswordInput->setPlaceholderText("Re-enter your password");
    confirmPasswordInput->setEchoMode(QLineEdit::Password);
    confirmPasswordInput->setFixedHeight(48);
    
    mainLayout->addWidget(usernameLabel);
    mainLayout->addWidget(usernameInput);
    mainLayout->addWidget(emailLabel);
    mainLayout->addWidget(emailInput);
    mainLayout->addWidget(passwordLabel);
    mainLayout->addWidget(passwordInput);
    mainLayout->addWidget(confirmLabel);
    mainLayout->addWidget(confirmPasswordInput);
    
    mainLayout->addSpacing(10);
    
    // Buttons
    QWidget *buttonWidget = new QWidget();
    QHBoxLayout *buttonLayout = new QHBoxLayout(buttonWidget);
    buttonLayout->setContentsMargins(0, 0, 0, 0);
    buttonLayout->setSpacing(15);
    
    cancelButton = new QPushButton("Cancel");
    cancelButton->setObjectName("cancelButton");
    cancelButton->setFixedHeight(48);
    cancelButton->setCursor(Qt::PointingHandCursor);
    
    signUpButton = new QPushButton("Create Account");
    signUpButton->setObjectName("primaryButton");
    signUpButton->setFixedHeight(48);
    signUpButton->setCursor(Qt::PointingHandCursor);
    
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(signUpButton);
    
    mainLayout->addWidget(buttonWidget);
    
    // Connect signals
    connect(signUpButton, &QPushButton::clicked, this, &SignUpDialog::onSignUpClicked);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

void SignUpDialog::onSignUpClicked()
{
    QString username = usernameInput->text().trimmed();
    QString email = emailInput->text().trimmed();
    QString password = passwordInput->text();
    QString confirmPassword = confirmPasswordInput->text();
    
    // Validation
    if (username.isEmpty() || email.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill in all fields.");
        return;
    }
    
    if (username.length() < 3) {
        QMessageBox::warning(this, "Invalid Username", "Username must be at least 3 characters long.");
        return;
    }
    
    if (!email.contains("@") || !email.contains(".")) {
        QMessageBox::warning(this, "Invalid Email", "Please enter a valid email address.");
        return;
    }
    
    if (password.length() < 6) {
        QMessageBox::warning(this, "Weak Password", "Password must be at least 6 characters long.");
        return;
    }
    
    if (password != confirmPassword) {
        QMessageBox::warning(this, "Password Mismatch", "Passwords do not match. Please try again.");
        return;
    }
    
    // Try to register in database
    EliteDatabase *db = EliteDatabase::instance();
    if (db->isConnected()) {
        if (db->registerUser(username, email, password)) {
            QMessageBox msgBox(this);
            msgBox.setWindowTitle("Success");
            msgBox.setIcon(QMessageBox::Information);
            msgBox.setText("<h3 style='color: #10B981;'>✓ Account Created!</h3>");
            msgBox.setInformativeText(
                QString("<p style='color: #2D3748;'>Your account has been created successfully!</p>"
                       "<p><b>Username:</b> %1</p>"
                       "<p><b>Email:</b> %2</p>"
                       "<p style='color: #718096; margin-top: 10px;'>You can now sign in with your credentials.</p>")
                .arg(username).arg(email));
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.button(QMessageBox::Ok)->setStyleSheet(
                "background-color: #10B981; color: white; padding: 8px 24px; "
                "border-radius: 6px; font-weight: 600; min-width: 80px;");
            msgBox.setStyleSheet("QMessageBox { background-color: white; } QLabel { color: #1A202C; }");
            msgBox.exec();
            accept();
        } else {
            QMessageBox::critical(this, "Registration Failed", 
                QString("Failed to create account:\n%1\n\nThe email might already be registered.")
                .arg(db->lastError()));
        }
    } else {
        // Demo mode - just accept without showing popup
        // User will see the success message in login window
        accept();
    }
}

QString SignUpDialog::getStyleSheet()
{
    return R"(
        QDialog {
            background-color: white;
        }
        
        #dialogHeader {
            font-size: 28px;
            font-weight: 700;
            color: #1A202C;
        }
        
        #dialogSubheader {
            font-size: 15px;
            color: #718096;
        }
        
        #inputLabel {
            font-size: 14px;
            font-weight: 600;
            color: #2D3748;
        }
        
        #dialogInput {
            border: 2px solid #E2E8F0;
            border-radius: 10px;
            padding: 0 16px;
            font-size: 15px;
            background-color: white;
            color: #2D3748;
        }
        
        #dialogInput:focus {
            border: 2px solid #4F46E5;
        }
        
        #primaryButton {
            background-color: #4F46E5;
            color: white;
            border: none;
            border-radius: 10px;
            font-size: 16px;
            font-weight: 700;
        }
        
        #primaryButton:hover {
            background-color: #4338CA;
        }
        
        #cancelButton {
            background-color: #F7FAFC;
            color: #2D3748;
            border: 2px solid #E2E8F0;
            border-radius: 10px;
            font-size: 16px;
            font-weight: 600;
        }
        
        #cancelButton:hover {
            background-color: #EDF2F7;
        }
    )";
}
