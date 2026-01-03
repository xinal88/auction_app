# 🚀 HƯỚNG DẪN CHẠY QT CLIENT TRÊN WINDOWS

## Vấn đề hiện tại

Khi bạn click Run trong Qt Creator, ứng dụng bị crash vì:
1. ❌ Server chưa chạy
2. ❌ Client không kết nối được

## Giải pháp: Chạy theo thứ tự

### Bước 1: Chạy Server trên WSL

**Mở WSL terminal:**

```bash
cd /mnt/f/AI_project/[HUST]Auction_Application_v1/auction_app

# Kill server cũ nếu có
pkill -9 auction_server

# Chạy server
./auction_server
```

**Đợi thấy:**
```
===========================================
   Auction Server - Network Programming   
===========================================

Database connected successfully
Server is listening on port 5500...
```

✅ Server đã sẵn sàng!

### Bước 2: Build Client trong Qt Creator

1. Trong Qt Creator, click **Build** (🔨) hoặc Ctrl+B
2. Đợi build xong (xem Application Output)
3. Nếu có lỗi, xem phần Troubleshooting bên dưới

### Bước 3: Run Client

1. Click **Run** (▶️) hoặc Ctrl+R
2. Cửa sổ Login sẽ hiện ra!

### Bước 4: Login

**Thông tin đăng nhập:**
- Username: `alice`
- Password: `pass123`

**Hoặc các accounts khác:**
- bob / pass123
- charlie / pass123
- david / pass123
- emma / pass123

---

## Nếu vẫn bị crash

### Kiểm tra 1: Server có đang chạy không?

**Trong WSL:**
```bash
netstat -tulpn | grep 5500
```

Nếu thấy output → Server đang chạy ✅  
Nếu không thấy gì → Server chưa chạy ❌

### Kiểm tra 2: Xem log lỗi

Trong Qt Creator, xem tab **Application Output** (phía dưới).

**Lỗi thường gặp:**

#### Lỗi: "Connection refused"
```
QAbstractSocket::connectToHost: Connection refused
```

**Nguyên nhân:** Server chưa chạy  
**Giải pháp:** Chạy server trên WSL (Bước 1)

#### Lỗi: "Cannot find -lpq"
```
cannot find -lpq
```

**Nguyên nhân:** Thiếu PostgreSQL library  
**Giải pháp:** Cần cài PostgreSQL trên Windows hoặc chỉ chạy CLI client

#### Lỗi: "The process was ended forcefully"

**Nguyên nhân:** Ứng dụng crash khi khởi động  
**Giải pháp:** 
1. Đảm bảo server đang chạy
2. Xem chi tiết lỗi trong Application Output
3. Thử chạy CLI client thay thế

---

## Giải pháp thay thế: Dùng CLI Client

Nếu Qt Client vẫn không chạy được, dùng CLI client (đã hoạt động):

**Trong WSL:**
```bash
cd /mnt/f/AI_project/[HUST]Auction_Application_v1/auction_app

# Terminal 1: Server
./auction_server

# Terminal 2: Client
./auction_client_cli
```

CLI client có đầy đủ tính năng và chạy ổn định!

---

## Debug Qt Client

### Chạy ở chế độ Debug

1. Trong Qt Creator, click **Debug** (🐛) thay vì Run
2. Ứng dụng sẽ dừng tại breakpoint nếu có lỗi
3. Xem stack trace để biết lỗi ở đâu

### Thêm debug output

Trong `main.cpp`, thêm:

```cpp
#include <QDebug>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    qDebug() << "Application starting...";
    
    NetworkClient client;
    qDebug() << "NetworkClient created";
    
    client.connectToServer("127.0.0.1", 5500);
    qDebug() << "Connecting to server...";
    
    // ... rest of code
}
```

Xem output trong Application Output tab.

---

## Cấu trúc chạy đúng

```
┌─────────────────┐
│  WSL Terminal   │
│                 │
│ ./auction_server│  ← Chạy TRƯỚC
│  Port 5500      │
└────────┬────────┘
         │
         │ TCP Connection
         │
┌────────▼────────┐
│  Qt Creator     │
│                 │
│ Run Client      │  ← Chạy SAU
│ (Windows)       │
└─────────────────┘
```

---

## Checklist trước khi Run

- [ ] PostgreSQL đang chạy trong WSL
- [ ] Database `auction_db` đã được tạo
- [ ] Server đang chạy và listening port 5500
- [ ] Qt Creator đã build thành công
- [ ] Không có lỗi compile

---

## Tóm tắt lệnh

**WSL Terminal 1 - Server:**
```bash
cd /mnt/f/AI_project/[HUST]Auction_Application_v1/auction_app
./auction_server
```

**Qt Creator - Client:**
1. Build (Ctrl+B)
2. Run (Ctrl+R)
3. Login: alice / pass123

---

**Nếu vẫn gặp vấn đề, dùng CLI client để demo! 🎯**
