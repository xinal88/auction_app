# 🎯 HƯỚNG DẪN CÀI ĐẶT VÀ CHẠY ỨNG DỤNG ĐẤU GIÁ

## 📋 Mục lục
1. [Yêu cầu hệ thống](#yêu-cầu-hệ-thống)
2. [Cài đặt Dependencies](#cài-đặt-dependencies)
3. [Setup Database](#setup-database)
4. [Build và chạy Server](#build-và-chạy-server)
5. [Build và chạy Client](#build-và-chạy-client)
6. [Test ứng dụng](#test-ứng-dụng)
7. [Troubleshooting](#troubleshooting)

---

## 🖥️ Yêu cầu hệ thống

### Server (C)
- **GCC compiler** (hoặc Clang)
- **PostgreSQL** 12+ và development libraries
- **pthread** library (thường có sẵn trên Linux)
- **Make**

### Client (Qt/C++)
- **Qt 5.12+** hoặc **Qt 6.x**
- **Qt Creator** (khuyến nghị) hoặc qmake
- **C++ compiler** (g++/clang/MSVC)

---

## 📦 Cài đặt Dependencies

### Ubuntu/Debian
```bash
# Update package list
sudo apt-get update

# Server dependencies
sudo apt-get install -y build-essential libpq-dev postgresql postgresql-contrib

# Client dependencies (Qt 5)
sudo apt-get install -y qt5-default qtcreator qtbase5-dev

# Hoặc Qt 6
sudo apt-get install -y qt6-base-dev qt6-tools-dev qt6-tools-dev-tools qtcreator
```

### Windows
1. **PostgreSQL**: Download từ https://www.postgresql.org/download/windows/
2. **MinGW/MSVC**: Cài đặt compiler
3. **Qt**: Download từ https://www.qt.io/download
   - Chọn Qt 5.15 hoặc Qt 6.x
   - Chọn MinGW hoặc MSVC kit

### macOS
```bash
# Install Homebrew nếu chưa có
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install dependencies
brew install postgresql qt@5
brew services start postgresql
```

---

## 🗄️ Setup Database

### Bước 1: Khởi động PostgreSQL

**Linux:**
```bash
sudo service postgresql start
# Hoặc
sudo systemctl start postgresql
```

**Windows:**
- PostgreSQL service tự động start sau khi cài đặt
- Hoặc start từ Services (services.msc)

**macOS:**
```bash
brew services start postgresql
```

### Bước 2: Tạo User và Database

```bash
cd auction_app

# Tạo user 'trung' với password '123'
sudo -u postgres psql -f data/create_user.sql

# Tạo database 'auction_db'
sudo -u postgres createdb -O trung auction_db

# Hoặc trên Windows (mở cmd với quyền admin):
psql -U postgres -f data\create_user.sql
createdb -U postgres -O trung auction_db
```

### Bước 3: Import Schema và Data

```bash
# Import schema
psql -U trung -d auction_db -f data/schema.sql

# Import sample data
psql -U trung -d auction_db -f data/data.sql
```

**Lưu ý:** Nếu gặp lỗi authentication, edit file `pg_hba.conf`:
```bash
# Linux
sudo nano /etc/postgresql/*/main/pg_hba.conf

# Thay đổi dòng:
# local   all   all   peer
# Thành:
local   all   all   md5

# Restart PostgreSQL
sudo service postgresql restart
```

### Bước 4: Verify Database

```bash
psql -U trung -d auction_db

# Trong psql prompt:
\dt                    # List tables
SELECT * FROM users;   # Check data
\q                     # Quit
```

---

## 🚀 Build và chạy Server

### Linux/macOS

```bash
cd auction_app

# Clean previous builds
make clean

# Build server
make server

# Run server
./auction_server
```

Bạn sẽ thấy output:
```
===========================================
   Auction Server - Network Programming   
===========================================

[2024-11-27 10:30:00] [INFO] === Auction Server Starting ===
[2024-11-27 10:30:00] [INFO] Session manager initialized
[2024-11-27 10:30:00] [INFO] Timer manager started
[2024-11-27 10:30:00] [INFO] Database connected
[2024-11-27 10:30:00] [INFO] Server listening on port 5500
Server is listening on port 5500...
```

### Windows (MinGW)

```cmd
cd auction_app

REM Build
mingw32-make clean
mingw32-make server

REM Run
auction_server.exe
```

### Chạy server ở background (Linux)

```bash
# Run in background
nohup ./auction_server > server_output.log 2>&1 &

# Check if running
ps aux | grep auction_server

# Stop server
pkill auction_server
```

---

## 🎨 Build và chạy Client

### Sử dụng Qt Creator (Khuyến nghị)

1. **Mở Qt Creator**
2. **File → Open File or Project**
3. Chọn file `auction_app/auction_client.pro`
4. **Configure Project**: Chọn kit phù hợp (Desktop Qt 5.x hoặc 6.x)
5. **Build → Build Project** (Ctrl+B)
6. **Run** (Ctrl+R)

### Sử dụng Command Line

**Linux/macOS:**
```bash
cd auction_app

# Generate Makefile
qmake auction_client.pro
# Hoặc nếu dùng Qt 6:
qmake6 auction_client.pro

# Build
make

# Run
./auction_client
```

**Windows (MinGW):**
```cmd
cd auction_app

REM Generate Makefile
qmake auction_client.pro

REM Build
mingw32-make

REM Run
release\auction_client.exe
```

---

## 🧪 Test ứng dụng

### 1. Khởi động Server
```bash
./auction_server
```

### 2. Khởi động Client (có thể mở nhiều cửa sổ)

### 3. Đăng nhập với tài khoản test

Database đã có sẵn 10 users:
- **Username**: `alice`, `bob`, `charlie`, `david`, `emma`, `frank`, `hannah`, `ian`, `julia`, `kevin`
- **Password**: `pass123` (cho tất cả)

### 4. Test các chức năng

#### A. Account Management
1. Login với user `alice` / `pass123`
2. Tab **Account**:
   - Deposit: Nhập `1000000` → Click **Deposit**
   - Redeem: Nhập `500000` → Click **Redeem**
   - View History: Click **Refresh History**

#### B. Room Management
1. Tab **Rooms**:
   - Tạo phòng mới: Nhập tên và mô tả → Click **Create Room**
   - Click **Refresh** để xem danh sách phòng
   - Double-click vào phòng hoặc chọn và click **Join Room**

#### C. Auction
1. Sau khi join phòng, tab **Auction**:
   - Click **Refresh Items** để xem items
   - Chọn item → Nhập giá → Click **Place Bid**
   - Hoặc click **Buy Now** để mua ngay

#### D. Chat
1. Trong tab **Auction**:
   - Nhập tin nhắn ở ô chat
   - Click **Send** hoặc Enter
   - Tất cả users trong phòng sẽ nhận được

#### E. Test Multi-user
1. Mở 2-3 client windows
2. Login với users khác nhau (`bob`, `charlie`)
3. Join cùng một phòng
4. Test bidding và chat real-time

---

## 🔧 Troubleshooting

### Server không kết nối được database

**Lỗi:** `DB Connection failed: FATAL: password authentication failed`

**Giải pháp:**
```bash
# Check PostgreSQL đang chạy
sudo service postgresql status

# Reset password
sudo -u postgres psql
ALTER USER trung WITH PASSWORD '123';
\q

# Hoặc edit connection string trong src/server/server.c:
const char *conninfo = "host=localhost dbname=auction_db user=trung password=123";
```

### Client không kết nối được server

**Lỗi:** `Failed to connect to server`

**Giải pháp:**
1. Check server đang chạy: `ps aux | grep auction_server`
2. Check port 5500 không bị block:
   ```bash
   # Linux
   sudo netstat -tulpn | grep 5500
   
   # Windows
   netstat -ano | findstr 5500
   ```
3. Thử connect với `127.0.0.1` thay vì `localhost`
4. Tắt firewall tạm thời để test

### Lỗi compile server

**Lỗi:** `fatal error: libpq-fe.h: No such file or directory`

**Giải pháp:**
```bash
# Ubuntu/Debian
sudo apt-get install libpq-dev

# Fedora/RHEL
sudo dnf install postgresql-devel

# macOS
brew install postgresql
```

### Lỗi compile client (Qt)

**Lỗi:** `Project ERROR: Unknown module(s) in QT: widgets`

**Giải pháp:**
```bash
# Ubuntu
sudo apt-get install qtbase5-dev

# Hoặc check Qt installation
qmake --version
```

### Port 5500 đã được sử dụng

**Giải pháp:**
```bash
# Linux: Kill process using port 5500
sudo lsof -ti:5500 | xargs kill -9

# Windows
netstat -ano | findstr 5500
taskkill /PID <PID> /F

# Hoặc đổi port trong src/server/server.c và src/client/main.cpp
```

### Database schema errors

**Giải pháp:**
```bash
# Drop và recreate database
dropdb -U trung auction_db
createdb -U trung auction_db
psql -U trung -d auction_db -f data/schema.sql
psql -U trung -d auction_db -f data/data.sql
```

---

## 📝 Logs

- **Server log**: `server.log` (trong thư mục chạy server)
- **Client log**: `client.log` (trong thư mục chạy client)

Xem logs real-time:
```bash
# Linux/macOS
tail -f server.log
tail -f client.log

# Windows
Get-Content server.log -Wait
```

---

## 🎯 Các tính năng đã implement

✅ Đăng ký/Đăng nhập với session management  
✅ Tạo và quản lý phòng đấu giá  
✅ Tạo/xóa items với queue management  
✅ Bidding với validation ≥10,000 VND  
✅ Buy Now  
✅ Timer với 30s warning và auto-reset  
✅ Real-time notifications (bid, chat, timer)  
✅ Deposit/Redeem money  
✅ Transaction history  
✅ Room chat  
✅ Multi-threaded server  
✅ Thread-safe session và timer management  
✅ Comprehensive logging  

---

## 📞 Support

Nếu gặp vấn đề, check:
1. Server logs: `server.log`
2. Client logs: `client.log`
3. PostgreSQL logs: `/var/log/postgresql/`
4. Network connectivity: `telnet localhost 5500`

---

**Chúc bạn test thành công! 🎉**
