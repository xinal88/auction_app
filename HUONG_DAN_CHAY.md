# 🚀 HƯỚNG DẪN CHẠY PROJECT

## Cấu hình Database

Project đã được cấu hình để sử dụng:
- **Username**: postgres
- **Password**: (không có mật khẩu)
- **Database**: auction_db

## Bước 1: Setup Database

```bash
# Start PostgreSQL
sudo service postgresql start

# Tạo database (không cần tạo user vì dùng postgres có sẵn)
sudo -u postgres createdb auction_db

# Import schema và data
sudo -u postgres psql -d auction_db -f data/schema.sql
sudo -u postgres psql -d auction_db -f data/data.sql
```

## Bước 2: Build Server

```bash
cd auction_app

# Clean và build
make clean
make server
```

## Bước 3: Chạy Server

```bash
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

## Bước 4: Build Client (Terminal mới)

```bash
cd auction_app

# Build với Qt
qmake auction_client.pro
make

# Chạy client
./auction_client
```

## Bước 5: Test

**Accounts có sẵn:**
- Username: `alice`, Password: `pass123`
- Username: `bob`, Password: `pass123`
- Username: `charlie`, Password: `pass123`

**Test flow:**
1. Login với alice
2. Tab Account: Deposit tiền
3. Tab Rooms: Tạo hoặc join phòng
4. Tab Auction: Tạo item hoặc bid

## Troubleshooting

### Lỗi database connection
```bash
# Check PostgreSQL đang chạy
sudo service postgresql status

# Restart PostgreSQL
sudo service postgresql restart

# Check database tồn tại
sudo -u postgres psql -l | grep auction_db
```

### Lỗi port 5500 đã được sử dụng
```bash
# Tìm process đang dùng port
sudo netstat -tulpn | grep 5500

# Kill process
sudo kill -9 <PID>
```

### Reset database
```bash
# Drop và tạo lại
sudo -u postgres dropdb auction_db
sudo -u postgres createdb auction_db
sudo -u postgres psql -d auction_db -f data/schema.sql
sudo -u postgres psql -d auction_db -f data/data.sql
```

---

**Chúc bạn chạy thành công! 🎉**
