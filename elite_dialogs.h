#ifndef ELITE_DIALOGS_H
#define ELITE_DIALOGS_H

#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QDateTimeEdit>
#include <QCheckBox>

// Create Room Dialog
class CreateRoomDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateRoomDialog(QWidget *parent = nullptr);
    
    QString getRoomName() const;
    QString getDescription() const;
    bool isPublic() const;

private:
    void setupUI();
    QString getStyleSheet();
    
    QLineEdit *roomNameInput;
    QTextEdit *descriptionInput;
    QCheckBox *publicCheckbox;
    QPushButton *createButton;
    QPushButton *cancelButton;
};

// Deposit Money Dialog
class DepositMoneyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DepositMoneyDialog(QWidget *parent = nullptr);
    
    double getAmount() const;

private slots:
    void onQuickAmountClicked();
    void onDepositClicked();

private:
    void setupUI();
    QString getStyleSheet();
    
    QLineEdit *amountInput;
    QPushButton *amount1MBtn;
    QPushButton *amount5MBtn;
    QPushButton *amount10MBtn;
    QPushButton *depositButton;
    QPushButton *cancelButton;
    QLabel *currentBalanceLabel;
};

// Withdraw Money Dialog
class WithdrawMoneyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WithdrawMoneyDialog(QWidget *parent = nullptr);
    
    double getAmount() const;

private slots:
    void onWithdrawClicked();

private:
    void setupUI();
    QString getStyleSheet();
    
    QLineEdit *amountInput;
    QPushButton *withdrawButton;
    QPushButton *cancelButton;
    QLabel *currentBalanceLabel;
    QLabel *bankInfoLabel;
};

// Bank Information Dialog
class BankInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BankInfoDialog(QWidget *parent = nullptr);
    
    QString getBankName() const;
    QString getAccountNumber() const;
    QString getAccountHolder() const;

private:
    void setupUI();
    QString getStyleSheet();
    
    QLineEdit *bankNameInput;
    QLineEdit *accountNumberInput;
    QLineEdit *accountHolderInput;
    QPushButton *saveButton;
    QPushButton *cancelButton;
};

// Sign Up Dialog
class SignUpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SignUpDialog(QWidget *parent = nullptr);
    
    QString getUsername() const;
    QString getEmail() const;
    QString getPassword() const;

private slots:
    void onSignUpClicked();

private:
    void setupUI();
    QString getStyleSheet();
    
    QLineEdit *usernameInput;
    QLineEdit *emailInput;
    QLineEdit *passwordInput;
    QLineEdit *confirmPasswordInput;
    QPushButton *signUpButton;
    QPushButton *cancelButton;
};

#endif // ELITE_DIALOGS_H
