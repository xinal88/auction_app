# 🖥️ HƯỚNG DẪN CHẠY CLIENT TRÊN WSL

## Vấn đề hiện tại

Client Qt cần X server để hiển thị UI, nhưng WSL không có GUI mặc định.

## ✅ Giải pháp 1: Dùng X Server (Khuyến nghị)

### Bước 1: Cài đặt VcXsrv (Windows)

1. Download VcXsrv: https://sourceforge.net/projects/vcxsrv/
2. Cài đặt và chạy XLaunch
3. Chọn:
   - Multiple windows
   - Display number: 0
   - Start no client
   - ✅ Disable access control

### Bước 2: Cấu hình WSL

```bash
# Thêm vào ~/.bashrc
echo 'export DISPLAY=$(cat /etc/resolv.conf | grep nameserver | awk "{print \$2}"):0' >> ~/.bashrc
source ~/.bashrc

# Hoặc dùng cố định
export DISPLAY=:0
```

### Bước 3: Chạy Client

```bash
cd /mnt/f/AI_project/[HUST]Auction_Application_v1/auction_app
./auction_client
```

---

## ✅ Giải pháp 2: Build Client trên Windows Native

### Yêu cầu

1. **Qt 5.15 hoặc Qt 6.x cho Windows**
   - Download: https://www.qt.io/download-qt-installer
   - Chọn MinGW kit

2. **Qt Creator**

### Bước 1: Mở Qt Creator

1. Mở Qt Creator
2. File → Open File or Project
3. Chọn: `F:\AI_project\[HUST]Auction_Application_v1\auction_app\auction_client.pro`

### Bước 2: Configure Project

1. Chọn MinGW kit
2. Click "Configure Project"

### Bước 3: Build và Run

1. Build → Build Project (Ctrl+B)
2. Build → Run (Ctrl+R)

### Bước 4: Connect tới Server

Client sẽ tự động connect tới `127.0.0.1:5500` (server đang chạy trong WSL)

---

## ✅ Giải pháp 3: Dùng WSL2 với WSLg (Windows 11)

Nếu bạn dùng Windows 11, WSL2 đã có GUI support:

```bash
# Update WSL
wsl --update

# Restart WSL
wsl --shutdown

# Chạy client
cd /mnt/f/AI_project/[HUST]Auction_Application_v1/auction_app
./auction_client
```

---

## 🔍 Kiểm tra Server đang chạy

```bash
# Check process
ps aux | grep auction_server

# Check port
netstat -tulpn | grep 5500

# Check log
tail -f server.log
```

---

## 🧪 Test Connection

```bash
# Test từ WSL
telnet localhost 5500

# Hoặc
nc -zv localhost 5500
```

---

## ⚠️ Troubleshooting

### Lỗi: cannot connect to X server

**Giải pháp:**
```bash
# Check DISPLAY
echo $DISPLAY

# Set lại
export DISPLAY=:0

# Hoặc với WSL2
export DISPLAY=$(cat /etc/resolv.conf | grep nameserver | awk '{print $2}'):0
```

### Lỗi: Connection refused

**Nguyên nhân:** VcXsrv chưa chạy hoặc firewall block

**Giải pháp:**
1. Chạy VcXsrv với "Disable access control"
2. Tắt Windows Firewall tạm thời
3. Hoặc thêm rule cho VcXsrv

### Client không connect tới server

**Kiểm tra:**
```bash
# Server có đang chạy?
ps aux | grep auction_server

# Port có mở?
netstat -tulpn | grep 5500
```

---

## 📝 Khuyến nghị

**Cho demo nhanh:** Dùng Giải pháp 2 (Qt Creator trên Windows)
- Không cần config X server
- UI mượt mà hơn
- Dễ debug

**Cho development:** Dùng Giải pháp 1 (VcXsrv)
- Tất cả chạy trong WSL
- Gần với môi trường Linux thật

---

## 🎯 Quick Commands

```bash
# Server (WSL)
cd /mnt/f/AI_project/[HUST]Auction_Application_v1/auction_app
./auction_server

# Client Option 1: WSL với X server
export DISPLAY=:0
./auction_client

# Client Option 2: Windows Qt Creator
# Mở Qt Creator → Open auction_client.pro → Build → Run
```

---

**Server đang chạy tốt! Chỉ cần setup client UI là xong! 🚀**
