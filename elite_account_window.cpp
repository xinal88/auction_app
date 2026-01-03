#include "elite_account_window.h"
#include "elite_dialogs.h"
#include "elite_database.h"
#include <QScrollArea>
#include <QGraphicsDropShadowEffect>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QColor>
#include <QMessageBox>

EliteAccountWindow::EliteAccountWindow(QWidget *parent)
    : QWidget(parent), currentUserId(1)
{
    setupUI();
    setStyleSheet(getStyleSheet());
    loadUserData(currentUserId);
}

EliteAccountWindow::~EliteAccountWindow()
{
}

void EliteAccountWindow::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(40, 40, 40, 40);
    mainLayout->setSpacing(30);
    
    // Header
    QLabel *headerLabel = new QLabel("My Account");
    headerLabel->setObjectName("pageHeader");
    
    mainLayout->addWidget(headerLabel);
    
    // Scroll area
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setObjectName("scrollArea");
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    
    QWidget *scrollContent = new QWidget();
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollContent);
    scrollLayout->setSpacing(20);
    
    // Profile card
    QWidget *profileCard = createCard();
    QVBoxLayout *profileLayout = new QVBoxLayout(profileCard);
    profileLayout->setSpacing(15);
    
    QLabel *profileIcon = new QLabel("👤");
    profileIcon->setAlignment(Qt::AlignCenter);
    profileIcon->setStyleSheet("font-size: 48px;");
    
    QLabel *userIdLabel = new QLabel("1234567");
    userIdLabel->setObjectName("userId");
    userIdLabel->setAlignment(Qt::AlignCenter);
    
    QLabel *emailLabel = new QLabel("123@gmail.com");
    emailLabel->setObjectName("userEmail");
    emailLabel->setAlignment(Qt::AlignCenter);
    
    QLabel *statusBadge = new QLabel("Active");
    statusBadge->setObjectName("activeBadge");
    statusBadge->setAlignment(Qt::AlignCenter);
    statusBadge->setFixedWidth(100);
    
    QHBoxLayout *statusLayout = new QHBoxLayout();
    statusLayout->addStretch();
    statusLayout->addWidget(statusBadge);
    statusLayout->addStretch();
    
    profileLayout->addWidget(profileIcon);
    profileLayout->addWidget(userIdLabel);
    profileLayout->addWidget(emailLabel);
    profileLayout->addLayout(statusLayout);
    
    // Financial info cards
    QWidget *financialWidget = new QWidget();
    QHBoxLayout *financialLayout = new QHBoxLayout(financialWidget);
    financialLayout->setSpacing(20);
    
    // Balance card
    QWidget *balanceCard = createCard();
    QVBoxLayout *balanceLayout = new QVBoxLayout(balanceCard);
    balanceLayout->setSpacing(10);
    
    QLabel *balanceIcon = new QLabel("💰");
    balanceIcon->setStyleSheet("font-size: 32px;");
    
    QLabel *balanceTitle = new QLabel("Available Balance");
    balanceTitle->setObjectName("cardTitle");
    
    balanceLabel = new QLabel("10,000,000 đ");
    balanceLabel->setObjectName("balanceAmount");
    
    balanceLayout->addWidget(balanceIcon);
    balanceLayout->addWidget(balanceTitle);
    balanceLayout->addWidget(balanceLabel);
    
    // Bank account card
    QWidget *bankCard = createCard();
    QVBoxLayout *bankLayout = new QVBoxLayout(bankCard);
    bankLayout->setSpacing(10);
    
    QLabel *bankIcon = new QLabel("🏦");
    bankIcon->setStyleSheet("font-size: 32px;");
    
    QLabel *bankTitle = new QLabel("Bank Account");
    bankTitle->setObjectName("cardTitle");
    
    bankAccountLabel = new QLabel("Not set");
    bankAccountLabel->setObjectName("bankInfo");
    
    bankLayout->addWidget(bankIcon);
    bankLayout->addWidget(bankTitle);
    bankLayout->addWidget(bankAccountLabel);
    
    // Member since card
    QWidget *memberCard = createCard();
    QVBoxLayout *memberLayout = new QVBoxLayout(memberCard);
    memberLayout->setSpacing(10);
    
    QLabel *memberIcon = new QLabel("📅");
    memberIcon->setStyleSheet("font-size: 32px;");
    
    QLabel *memberTitle = new QLabel("Member Since");
    memberTitle->setObjectName("cardTitle");
    
    QLabel *memberDate = new QLabel("18/12/2025");
    memberDate->setObjectName("memberInfo");
    
    memberLayout->addWidget(memberIcon);
    memberLayout->addWidget(memberTitle);
    memberLayout->addWidget(memberDate);
    
    financialLayout->addWidget(balanceCard);
    financialLayout->addWidget(bankCard);
    financialLayout->addWidget(memberCard);
    
    // Action buttons
    QWidget *actionsWidget = new QWidget();
    QHBoxLayout *actionsLayout = new QHBoxLayout(actionsWidget);
    actionsLayout->setSpacing(15);
    
    depositBtn = new QPushButton("💵 Deposit Money");
    depositBtn->setObjectName("actionButton");
    depositBtn->setFixedHeight(60);
    depositBtn->setCursor(Qt::PointingHandCursor);
    
    withdrawBtn = new QPushButton("💸 Withdraw Money");
    withdrawBtn->setObjectName("withdrawButton");
    withdrawBtn->setFixedHeight(60);
    withdrawBtn->setCursor(Qt::PointingHandCursor);
    
    updateBankBtn = new QPushButton("🏦 Bank Information");
    updateBankBtn->setObjectName("secondaryButton");
    updateBankBtn->setFixedHeight(60);
    updateBankBtn->setCursor(Qt::PointingHandCursor);
    
    actionsLayout->addWidget(depositBtn);
    actionsLayout->addWidget(withdrawBtn);
    actionsLayout->addWidget(updateBankBtn);
    
    // Recent activity
    QLabel *activityHeader = new QLabel("Recent Activity");
    activityHeader->setObjectName("sectionHeader");
    
    QWidget *activityCard = createCard();
    QVBoxLayout *activityLayout = new QVBoxLayout(activityCard);
    activityLayout->setSpacing(15);
    
    activityLayout->addWidget(createActivityItem("Joined Luxury Watches Auction", "2 hours ago", "Participated"));
    activityLayout->addWidget(createDivider());
    activityLayout->addWidget(createActivityItem("Won: Vintage Camera", "Final bid: 2,500,000 VND", "Won"));
    activityLayout->addWidget(createDivider());
    activityLayout->addWidget(createActivityItem("Deposited funds", "+5,000,000 VND", "Completed"));
    
    // Add all to scroll layout
    scrollLayout->addWidget(profileCard);
    scrollLayout->addWidget(financialWidget);
    scrollLayout->addWidget(actionsWidget);
    scrollLayout->addWidget(activityHeader);
    scrollLayout->addWidget(activityCard);
    scrollLayout->addStretch();
    
    scrollArea->setWidget(scrollContent);
    mainLayout->addWidget(scrollArea);
    
    // Connect signals
    connect(depositBtn, &QPushButton::clicked, this, &EliteAccountWindow::onDepositClicked);
    connect(withdrawBtn, &QPushButton::clicked, this, &EliteAccountWindow::onWithdrawClicked);
    connect(updateBankBtn, &QPushButton::clicked, this, &EliteAccountWindow::onUpdateBankClicked);
}

QWidget* EliteAccountWindow::createCard()
{
    QWidget *card = new QWidget();
    card->setObjectName("accountCard");
    
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();
    shadow->setBlurRadius(20);
    shadow->setXOffset(0);
    shadow->setYOffset(4);
    shadow->setColor(QColor(0, 0, 0, 15));
    card->setGraphicsEffect(shadow);
    
    return card;
}

QWidget* EliteAccountWindow::createActivityItem(const QString &title, const QString &subtitle, const QString &status)
{
    QWidget *item = new QWidget();
    QHBoxLayout *itemLayout = new QHBoxLayout(item);
    itemLayout->setContentsMargins(0, 0, 0, 0);
    
    QVBoxLayout *textLayout = new QVBoxLayout();
    textLayout->setSpacing(5);
    
    QLabel *titleLabel = new QLabel(title);
    titleLabel->setObjectName("activityTitle");
    
    QLabel *subtitleLabel = new QLabel(subtitle);
    subtitleLabel->setObjectName("activitySubtitle");
    
    textLayout->addWidget(titleLabel);
    textLayout->addWidget(subtitleLabel);
    
    QLabel *statusLabel = new QLabel(status);
    if (status == "Won") {
        statusLabel->setObjectName("wonBadge");
    } else if (status == "Completed") {
        statusLabel->setObjectName("completedBadge");
    } else {
        statusLabel->setObjectName("participatedBadge");
    }
    statusLabel->setFixedWidth(100);
    statusLabel->setAlignment(Qt::AlignCenter);
    
    itemLayout->addLayout(textLayout);
    itemLayout->addStretch();
    itemLayout->addWidget(statusLabel);
    
    return item;
}

QWidget* EliteAccountWindow::createDivider()
{
    QWidget *divider = new QWidget();
    divider->setFixedHeight(1);
    divider->setStyleSheet("background-color: #E2E8F0;");
    return divider;
}

void EliteAccountWindow::onDepositClicked()
{
    DepositMoneyDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        double amount = dialog.getAmount();
        
        if (amount <= 0) {
            QMessageBox::warning(this, "Invalid Amount", "Please enter a valid amount!");
            return;
        }
        
        // Update balance in database
        EliteDatabase *db = EliteDatabase::instance();
        if (db->isConnected()) {
            double currentBalance = db->getUserBalance(1);
            double newBalance = currentBalance + amount;
            
            if (db->updateUserBalance(1, newBalance)) {
                // Add transaction record
                db->addTransaction(1, "deposit", amount, 
                    QString("Deposited %L1 đ").arg(amount, 0, 'f', 0));
                
                // Update UI
                balanceLabel->setText(QString("%L1 đ").arg(newBalance, 0, 'f', 0));
                
                // Show success message
                QMessageBox msgBox(this);
                msgBox.setWindowTitle("Deposit Successful");
                msgBox.setIcon(QMessageBox::Information);
                msgBox.setText("<h3 style='color: #10B981;'>✓ Deposit Successful!</h3>");
                msgBox.setInformativeText(
                    QString("<p style='color: #2D3748;'>You have successfully deposited <b>%L1 đ</b></p>"
                           "<p style='color: #718096; margin-top: 10px;'>New balance: <b>%L2 đ</b></p>")
                    .arg(amount, 0, 'f', 0)
                    .arg(newBalance, 0, 'f', 0));
                msgBox.setStandardButtons(QMessageBox::Ok);
                msgBox.button(QMessageBox::Ok)->setStyleSheet(
                    "background-color: #10B981; color: white; padding: 8px 24px; "
                    "border-radius: 6px; font-weight: 600; min-width: 80px;");
                msgBox.setStyleSheet("QMessageBox { background-color: white; } QLabel { color: #1A202C; }");
                msgBox.exec();
                
                // Emit signal to update main window balance
                emit balanceUpdated(newBalance);
            } else {
                QMessageBox::critical(this, "Deposit Failed", 
                    QString("Failed to deposit:\n%1").arg(db->lastError()));
            }
        } else {
            // Demo mode
            double currentBalance = balanceLabel->text().remove(" đ").remove(",").toDouble();
            double newBalance = currentBalance + amount;
            balanceLabel->setText(QString("%L1 đ").arg(newBalance, 0, 'f', 0));
            
            QMessageBox::information(this, "Deposit Successful (Demo)", 
                QString("Deposited %L1 đ successfully!\n\nNew balance: %L2 đ\n\n"
                       "Note: Running in demo mode.")
                .arg(amount, 0, 'f', 0)
                .arg(newBalance, 0, 'f', 0));
        }
    }
}

void EliteAccountWindow::onWithdrawClicked()
{
    WithdrawMoneyDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        double amount = dialog.getAmount();
        
        if (amount <= 0) {
            QMessageBox::warning(this, "Invalid Amount", "Please enter a valid amount!");
            return;
        }
        
        // Check balance and update in database
        EliteDatabase *db = EliteDatabase::instance();
        if (db->isConnected()) {
            double currentBalance = db->getUserBalance(1);
            
            if (amount > currentBalance) {
                QMessageBox::warning(this, "Insufficient Balance", 
                    QString("Your balance (%L1 đ) is not enough to withdraw %L2 đ")
                    .arg(currentBalance, 0, 'f', 0)
                    .arg(amount, 0, 'f', 0));
                return;
            }
            
            double newBalance = currentBalance - amount;
            
            if (db->updateUserBalance(1, newBalance)) {
                // Add transaction record
                db->addTransaction(1, "withdraw", amount, 
                    QString("Withdrew %L1 đ").arg(amount, 0, 'f', 0));
                
                // Update UI
                balanceLabel->setText(QString("%L1 đ").arg(newBalance, 0, 'f', 0));
                
                // Show success message
                QMessageBox msgBox(this);
                msgBox.setWindowTitle("Withdrawal Successful");
                msgBox.setIcon(QMessageBox::Information);
                msgBox.setText("<h3 style='color: #10B981;'>✓ Withdrawal Successful!</h3>");
                msgBox.setInformativeText(
                    QString("<p style='color: #2D3748;'>You have successfully withdrawn <b>%L1 đ</b></p>"
                           "<p style='color: #718096; margin-top: 10px;'>New balance: <b>%L2 đ</b></p>")
                    .arg(amount, 0, 'f', 0)
                    .arg(newBalance, 0, 'f', 0));
                msgBox.setStandardButtons(QMessageBox::Ok);
                msgBox.button(QMessageBox::Ok)->setStyleSheet(
                    "background-color: #F59E0B; color: white; padding: 8px 24px; "
                    "border-radius: 6px; font-weight: 600; min-width: 80px;");
                msgBox.setStyleSheet("QMessageBox { background-color: white; } QLabel { color: #1A202C; }");
                msgBox.exec();
                
                // Emit signal to update main window balance
                emit balanceUpdated(newBalance);
            } else {
                QMessageBox::critical(this, "Withdrawal Failed", 
                    QString("Failed to withdraw:\n%1").arg(db->lastError()));
            }
        } else {
            // Demo mode
            double currentBalance = balanceLabel->text().remove(" đ").remove(",").toDouble();
            
            if (amount > currentBalance) {
                QMessageBox::warning(this, "Insufficient Balance", 
                    QString("Your balance (%L1 đ) is not enough to withdraw %L2 đ")
                    .arg(currentBalance, 0, 'f', 0)
                    .arg(amount, 0, 'f', 0));
                return;
            }
            
            double newBalance = currentBalance - amount;
            balanceLabel->setText(QString("%L1 đ").arg(newBalance, 0, 'f', 0));
            
            QMessageBox::information(this, "Withdrawal Successful (Demo)", 
                QString("Withdrew %L1 đ successfully!\n\nNew balance: %L2 đ\n\n"
                       "Note: Running in demo mode.")
                .arg(amount, 0, 'f', 0)
                .arg(newBalance, 0, 'f', 0));
        }
    }
}

void EliteAccountWindow::onUpdateBankClicked()
{
    BankInfoDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QString bankName = dialog.getBankName();
        QString accountNumber = dialog.getAccountNumber();
        QString accountHolder = dialog.getAccountHolder();
        
        if (bankName.isEmpty() || accountNumber.isEmpty() || accountHolder.isEmpty()) {
            QMessageBox::warning(this, "Input Error", "Please fill in all bank information fields!");
            return;
        }
        
        // Save to database
        EliteDatabase *db = EliteDatabase::instance();
        if (db->isConnected()) {
            if (db->updateBankInfo(1, bankName, accountNumber, accountHolder)) {
                // Update UI
                bankAccountLabel->setText(QString("%1 - %2").arg(bankName, accountNumber));
                
                // Show success message
                QMessageBox msgBox(this);
                msgBox.setWindowTitle("Bank Information Updated");
                msgBox.setIcon(QMessageBox::Information);
                msgBox.setText("<h3 style='color: #10B981;'>✓ Bank Information Updated!</h3>");
                msgBox.setInformativeText(
                    QString("<p style='color: #2D3748;'>Your bank information has been updated successfully.</p>"
                           "<p style='margin-top: 10px;'><b>Bank:</b> %1</p>"
                           "<p><b>Account:</b> %2</p>"
                           "<p><b>Holder:</b> %3</p>")
                    .arg(bankName, accountNumber, accountHolder));
                msgBox.setStandardButtons(QMessageBox::Ok);
                msgBox.button(QMessageBox::Ok)->setStyleSheet(
                    "background-color: #4F46E5; color: white; padding: 8px 24px; "
                    "border-radius: 6px; font-weight: 600; min-width: 80px;");
                msgBox.setStyleSheet("QMessageBox { background-color: white; } QLabel { color: #1A202C; }");
                msgBox.exec();
            } else {
                QMessageBox::critical(this, "Update Failed", 
                    QString("Failed to update bank information:\n%1").arg(db->lastError()));
            }
        } else {
            // Demo mode
            bankAccountLabel->setText(QString("%1 - %2").arg(bankName, accountNumber));
            QMessageBox::information(this, "Bank Information Updated (Demo)", 
                QString("Bank information updated successfully!\n\n"
                       "Bank: %1\nAccount: %2\nHolder: %3\n\n"
                       "Note: Running in demo mode.")
                .arg(bankName, accountNumber, accountHolder));
        }
    }
}

void EliteAccountWindow::loadUserData(int userId)
{
    currentUserId = userId;
    
    EliteDatabase *db = EliteDatabase::instance();
    if (db->isConnected()) {
        // Load user info
        QVariantMap userInfo = db->getUserInfo(userId);
        if (!userInfo.isEmpty()) {
            userIdLabel->setText(userInfo["username"].toString());
            emailLabel->setText(userInfo["email"].toString());
            balanceLabel->setText(QString("%L1 đ").arg(userInfo["balance"].toDouble(), 0, 'f', 0));
            
            // Load bank info
            QString bankName = userInfo["bank_name"].toString();
            QString bankAccount = userInfo["bank_account"].toString();
            if (!bankName.isEmpty() && !bankAccount.isEmpty()) {
                bankAccountLabel->setText(QString("%1 - %2").arg(bankName, bankAccount));
            } else {
                bankAccountLabel->setText("Not set");
            }
        }
        
        // Load activity history
        loadActivityHistory();
    }
}

void EliteAccountWindow::refreshBalance()
{
    EliteDatabase *db = EliteDatabase::instance();
    if (db->isConnected()) {
        double balance = db->getUserBalance(currentUserId);
        balanceLabel->setText(QString("%L1 đ").arg(balance, 0, 'f', 0));
    }
}

void EliteAccountWindow::loadActivityHistory()
{
    // Clear existing activities (keep first 3 items which are static)
    while (activityLayout && activityLayout->count() > 0) {
        QLayoutItem *item = activityLayout->takeAt(0);
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }
    
    EliteDatabase *db = EliteDatabase::instance();
    if (db->isConnected()) {
        QList<QVariantMap> transactions = db->getUserTransactions(currentUserId, 10);
        
        for (const QVariantMap &trans : transactions) {
            QString action = trans["action"].toString();
            QString details = trans["details"].toString();
            QString timestamp = trans["timestamp"].toDateTime().toString("dd/MM/yyyy hh:mm");
            
            QString status = "Completed";
            if (action.contains("bid")) {
                status = "Participated";
            } else if (action.contains("won") || action.contains("purchase")) {
                status = "Won";
            }
            
            if (activityLayout) {
                activityLayout->addWidget(createActivityItem(details, timestamp, status));
                if (activityLayout->count() < transactions.size()) {
                    activityLayout->addWidget(createDivider());
                }
            }
        }
    }
}

QString EliteAccountWindow::getStyleSheet()
{
    return R"(
        QWidget {
            background-color: #F8F9FA;
            font-family: 'Segoe UI', 'Inter', sans-serif;
        }
        
        #pageHeader {
            font-size: 36px;
            font-weight: 700;
            color: #1A202C;
        }
        
        #sectionHeader {
            font-size: 20px;
            font-weight: 700;
            color: #1A202C;
        }
        
        #accountCard {
            background-color: white;
            border-radius: 16px;
            padding: 30px;
        }
        
        #userId {
            font-size: 28px;
            font-weight: 700;
            color: #1A202C;
        }
        
        #userEmail {
            font-size: 15px;
            color: #718096;
        }
        
        #activeBadge {
            background-color: #D1FAE5;
            color: #065F46;
            font-size: 13px;
            font-weight: 700;
            padding: 8px 16px;
            border-radius: 8px;
        }
        
        #cardTitle {
            font-size: 14px;
            color: #718096;
            font-weight: 500;
        }
        
        #balanceAmount {
            font-size: 24px;
            font-weight: 700;
            color: #4F46E5;
        }
        
        #bankInfo, #memberInfo {
            font-size: 15px;
            font-weight: 600;
            color: #2D3748;
        }
        
        #actionButton {
            background-color: #4F46E5;
            color: white;
            border: none;
            border-radius: 12px;
            font-size: 15px;
            font-weight: 600;
        }
        
        #actionButton:hover {
            background-color: #4338CA;
        }
        
        #withdrawButton {
            background-color: #F59E0B;
            color: white;
            border: none;
            border-radius: 12px;
            font-size: 15px;
            font-weight: 600;
        }
        
        #withdrawButton:hover {
            background-color: #D97706;
        }
        
        #secondaryButton {
            background-color: white;
            color: #2D3748;
            border: 2px solid #E2E8F0;
            border-radius: 12px;
            font-size: 15px;
            font-weight: 600;
        }
        
        #secondaryButton:hover {
            background-color: #F7FAFC;
            border-color: #CBD5E0;
        }
        
        #activityTitle {
            font-size: 15px;
            font-weight: 600;
            color: #1A202C;
        }
        
        #activitySubtitle {
            font-size: 13px;
            color: #718096;
        }
        
        #wonBadge {
            background-color: #D1FAE5;
            color: #065F46;
            font-size: 12px;
            font-weight: 700;
            padding: 6px 12px;
            border-radius: 6px;
        }
        
        #completedBadge {
            background-color: #DBEAFE;
            color: #1E40AF;
            font-size: 12px;
            font-weight: 700;
            padding: 6px 12px;
            border-radius: 6px;
        }
        
        #participatedBadge {
            background-color: #F3E8FF;
            color: #6B21A8;
            font-size: 12px;
            font-weight: 700;
            padding: 6px 12px;
            border-radius: 6px;
        }
        
        #scrollArea {
            border: none;
            background-color: transparent;
        }
    )";
}
