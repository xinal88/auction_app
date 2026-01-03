# 🚀 QUICK START GUIDE

## Chạy nhanh trong 5 phút

### Bước 1: Setup Database (2 phút)

```bash
# Start PostgreSQL
sudo service postgresql start

# Tạo user và database
cd auction_app
sudo -u postgres psql -f data/create_user.sql
sudo -u postgres createdb -O trung auction_db

# Import schema và data
psql -U trung -d auction_db -f data/schema.sql
psql -U trung -d auction_db -f data/data.sql
```

### Bước 2: Build và chạy Server (1 phút)

```bash
# Build
make clean && make server

# Chạy server
./auction_server
```

Bạn sẽ thấy:
```
===========================================
   Auction Server - Network Programming   
===========================================

[INFO] === Auction Server Starting ===
[INFO] Session manager initialized
[INFO] Timer manager started
[INFO] Database connected
[INFO] Server listening on port 5500
Server is listening on port 5500...
```

### Bước 3: Build và chạy Client (2 phút)

**Terminal mới:**

```bash
cd auction_app

# Build
qmake auction_client.pro
make

# Chạy
./auction_client
```

### Bước 4: Test (1 phút)

1. **Login**: Username `alice`, Password `pass123`
2. **Tab Account**: Deposit `1000000` VND
3. **Tab Rooms**: 
   - Tạo phòng "Test Room"
   - Hoặc join phòng có sẵn
4. **Tab Auction**:
   - Tạo item mới hoặc
   - Bid vào item có sẵn

---

## Test Multi-user

**Terminal 1:**
```bash
./auction_client  # Login: alice
```

**Terminal 2:**
```bash
./auction_client  # Login: bob
```

**Test scenario:**
1. Alice tạo phòng "Auction Room"
2. Alice tạo item "iPhone 15", giá 8,000,000 VND, duration 60s
3. Bob join "Auction Room"
4. Bob bid 8,100,000 VND
5. Alice thấy notification ngay lập tức
6. Đợi timer còn 25s
7. Alice bid 8,200,000 VND
8. **Timer reset về 30s** ⭐
9. Chat test: Cả 2 gửi tin nhắn
10. Đợi hết thời gian → Item sold notification

---

## Accounts có sẵn

| Username | Password | Balance |
|----------|----------|---------|
| alice    | pass123  | 50,000,000 VND |
| bob      | pass123  | 30,000,000 VND |
| charlie  | pass123  | 15,000,000 VND |
| david    | pass123  | 8,000,000 VND |
| emma     | pass123  | 12,000,000 VND |

---

## Troubleshooting nhanh

### Server không start
```bash
# Check PostgreSQL
sudo service postgresql status

# Check port 5500
sudo netstat -tulpn | grep 5500
```

### Client không connect
```bash
# Check server đang chạy
ps aux | grep auction_server

# Test connection
telnet localhost 5500
```

### Database error
```bash
# Reset database
dropdb -U trung auction_db
createdb -U trung auction_db
psql -U trung -d auction_db -f data/schema.sql
psql -U trung -d auction_db -f data/data.sql
```

---

## Logs

```bash
# Xem server log real-time
tail -f server.log

# Xem client log
tail -f client.log
```

---

## Tính năng chính để test

✅ **Login/Register** - Tab Login  
✅ **Deposit/Redeem** - Tab Account  
✅ **Create/Join Room** - Tab Rooms  
✅ **Create Item** - Tab Auction (cần ở trong phòng)  
✅ **Bid** - Tab Auction (chọn item, nhập giá, click Bid)  
✅ **Buy Now** - Tab Auction (chọn item, click Buy Now)  
✅ **Chat** - Tab Auction (nhập tin nhắn, Enter)  
✅ **Timer** - Tự động countdown, 30s warning, auto-reset khi bid  

---

**Chúc bạn test thành công! 🎉**
