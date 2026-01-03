#include <QApplication>
#include <QFont>
#include "elite_login_window.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    // Set application-wide font
    QFont font("Inter", 10);
    app.setFont(font);
    
    EliteLoginWindow loginWindow;
    loginWindow.show();
    
    return app.exec();
}
