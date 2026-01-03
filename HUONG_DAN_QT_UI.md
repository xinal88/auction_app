# 🎨 HƯỚNG DẪN QT UI

## Tổng quan về UI hiện có

Project đã có sẵn 2 cửa sổ chính:
1. **LoginWindow** - Màn hình đăng nhập/đăng ký
2. **MainWindow** - Màn hình chính với 3 tabs (Account, Rooms, Auction)

## Cấu trúc UI

```
LoginWindow (login_window.cpp/h)
├── Username input
├── Password input  
├── Login button
└── Register button

MainWindow (main_window.cpp/h)
├── Tab 1: Account
│   ├── Balance display
│   ├── Deposit input + button
│   └── Transaction history
├── Tab 2: Rooms
│   ├── Room list
│   ├── Create room button
│   └── Join room button
└── Tab 3: Auction
    ├── Item list
    ├── Create item button
    ├── Bid input + button
    └── Chat box
```

## Cách chạy Qt UI

### Option 1: Trên Windows (Khuyến nghị)

#### Bước 1: Cài Qt

1. Download Qt: https://www.qt.io/download-qt-installer-oss
2. Chạy installer
3. Chọn:
   - Qt 5.15.x hoặc Qt 6.x
   - MinGW 64-bit compiler
   - Qt Creator IDE

#### Bước 2: Mở project trong Qt Creator

1. Mở **Qt Creator**
2. **File** → **Open File or Project**
3. Chọn file: `F:\AI_project\[HUST]Auction_Application_v1\auction_app\auction_client.pro`
4. **Configure Project**:
   - Chọn kit: **Desktop Qt 5.15.x MinGW 64-bit** (hoặc Qt 6)
   - Click **Configure Project**

#### Bước 3: Build và Run

1. Click nút **🔨 Build** (Ctrl+B)
2. Click nút **▶️ Run** (Ctrl+R)

#### Bước 4: Kết nối với Server

Server phải chạy trên WSL:

```bash
# Trong WSL terminal
cd /mnt/f/AI_project/[HUST]Auction_Application_v1/auction_app
./auction_server
```

Client trên Windows sẽ tự động connect tới `localhost:5500`

---

### Option 2: Trên WSL với X Server

#### Bước 1: Cài VcXsrv trên Windows

1. Download: https://sourceforge.net/projects/vcxsrv/
2. Chạy **XLaunch**:
   - Multiple windows
   - Display: 0
   - Start no client
   - ✅ **Disable access control**

#### Bước 2: Cấu hình WSL

```bash
# Set DISPLAY
export DISPLAY=$(cat /etc/resolv.conf | grep nameserver | awk '{print $2}'):0

# Test X server
xclock  # Nếu hiện đồng hồ = thành công
```

#### Bước 3: Build và Run

```bash
cd /mnt/f/AI_project/[HUST]Auction_Application_v1/auction_app

# Build
qmake auction_client.pro
make

# Run
./auction_client
```

---

## Cấu trúc code Qt UI

### 1. LoginWindow (login_window.cpp)

```cpp
// Constructor tạo UI
LoginWindow::LoginWindow(QWidget *parent) {
    // Tạo widgets
    usernameEdit = new QLineEdit(this);
    passwordEdit = new QLineEdit(this);
    loginButton = new QPushButton("Login", this);
    
    // Layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(usernameEdit);
    layout->addWidget(passwordEdit);
    layout->addWidget(loginButton);
    
    // Connect signals
    connect(loginButton, &QPushButton::clicked, 
            this, &LoginWindow::onLoginClicked);
}

// Slot xử lý khi click Login
void LoginWindow::onLoginClicked() {
    QString username = usernameEdit->text();
    QString password = passwordEdit->text();
    
    // Gửi request qua NetworkClient
    networkClient->login(username, password);
}
```

### 2. MainWindow (main_window.cpp)

```cpp
// Constructor tạo tabs
MainWindow::MainWindow(QWidget *parent) {
    tabWidget = new QTabWidget(this);
    
    // Tab 1: Account
    QWidget *accountTab = new QWidget();
    balanceLabel = new QLabel("Balance: 0 VND");
    depositButton = new QPushButton("Deposit");
    // ... thêm widgets
    
    // Tab 2: Rooms
    QWidget *roomsTab = new QWidget();
    roomList = new QListWidget();
    createRoomButton = new QPushButton("Create Room");
    // ... thêm widgets
    
    // Tab 3: Auction
    QWidget *auctionTab = new QWidget();
    itemList = new QListWidget();
    bidButton = new QPushButton("Bid");
    chatBox = new QTextEdit();
    // ... thêm widgets
    
    tabWidget->addTab(accountTab, "Account");
    tabWidget->addTab(roomsTab, "Rooms");
    tabWidget->addTab(auctionTab, "Auction");
}
```

### 3. NetworkClient (network_client.cpp)

```cpp
// Kết nối tới server
void NetworkClient::connectToServer() {
    socket = new QTcpSocket(this);
    socket->connectToHost("127.0.0.1", 5500);
    
    connect(socket, &QTcpSocket::readyRead,
            this, &NetworkClient::onReadyRead);
}

// Gửi message
void NetworkClient::login(QString username, QString password) {
    MessageHeader header;
    header.type = LOGIN_REQ;
    header.payload_length = sizeof(LoginReq);
    
    LoginReq req;
    strcpy(req.username, username.toStdString().c_str());
    strcpy(req.password, password.toStdString().c_str());
    
    socket->write((char*)&header, sizeof(header));
    socket->write((char*)&req, sizeof(req));
}

// Nhận response
void NetworkClient::onReadyRead() {
    // Đọc header
    MessageHeader header;
    socket->read((char*)&header, sizeof(header));
    
    // Đọc payload
    QByteArray payload = socket->read(header.payload_length);
    
    // Xử lý theo type
    switch(header.type) {
        case LOGIN_RES:
            handleLoginResponse(payload);
            break;
        case BID_NOTIFY:
            handleBidNotify(payload);
            break;
        // ...
    }
}
```

---

## Cách tùy chỉnh UI

### Thay đổi màu sắc

```cpp
// Trong constructor
loginButton->setStyleSheet(
    "QPushButton {"
    "  background-color: #4CAF50;"
    "  color: white;"
    "  border-radius: 5px;"
    "  padding: 10px;"
    "}"
    "QPushButton:hover {"
    "  background-color: #45a049;"
    "}"
);
```

### Thêm icon

```cpp
loginButton->setIcon(QIcon(":/icons/login.png"));
loginButton->setIconSize(QSize(24, 24));
```

### Thay đổi font

```cpp
QFont font("Arial", 12, QFont::Bold);
titleLabel->setFont(font);
```

### Thêm spacing

```cpp
layout->setSpacing(10);
layout->setContentsMargins(20, 20, 20, 20);
```

---

## Sử dụng Qt Designer (GUI Editor)

### Bước 1: Tạo .ui file

1. Qt Creator → **File** → **New File**
2. Chọn **Qt** → **Qt Designer Form**
3. Chọn template: **Widget** hoặc **Main Window**
4. Đặt tên: `login_window.ui`

### Bước 2: Vẽ UI

1. Kéo thả widgets từ bên trái:
   - **Line Edit** cho username/password
   - **Push Button** cho Login/Register
   - **Label** cho tiêu đề
2. Sắp xếp với **Layouts**:
   - **Vertical Layout** (Ctrl+L)
   - **Horizontal Layout** (Ctrl+H)
   - **Grid Layout** (Ctrl+G)
3. Đặt tên object (objectName):
   - `usernameEdit`
   - `passwordEdit`
   - `loginButton`

### Bước 3: Sử dụng trong code

```cpp
// login_window.h
#include "ui_login_window.h"

class LoginWindow : public QWidget {
    Q_OBJECT
    
public:
    LoginWindow(QWidget *parent = nullptr);
    
private:
    Ui::LoginWindow *ui;  // Auto-generated từ .ui file
};

// login_window.cpp
LoginWindow::LoginWindow(QWidget *parent) 
    : QWidget(parent), ui(new Ui::LoginWindow) {
    ui->setupUi(this);  // Load UI từ .ui file
    
    // Connect signals
    connect(ui->loginButton, &QPushButton::clicked,
            this, &LoginWindow::onLoginClicked);
}
```

---

## Debug UI

### Xem log

```cpp
#include <QDebug>

qDebug() << "Username:" << username;
qDebug() << "Connected to server";
```

### Hiển thị message box

```cpp
#include <QMessageBox>

QMessageBox::information(this, "Success", "Login successful!");
QMessageBox::warning(this, "Error", "Login failed!");
```

### Kiểm tra kết nối

```cpp
if (socket->state() == QAbstractSocket::ConnectedState) {
    qDebug() << "Connected";
} else {
    qDebug() << "Not connected";
}
```

---

## Troubleshooting

### UI không hiện

```bash
# Kiểm tra DISPLAY
echo $DISPLAY

# Test X server
xclock
```

### Build lỗi

```bash
# Clean và rebuild
make clean
qmake
make
```

### Không connect được server

```bash
# Kiểm tra server đang chạy
netstat -tulpn | grep 5500

# Kiểm tra firewall
sudo ufw allow 5500
```

---

## Tài liệu tham khảo

- Qt Documentation: https://doc.qt.io/
- Qt Widgets: https://doc.qt.io/qt-5/qtwidgets-index.html
- Qt Designer: https://doc.qt.io/qt-5/qtdesigner-manual.html
- Qt Signals & Slots: https://doc.qt.io/qt-5/signalsandslots.html

---

**Khuyến nghị: Chạy Qt UI trên Windows để có trải nghiệm tốt nhất!**
