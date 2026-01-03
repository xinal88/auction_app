#ifndef ELITE_ACCOUNT_WINDOW_H
#define ELITE_ACCOUNT_WINDOW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

class EliteAccountWindow : public QWidget
{
    Q_OBJECT

public:
    explicit EliteAccountWindow(QWidget *parent = nullptr);
    ~EliteAccountWindow();
    
    void loadUserData(int userId);
    void refreshBalance();

signals:
    void balanceUpdated(double newBalance);

private slots:
    void onDepositClicked();
    void onWithdrawClicked();
    void onUpdateBankClicked();

private:
    void setupUI();
    QString getStyleSheet();
    QWidget* createCard();
    QWidget* createActivityItem(const QString &title, const QString &subtitle, const QString &status);
    QWidget* createDivider();
    void loadActivityHistory();
    
    int currentUserId;
    QLabel *balanceLabel;
    QLabel *bankAccountLabel;
    QLabel *userIdLabel;
    QLabel *emailLabel;
    QPushButton *depositBtn;
    QPushButton *withdrawBtn;
    QPushButton *updateBankBtn;
    QVBoxLayout *activityLayout;
};

#endif // ELITE_ACCOUNT_WINDOW_H
