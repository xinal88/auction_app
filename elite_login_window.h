#ifndef ELITE_LOGIN_WINDOW_H
#define ELITE_LOGIN_WINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

class EliteMainWindow;

class EliteLoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit EliteLoginWindow(QWidget *parent = nullptr);
    ~EliteLoginWindow();

private slots:
    void onLoginClicked();
    void onSignUpClicked();

private:
    void setupUI();
    QString getStyleSheet();
    
    QLineEdit *emailInput;
    QLineEdit *passwordInput;
    QPushButton *loginButton;
    QPushButton *signUpButton;
    QLabel *titleLabel;
    QLabel *subtitleLabel;
    
    EliteMainWindow *mainWindow;
};

#endif // ELITE_LOGIN_WINDOW_H
