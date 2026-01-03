#ifndef ELITE_MAIN_WINDOW_H
#define ELITE_MAIN_WINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QStackedWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QNetworkAccessManager>

class EliteAuctionRoom;
class EliteAccountWindow;
class EliteNetworkClient;

class EliteMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit EliteMainWindow(QWidget *parent = nullptr);
    ~EliteMainWindow();

private slots:
    void onExploreClicked();
    void onRoomsClicked();
    void onAccountClicked();
    void onCreateRoomClicked();
    void onRoomCardClicked(const QString &roomName);
    void onSearchTextChanged(const QString &text);

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    void setupUI();
    void setupNavigationBar();
    void setupExplorePage();
    void setupRoomsPage();
    QString getStyleSheet();
    QWidget* createRoomCard(int roomId, const QString &title, const QString &description, 
                           const QString &host, int participants, const QString &status,
                           const QString &imageUrl);
    void loadRoomsFromDatabase();
    void loadDemoRooms();
    void loadUserBalance();
    void loadImageForLabel(QLabel *label, const QString &url);
    
    // Navigation
    QWidget *navBar;
    QPushButton *exploreBtn;
    QPushButton *roomsBtn;
    QPushButton *accountBtn;
    QPushButton *createRoomBtn;
    QLabel *balanceLabel;
    
    // Pages
    QStackedWidget *stackedWidget;
    QWidget *explorePage;
    QWidget *roomsPage;
    EliteAccountWindow *accountPage;
    EliteAuctionRoom *auctionRoomPage;
    
    // Explore page widgets
    QLineEdit *searchInput;
    QPushButton *liveFilterBtn;
    QPushButton *upcomingFilterBtn;
    QWidget *roomsContainer;
    QVBoxLayout *roomsLayout;
    
    // Network
    EliteNetworkClient *networkClient;
    QNetworkAccessManager *networkManager;
    
    QString currentFilter;
    int currentUserId;
};

#endif // ELITE_MAIN_WINDOW_H
