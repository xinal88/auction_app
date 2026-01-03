# Hướng Dẫn Setup Hoàn Chỉnh Cho Windows

## 📋 Yêu Cầu

- Windows 10/11
- Qt Creator với Qt 5.15+ hoặc Qt 6.x
- PostgreSQL 12+ (sẽ hướng dẫn cài)
- MinGW hoặc MSVC compiler

## 🗄️ Phần 1: Cài Đặt PostgreSQL (Nếu Chưa Có)

### Bước 1: Download PostgreSQL

1. Truy cập: https://www.postgresql.org/download/windows/
2. Click "Download the installer"
3. Chọn phiên bản mới nhất (PostgreSQL 16 recommended)
4. Download file .exe

### Bước 2: Cài Đặt PostgreSQL

1. Chạy file installer vừa download
2. Click "Next" qua các bước
3. **QUAN TRỌNG:** Nhớ password bạn đặt cho user `postgres`
4. Port mặc định: 5432 (giữ nguyên)
5. Locale: Default locale
6. Hoàn tất cài đặt

### Bước 3: Kiểm Tra Cài Đặt

```bash
# Chạy script kiểm tra
check_postgresql.bat
```

Nếu thấy "PostgreSQL is installed!" → OK, tiếp tục bước tiếp theo

## 🔧 Phần 2: Setup Database

### Cách 1: Dùng Script Tự Động (Khuyến Nghị)

```bash
# Chạy script setup
setup_database_windows.bat

# Nhập password PostgreSQL khi được hỏi
# Script sẽ tự động:
# - Tạo database auction_db
# - Import schema
# - Import dữ liệu demo
# - Verify kết quả
```

### Cách 2: Setup Thủ Công

#### Bước 2.1: Mở pgAdmin 4

1. Tìm "pgAdmin 4" trong Start Menu
2. Mở pgAdmin
3. Nhập master password (nếu được hỏi)
4. Expand "Servers" → "PostgreSQL"
5. Nhập password postgres

#### Bước 2.2: Tạo Database

1. Right-click "Databases" → "Create" → "Database"
2. Name: `auction_db`
3. Owner: `postgres`
4. Click "Save"

#### Bước 2.3: Import Schema

1. Click vào database `auction_db`
2. Click "Tools" → "Query Tool"
3. Mở file `data/schema.sql`
4. Copy toàn bộ nội dung
5. Paste vào Query Tool
6. Click "Execute" (F5)
7. Kiểm tra "Messages" - phải thấy "Query returned successfully"

#### Bước 2.4: Import Data

1. Trong Query Tool (vẫn ở database auction_db)
2. Mở file `data/data.sql`
3. Copy toàn bộ nội dung
4. Paste vào Query Tool
5. Click "Execute" (F5)
6. Kiểm tra thành công

#### Bước 2.5: Verify

Chạy query này để kiểm tra:

```sql
-- Kiểm tra rooms
SELECT * FROM auction_rooms;

-- Kiểm tra items
SELECT * FROM auction_items;

-- Kiểm tra users
SELECT * FROM users;
```

Phải thấy:
- 5 rooms
- 15+ items
- 10 users

## 🔌 Phần 3: Cấu Hình Kết Nối

### Bước 3.1: Mở File elite_main_window.cpp

Tìm dòng ~20, sửa thông tin kết nối:

```cpp
// TRƯỚC:
if (db->connectToDatabase("localhost", "auction_db", "postgres", "")) {

// SAU (thay YOUR_PASSWORD bằng password thực của bạn):
if (db->connectToDatabase("localhost", "auction_db", "postgres", "YOUR_PASSWORD")) {
```

**Ví dụ:**
```cpp
// Nếu password của bạn là "admin123"
if (db->connectToDatabase("localhost", "auction_db", "postgres", "admin123")) {
```

### Bước 3.2: Lưu File

Ctrl+S để lưu file

## 🏗️ Phần 4: Cài Đặt PostgreSQL Driver Cho Qt

### Kiểm Tra Driver

1. Mở Qt Creator
2. Help → About Plugins
3. Tìm "SQL" → Kiểm tra "QPSQL" có enabled không

### Nếu Thiếu Driver

#### Cách 1: Copy libpq.dll

1. Tìm file `libpq.dll` trong PostgreSQL:
   ```
   C:\Program Files\PostgreSQL\16\bin\libpq.dll
   ```

2. Copy vào thư mục Qt:
   ```
   C:\Qt\6.x.x\mingw_64\bin\
   ```

3. Copy thêm các file liên quan:
   - `libintl-9.dll`
   - `libiconv-2.dll`
   - `libssl-3-x64.dll`
   - `libcrypto-3-x64.dll`

#### Cách 2: Thêm PostgreSQL vào PATH

1. Right-click "This PC" → "Properties"
2. "Advanced system settings"
3. "Environment Variables"
4. Trong "System variables", tìm "Path"
5. Click "Edit"
6. Click "New"
7. Thêm: `C:\Program Files\PostgreSQL\16\bin`
8. Click "OK" tất cả
9. **Restart Qt Creator**

## 🚀 Phần 5: Build và Chạy

### Bước 5.1: Build

```bash
# Chạy script build
build_elite_ui.bat
```

Hoặc trong Qt Creator:
1. Mở file `elite_auction_app.pro`
2. Click "Build" (Ctrl+B)
3. Đợi build xong

### Bước 5.2: Chạy

```bash
# Chạy script
run_elite_ui.bat
```

Hoặc trong Qt Creator:
1. Click "Run" (Ctrl+R)

### Bước 5.3: Kiểm Tra

Khi app khởi động, kiểm tra console output trong Qt Creator:

✅ **Thành công:**
```
Database connected successfully!
```

❌ **Lỗi:**
```
Database connection failed: [error message]
```

## 🐛 Troubleshooting

### Lỗi 1: "QPSQL driver not loaded"

**Nguyên nhân:** Thiếu PostgreSQL driver

**Giải pháp:**
1. Copy `libpq.dll` từ PostgreSQL vào Qt (xem Phần 4)
2. Hoặc thêm PostgreSQL bin vào PATH
3. Restart Qt Creator

### Lỗi 2: "Connection refused"

**Nguyên nhân:** PostgreSQL service không chạy

**Giải pháp:**
1. Mở "Services" (Win+R → `services.msc`)
2. Tìm "postgresql-x64-16" (hoặc version bạn cài)
3. Right-click → "Start"

### Lỗi 3: "Password authentication failed"

**Nguyên nhân:** Password sai

**Giải pháp:**
1. Kiểm tra lại password trong `elite_main_window.cpp`
2. Đảm bảo password đúng với password bạn đặt khi cài PostgreSQL

### Lỗi 4: "Database does not exist"

**Nguyên nhân:** Chưa tạo database

**Giải pháp:**
1. Chạy lại `setup_database_windows.bat`
2. Hoặc tạo thủ công qua pgAdmin (xem Phần 2)

### Lỗi 5: "No rooms displayed"

**Nguyên nhân:** Chưa import dữ liệu

**Giải pháp:**
1. Mở pgAdmin
2. Chạy query: `SELECT * FROM auction_rooms;`
3. Nếu empty → Import lại `data/data.sql`

### Lỗi 6: Images không hiển thị

**Nguyên nhân:** Không có internet hoặc URL bị block

**Giải pháp:**
1. Kiểm tra internet connection
2. Images sẽ fallback về emoji nếu load fail
3. Đợi vài giây để images load

## 📊 Kiểm Tra Kết Quả

### Checklist:

- [ ] PostgreSQL đã cài và chạy
- [ ] Database `auction_db` đã tạo
- [ ] Schema đã import (7 tables)
- [ ] Data đã import (5 rooms, 15+ items)
- [ ] Password đã cấu hình trong code
- [ ] libpq.dll đã copy hoặc PATH đã set
- [ ] App build thành công
- [ ] App chạy và kết nối DB thành công
- [ ] Rooms hiển thị với hình ảnh
- [ ] Filter Live/Upcoming hoạt động
- [ ] Vào room và xem items được
- [ ] Buy Now popup hiển thị đẹp

## 🎯 Demo Flow

1. **Khởi động app** → Console: "Database connected successfully!"
2. **Explore page** → Thấy 5 rooms với hình ảnh
3. **Click "Live" filter** → Chỉ hiện 3 rooms LIVE
4. **Click "Luxury Watches Auction"** → Vào room
5. **Xem current item** → Rolex Submariner với hình ảnh
6. **Xem sidebar trái** → Upcoming items
7. **Click "Buy Now"** → Popup confirmation đẹp
8. **Click "Confirm Purchase"** → Success message

## 📞 Cần Hỗ Trợ?

### Kiểm tra logs:

1. **Qt Creator Console** - Xem output khi chạy app
2. **PostgreSQL Logs** - `C:\Program Files\PostgreSQL\16\data\log\`
3. **pgAdmin Query History** - Xem queries đã chạy

### Files quan trọng:

- `QUICK_DEMO_GUIDE.md` - Hướng dẫn demo nhanh
- `HUONG_DAN_SETUP_DATABASE.md` - Chi tiết database
- `CAI_TIEN_UI_DATABASE.md` - Báo cáo kỹ thuật

### Scripts hữu ích:

- `check_postgresql.bat` - Kiểm tra PostgreSQL
- `setup_database_windows.bat` - Setup database tự động
- `build_elite_ui.bat` - Build app
- `run_elite_ui.bat` - Chạy app

---

## ✅ Hoàn Thành!

Nếu tất cả các bước trên OK, bạn đã sẵn sàng demo!

**Thời gian setup:** 15-20 phút (lần đầu)
**Độ khó:** ⭐⭐⭐ (Trung bình)
**Kết quả:** 🔥🔥🔥 (Impressive!)

🎉 **Chúc bạn demo thành công!** 🎉
