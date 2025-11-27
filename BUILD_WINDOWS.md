# 🪟 BUILD TRÊN WINDOWS

## ⚠️ Lưu ý quan trọng

Server được viết bằng C với pthread và libpq, **không thể compile trực tiếp trên Windows** vì:
- Windows không có pthread native
- Windows không có libpq-dev như Linux
- Socket API khác nhau (Winsock vs BSD sockets)

## 🎯 Giải pháp

### Option 1: Sử dụng WSL (Khuyến nghị) ⭐

**Windows Subsystem for Linux** - Chạy Linux trong Windows

```powershell
# 1. Enable WSL
wsl --install

# 2. Restart máy

# 3. Mở Ubuntu terminal
wsl

# 4. Install dependencies
sudo apt-get update
sudo apt-get install build-essential libpq-dev postgresql

# 5. Navigate to project
cd /mnt/f/AI_project/[HUST]Auction_Application_v1/auction_app

# 6. Build
make clean
make server

# 7. Run
./auction_server
```

### Option 2: Sử dụng MinGW + pthread-win32

**Cần cài đặt:**
1. MinGW-w64
2. pthread-win32
3. PostgreSQL for Windows
4. libpq

**Khó khăn:**
- Phải port code sang Winsock
- Phải thay pthread bằng Windows threads
- Phải config libpq paths
- Tốn nhiều thời gian

### Option 3: Sử dụng Docker (Dễ nhất)

```powershell
# 1. Install Docker Desktop for Windows

# 2. Create Dockerfile
```

```dockerfile
FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    build-essential \
    libpq-dev \
    postgresql \
    postgresql-contrib

WORKDIR /app
COPY . .

RUN make clean && make server

CMD ["./auction_server"]
```

```powershell
# 3. Build image
docker build -t auction-server .

# 4. Run
docker run -p 5500:5500 auction-server
```

### Option 4: Sử dụng Virtual Machine

1. Install VirtualBox hoặc VMware
2. Cài Ubuntu 22.04
3. Follow Linux instructions

---

## 🎨 Client (Qt) trên Windows

Client Qt **có thể build trên Windows** vì Qt cross-platform:

### Yêu cầu

1. **Qt 5.15 hoặc Qt 6.x**
   - Download: https://www.qt.io/download
   - Chọn MinGW hoặc MSVC kit

2. **Qt Creator**
   - Đi kèm với Qt installer

### Build Client

```powershell
# Option 1: Sử dụng Qt Creator (Khuyến nghị)
# 1. Mở Qt Creator
# 2. File → Open File or Project
# 3. Chọn auction_client.pro
# 4. Configure project với MinGW kit
# 5. Build → Build Project (Ctrl+B)
# 6. Run (Ctrl+R)

# Option 2: Command line
cd auction_app
qmake auction_client.pro
mingw32-make
release\auction_client.exe
```

---

## 🚀 Khuyến nghị cho Windows

### Để test nhanh:

**1. Server: Dùng WSL**
```bash
wsl
cd /mnt/f/AI_project/[HUST]Auction_Application_v1/auction_app
make clean && make server
./auction_server
```

**2. Client: Dùng Qt Creator trên Windows**
- Mở Qt Creator
- Build và run auction_client.pro
- Connect to localhost:5500

### Để demo:

**Option A: Tất cả trên WSL**
- Server trên WSL
- Client cũng trên WSL (cần X server như VcXsrv)

**Option B: Hybrid**
- Server trên WSL
- Client trên Windows native (Qt)
- Connect qua localhost

**Option C: Tất cả trên Linux VM**
- Dùng VirtualBox
- Cài Ubuntu
- Build cả server và client

---

## 📝 Quick Setup với WSL

```powershell
# 1. Install WSL (PowerShell as Admin)
wsl --install -d Ubuntu-22.04

# 2. Restart máy

# 3. Mở Ubuntu từ Start Menu

# 4. Setup trong Ubuntu
sudo apt-get update
sudo apt-get install -y build-essential libpq-dev postgresql postgresql-contrib

# 5. Start PostgreSQL
sudo service postgresql start

# 6. Setup database
cd /mnt/f/AI_project/[HUST]Auction_Application_v1/auction_app
sudo -u postgres psql -f data/create_user.sql
sudo -u postgres createdb -O trung auction_db
psql -U trung -d auction_db -f data/schema.sql
psql -U trung -d auction_db -f data/data.sql

# 7. Build server
make clean && make server

# 8. Run server
./auction_server
```

**Trong PowerShell khác:**
```powershell
# Build client với Qt Creator
# Hoặc:
cd auction_app
qmake auction_client.pro
mingw32-make
release\auction_client.exe
```

---

## ❌ Tại sao không compile trực tiếp trên Windows?

### Vấn đề 1: pthread
```c
#include <pthread.h>  // ❌ Windows không có
```

**Giải pháp**: Dùng pthread-win32 hoặc port sang Windows threads

### Vấn đề 2: BSD Sockets
```c
#include <sys/socket.h>  // ❌ Windows dùng Winsock
#include <netinet/in.h>  // ❌ Windows không có
```

**Giải pháp**: Port sang Winsock2

### Vấn đề 3: PostgreSQL
```c
#include <libpq-fe.h>  // ❌ Cần config paths
```

**Giải pháp**: Install PostgreSQL for Windows và config include/lib paths

### Vấn đề 4: POSIX APIs
```c
#include <unistd.h>  // ❌ Windows không có
```

**Giải pháp**: Port sang Windows APIs

---

## 🎯 Kết luận

**Cho Windows users:**

1. **Nhanh nhất**: Dùng WSL (5 phút setup)
2. **Dễ nhất**: Dùng Docker
3. **Tốt nhất**: Dùng Linux VM

**Không khuyến nghị**: Port code sang native Windows (tốn nhiều thời gian)

---

## 📞 Troubleshooting

### WSL không start
```powershell
# Enable WSL feature
dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all /norestart
dism.exe /online /enable-feature /featurename:VirtualMachinePlatform /all /norestart

# Restart máy
```

### PostgreSQL không start trong WSL
```bash
sudo service postgresql start
# Nếu lỗi:
sudo pg_ctlcluster 14 main start
```

### Client không connect
```bash
# Check server đang chạy
ps aux | grep auction_server

# Check port
netstat -tulpn | grep 5500
```

---

**Khuyến nghị: Dùng WSL để có trải nghiệm tốt nhất! 🚀**
