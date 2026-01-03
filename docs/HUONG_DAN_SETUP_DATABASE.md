# Hướng Dẫn Setup Database và Chạy Ứng Dụng

## 📋 Yêu Cầu

1. **PostgreSQL** đã được cài đặt
2. **Qt Creator** với Qt 5.15+ hoặc Qt 6.x
3. **PostgreSQL Driver** cho Qt (libpq)

## 🗄️ Bước 1: Setup Database

### 1.1. Tạo Database

```bash
# Đăng nhập vào PostgreSQL
psql -U postgres

# Tạo database mới
CREATE DATABASE auction_db;

# Kết nối vào database
\c auction_db
```

### 1.2. Chạy Schema

```bash
# Từ thư mục auction_app
psql -U postgres -d auction_db -f data/schema.sql
```

### 1.3. Thêm Dữ Liệu Demo

```bash
# Thêm dữ liệu mẫu
psql -U postgres -d auction_db -f data/data.sql
```

### 1.4. Kiểm Tra Dữ Liệu

```sql
-- Kiểm tra rooms
SELECT * FROM auction_rooms;

-- Kiểm tra items
SELECT * FROM auction_items;

-- Kiểm tra users
SELECT * FROM users;
```

## 🔧 Bước 2: Cấu Hình Kết Nối Database

Mở file `elite_main_window.cpp` và cập nhật thông tin kết nối:

```cpp
// Dòng ~20
if (db->connectToDatabase("localhost", "auction_db", "postgres", "YOUR_PASSWORD")) {
    qDebug() << "Database connected successfully!";
    loadUserBalance();
}
```

**Thay đổi:**
- `"localhost"` - Host của PostgreSQL (thường là localhost)
- `"auction_db"` - Tên database
- `"postgres"` - Username PostgreSQL
- `"YOUR_PASSWORD"` - Password của bạn

## 🚀 Bước 3: Build và Chạy Ứng Dụng

### Windows

```bash
# Build
qmake elite_auction_app.pro
mingw32-make

# Hoặc sử dụng script
build_elite_ui.bat

# Chạy
run_elite_ui.bat
```

### Linux/Mac

```bash
# Build
qmake elite_auction_app.pro
make

# Chạy
./elite_auction_app
```

## ✨ Tính Năng Mới

### 1. Kết Nối Database Thực Tế
- ✅ Load rooms từ database
- ✅ Hiển thị items thực tế
- ✅ Load balance người dùng
- ✅ Hỗ trợ hình ảnh từ URL

### 2. Responsive Layout
- ✅ Tự động điều chỉnh khi fullscreen
- ✅ Layout 3 cột linh hoạt
- ✅ Scroll smooth cho danh sách dài

### 3. Buy Now với Confirmation
- ✅ Popup xác nhận chi tiết
- ✅ Hiển thị thông tin item và giá
- ✅ Cảnh báo không thể hoàn tác
- ✅ Styling đẹp mắt

### 4. Hình Ảnh Sản Phẩm
- ✅ Load hình từ URL (Unsplash)
- ✅ Fallback emoji nếu load fail
- ✅ Thumbnail cho upcoming items
- ✅ Smooth loading với QNetworkAccessManager

### 5. Filter Rooms
- ✅ Filter "Live" - chỉ hiện rooms đang active
- ✅ Filter "Upcoming" - chỉ hiện rooms sắp diễn ra
- ✅ "All" - hiện tất cả rooms

## 📊 Dữ Liệu Demo

Database đã được thêm 5 rooms với nhiều items:

### Rooms:
1. **Luxury Watches Auction** (LIVE) - 12 participants
2. **Vintage Electronics** (UPCOMING) - 8 participants
3. **Art & Collectibles** (LIVE) - 15 participants
4. **Rare Books Collection** (UPCOMING) - 6 participants
5. **Designer Fashion** (LIVE) - 20 participants

### Items (với hình ảnh):
- Rolex Submariner - 50M đ
- Omega Speedmaster - 30M đ
- Patek Philippe Calatrava - 80M đ
- Apple Macintosh 128K - 8M đ
- Limited Edition Print - 15M đ
- Hermès Birkin Bag - 200M đ
- Và nhiều items khác...

## 🔍 Kiểm Tra Kết Nối

Khi chạy ứng dụng, kiểm tra console output:

```
Database connected successfully!
```

Nếu thấy lỗi:
```
Database connection failed: [error message]
```

Kiểm tra lại:
1. PostgreSQL đã chạy chưa
2. Database name, username, password đúng chưa
3. PostgreSQL driver đã cài đặt chưa

## 🐛 Troubleshooting

### Lỗi: "QPSQL driver not loaded"

**Windows:**
```bash
# Copy libpq.dll vào thư mục Qt
# Thường ở: C:\Qt\6.x.x\mingw_64\bin\
```

**Linux:**
```bash
sudo apt-get install libpq-dev
```

### Lỗi: "Connection refused"

```bash
# Kiểm tra PostgreSQL đang chạy
sudo systemctl status postgresql

# Khởi động nếu chưa chạy
sudo systemctl start postgresql
```

### Lỗi: "Database does not exist"

```bash
# Tạo lại database
createdb -U postgres auction_db
psql -U postgres -d auction_db -f data/schema.sql
psql -U postgres -d auction_db -f data/data.sql
```

## 📝 Thêm Dữ Liệu Mới

### Thêm Room Mới:

```sql
INSERT INTO auction_rooms (room_name, created_by, description, status, participant_count, image_url)
VALUES ('Your Room Name', 1, 'Description', 'active', 0, 'https://image-url.com');
```

### Thêm Item Mới:

```sql
INSERT INTO auction_items (room_id, item_name, description, starting_price, current_price, 
                          buy_now_price, status, created_by, queue_position, image_url)
VALUES (1, 'Item Name', 'Description', 1000000, 1000000, 2000000, 
        'available', 1, 1, 'https://image-url.com');
```

## 🎨 Tùy Chỉnh Hình Ảnh

Bạn có thể thay đổi URL hình ảnh trong database:

```sql
-- Update room image
UPDATE auction_rooms 
SET image_url = 'https://your-image-url.com' 
WHERE room_id = 1;

-- Update item image
UPDATE auction_items 
SET image_url = 'https://your-image-url.com' 
WHERE item_id = 1;
```

**Nguồn hình ảnh miễn phí:**
- Unsplash: https://unsplash.com
- Pexels: https://pexels.com
- Pixabay: https://pixabay.com

## 🎯 Demo Flow

1. **Khởi động app** → Tự động kết nối database
2. **Explore page** → Hiển thị tất cả rooms từ DB
3. **Click filter** → Filter rooms theo status
4. **Click room card** → Vào auction room
5. **Xem current item** → Load từ DB với hình ảnh
6. **Xem upcoming items** → Sidebar bên trái
7. **Place bid** → Cập nhật vào DB
8. **Buy Now** → Popup confirmation → Xử lý mua

## 📞 Hỗ Trợ

Nếu gặp vấn đề, kiểm tra:
1. Console output trong Qt Creator
2. PostgreSQL logs
3. Network connectivity (cho load hình ảnh)

---

**Chúc bạn demo thành công! 🎉**
