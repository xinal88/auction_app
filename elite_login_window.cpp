#include "elite_login_window.h"
#include "elite_main_window.h"
#include "elite_dialogs.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QGraphicsDropShadowEffect>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QColor>
#include <QMessageBox>

EliteLoginWindow::EliteLoginWindow(QWidget *parent)
    : QWidget(parent), mainWindow(nullptr)
{
    setupUI();
    setStyleSheet(getStyleSheet());
}

EliteLoginWindow::~EliteLoginWindow()
{
}

void EliteLoginWindow::setupUI()
{
    setWindowTitle("AuctionHub - Welcome");
    setFixedSize(1000, 700);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    
    // Center container
    QWidget *centerWidget = new QWidget();
    centerWidget->setObjectName("centerWidget");
    QVBoxLayout *centerLayout = new QVBoxLayout(centerWidget);
    centerLayout->setAlignment(Qt::AlignCenter);
    centerLayout->setSpacing(30);
    
    // Logo and title
    QLabel *logoLabel = new QLabel("🔨");
    logoLabel->setAlignment(Qt::AlignCenter);
    logoLabel->setStyleSheet("font-size: 48px;");
    
    titleLabel = new QLabel("Welcome Back");
    titleLabel->setObjectName("titleLabel");
    titleLabel->setAlignment(Qt::AlignCenter);
    
    subtitleLabel = new QLabel("Sign in to continue to AuctionHub");
    subtitleLabel->setObjectName("subtitleLabel");
    subtitleLabel->setAlignment(Qt::AlignCenter);
    
    // Login form container
    QWidget *formWidget = new QWidget();
    formWidget->setObjectName("formWidget");
    formWidget->setFixedWidth(400);
    QVBoxLayout *formLayout = new QVBoxLayout(formWidget);
    formLayout->setSpacing(20);
    formLayout->setContentsMargins(40, 40, 40, 40);
    
    // Email input
    QLabel *emailLabel = new QLabel("Email");
    emailLabel->setObjectName("inputLabel");
    emailInput = new QLineEdit();
    emailInput->setObjectName("modernInput");
    emailInput->setPlaceholderText("Enter your email");
    emailInput->setFixedHeight(48);
    
    // Password input
    QLabel *passwordLabel = new QLabel("Password");
    passwordLabel->setObjectName("inputLabel");
    passwordInput = new QLineEdit();
    passwordInput->setObjectName("modernInput");
    passwordInput->setPlaceholderText("Enter your password");
    passwordInput->setEchoMode(QLineEdit::Password);
    passwordInput->setFixedHeight(48);
    
    // Login button
    loginButton = new QPushButton("Sign In");
    loginButton->setObjectName("primaryButton");
    loginButton->setFixedHeight(48);
    loginButton->setCursor(Qt::PointingHandCursor);
    
    // Sign up link
    QWidget *signUpWidget = new QWidget();
    QHBoxLayout *signUpLayout = new QHBoxLayout(signUpWidget);
    signUpLayout->setContentsMargins(0, 0, 0, 0);
    signUpLayout->setAlignment(Qt::AlignCenter);
    
    QLabel *noAccountLabel = new QLabel("Don't have an account?");
    noAccountLabel->setObjectName("subtitleLabel");
    
    signUpButton = new QPushButton("Sign up");
    signUpButton->setObjectName("linkButton");
    signUpButton->setCursor(Qt::PointingHandCursor);
    
    signUpLayout->addWidget(noAccountLabel);
    signUpLayout->addWidget(signUpButton);
    
    // Add to form
    formLayout->addWidget(emailLabel);
    formLayout->addWidget(emailInput);
    formLayout->addWidget(passwordLabel);
    formLayout->addWidget(passwordInput);
    formLayout->addSpacing(10);
    formLayout->addWidget(loginButton);
    formLayout->addWidget(signUpWidget);
    
    // Add shadow effect to form
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();
    shadow->setBlurRadius(30);
    shadow->setXOffset(0);
    shadow->setYOffset(10);
    shadow->setColor(QColor(0, 0, 0, 30));
    formWidget->setGraphicsEffect(shadow);
    
    // Add to center layout
    centerLayout->addWidget(logoLabel);
    centerLayout->addWidget(titleLabel);
    centerLayout->addWidget(subtitleLabel);
    centerLayout->addSpacing(20);
    centerLayout->addWidget(formWidget, 0, Qt::AlignCenter);
    
    mainLayout->addWidget(centerWidget);
    
    // Connect signals
    connect(loginButton, &QPushButton::clicked, this, &EliteLoginWindow::onLoginClicked);
    connect(signUpButton, &QPushButton::clicked, this, &EliteLoginWindow::onSignUpClicked);
}

QString EliteLoginWindow::getStyleSheet()
{
    return R"(
        QWidget {
            background-color: #F8F9FA;
            font-family: 'Segoe UI', 'Inter', sans-serif;
        }
        
        #centerWidget {
            background-color: #F8F9FA;
        }
        
        #formWidget {
            background-color: white;
            border-radius: 16px;
        }
        
        #titleLabel {
            font-size: 32px;
            font-weight: 600;
            color: #1A202C;
        }
        
        #subtitleLabel {
            font-size: 14px;
            color: #718096;
        }
        
        #inputLabel {
            font-size: 14px;
            font-weight: 500;
            color: #2D3748;
        }
        
        #modernInput {
            border: 2px solid #E2E8F0;
            border-radius: 8px;
            padding: 0 16px;
            font-size: 14px;
            background-color: white;
            color: #2D3748;
        }
        
        #modernInput:focus {
            border: 2px solid #4F46E5;
            outline: none;
        }
        
        #primaryButton {
            background-color: #4F46E5;
            color: white;
            border: none;
            border-radius: 8px;
            font-size: 15px;
            font-weight: 600;
            padding: 0 24px;
        }
        
        #primaryButton:hover {
            background-color: #4338CA;
        }
        
        #primaryButton:pressed {
            background-color: #3730A3;
        }
        
        #linkButton {
            background-color: transparent;
            color: #4F46E5;
            border: none;
            font-size: 14px;
            font-weight: 600;
            text-decoration: underline;
        }
        
        #linkButton:hover {
            color: #4338CA;
        }
    )";
}

void EliteLoginWindow::onLoginClicked()
{
    QString email = emailInput->text().trimmed();
    QString password = passwordInput->text();
    
    // Basic validation
    if (email.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter both email and password.");
        return;
    }
    
    // For demo purposes, accept any non-empty credentials
    // In production, validate against database
    
    try {
        if (!mainWindow) {
            mainWindow = new EliteMainWindow();
        }
        
        // Enable maximize and fullscreen
        mainWindow->setWindowFlags(Qt::Window);
        mainWindow->setWindowState(Qt::WindowMaximized);
        
        mainWindow->show();
        this->hide();
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Error", 
            QString("Failed to open main window:\n%1\n\nPlease check database connection.").arg(e.what()));
    } catch (...) {
        QMessageBox::critical(this, "Error", 
            "An unexpected error occurred while opening the main window.\n\n"
            "Please check:\n"
            "1. PostgreSQL is running\n"
            "2. Database 'auction_db' exists\n"
            "3. Password in elite_main_window.cpp is correct");
    }
}

void EliteLoginWindow::onSignUpClicked()
{
    SignUpDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        // Auto-fill the login form with new credentials
        emailInput->setText(dialog.getEmail());
        passwordInput->setText(dialog.getPassword());
        
        // Show success message with better styling
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("Account Created");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("<h3 style='color: #10B981;'>✓ Welcome to AuctionHub!</h3>");
        msgBox.setInformativeText(
            "<p style='color: #2D3748;'>Your account has been created successfully!</p>"
            "<p style='color: #718096; margin-top: 10px;'>Your credentials have been filled in. "
            "Click <b>Sign In</b> to continue.</p>");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.button(QMessageBox::Ok)->setStyleSheet(
            "background-color: #4F46E5; color: white; padding: 8px 24px; "
            "border-radius: 6px; font-weight: 600; min-width: 80px;");
        msgBox.setStyleSheet("QMessageBox { background-color: white; } QLabel { color: #1A202C; }");
        msgBox.exec();
    }
}
