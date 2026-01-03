# Setup Database Bằng pgAdmin (GUI) - Dễ Nhất!

## 🎯 Cách Này Dễ Nhất Cho Windows

Không cần command line, chỉ cần click chuột!

## 📋 Yêu Cầu

- PostgreSQL đã cài đặt (có pgAdmin 4)
- Biết password của user `postgres`

## 🚀 Các Bước Setup

### Bước 1: Mở pgAdmin 4

1. Tìm "pgAdmin 4" trong Start Menu
2. Click để mở
3. Đợi browser mở (pgAdmin chạy trên browser)
4. Nếu hỏi master password → Nhập password

### Bước 2: Kết Nối PostgreSQL

1. Trong cây bên trái, expand "Servers"
2. Click vào "PostgreSQL 16" (hoặc version bạn có)
3. Nhập password user `postgres`
4. Click "OK"

### Bước 3: Tạo Database

1. Right-click vào "Databases"
2. Chọn "Create" → "Database..."
3. Trong tab "General":
   - **Database:** `auction_db`
   - **Owner:** `postgres`
4. Click "Save"

✅ Database đã tạo!

### Bước 4: Import Schema

1. Click vào database `auction_db` vừa tạo
2. Click menu "Tools" → "Query Tool"
3. Mở file `data/schema.sql` bằng Notepad
4. Copy toàn bộ nội dung (Ctrl+A, Ctrl+C)
5. Paste vào Query Tool trong pgAdmin (Ctrl+V)
6. Click nút "Execute" (▶️) hoặc nhấn F5
7. Kiểm tra tab "Messages" phía dưới
8. Phải thấy: "Query returned successfully"

✅ Schema đã import! (7 tables)

### Bước 5: Import Data

1. Vẫn trong Query Tool (database auction_db)
2. Click nút "Clear" (🗑️) để xóa query cũ
3. Mở file `data/data.sql` bằng Notepad
4. Copy toàn bộ nội dung (Ctrl+A, Ctrl+C)
5. Paste vào Query Tool (Ctrl+V)
6. Click "Execute" (▶️) hoặc F5
7. Kiểm tra "Messages" → "Query returned successfully"

✅ Data đã import! (5 rooms, 15+ items)

### Bước 6: Verify Data

Trong Query Tool, chạy các query sau:

```sql
-- Kiểm tra rooms
SELECT * FROM auction_rooms;
```
Click Execute → Phải thấy 5 rooms

```sql
-- Kiểm tra items
SELECT * FROM auction_items;
```
Click Execute → Phải thấy 15+ items

```sql
-- Kiểm tra users
SELECT * FROM users;
```
Click Execute → Phải thấy 10 users

✅ Tất cả dữ liệu đã OK!

## 🔧 Bước 7: Cấu Hình Code

### 7.1. Mở File

Trong Qt Creator hoặc text editor:
- Mở file: `elite_main_window.cpp`
- Tìm dòng ~20

### 7.2. Sửa Password

**Trước:**
```cpp
if (db->connectToDatabase("localhost", "auction_db", "postgres", "")) {
```

**Sau:**
```cpp
if (db->connectToDatabase("localhost", "auction_db", "postgres", "YOUR_PASSWORD")) {
```

**Ví dụ:** Nếu password là `admin123`:
```cpp
if (db->connectToDatabase("localhost", "auction_db", "postgres", "admin123")) {
```

### 7.3. Lưu File

Ctrl+S để lưu

## 🏗️ Bước 8: Build & Run

### 8.1. Build

Double-click: `build_elite_ui.bat`

Hoặc trong Qt Creator:
- Mở `elite_auction_app.pro`
- Click "Build" (Ctrl+B)

### 8.2. Run

Double-click: `run_elite_ui.bat`

Hoặc trong Qt Creator:
- Click "Run" (Ctrl+R)

### 8.3. Kiểm Tra

Trong console output, phải thấy:
```
Database connected successfully!
```

✅ Thành công!

## 🎯 Kết Quả

App sẽ hiển thị:
- ✅ 5 auction rooms với hình ảnh
- ✅ Filter Live/Upcoming
- ✅ Click room → Vào auction
- ✅ Items với hình ảnh đẹp
- ✅ Buy Now popup
- ✅ Balance từ database

## 🐛 Nếu Gặp Lỗi

### "QPSQL driver not loaded"

**Giải pháp:**
1. Tìm file `libpq.dll`:
   ```
   C:\Program Files\PostgreSQL\16\bin\libpq.dll
   ```

2. Copy vào thư mục Qt:
   ```
   C:\Qt\6.x.x\mingw_64\bin\
   ```

3. Copy thêm các file:
   - `libintl-9.dll`
   - `libiconv-2.dll`
   - `libssl-3-x64.dll`
   - `libcrypto-3-x64.dll`

4. Restart Qt Creator

### "Password authentication failed"

**Giải pháp:**
- Kiểm tra lại password trong `elite_main_window.cpp`
- Đảm bảo password đúng với password PostgreSQL

### "No rooms displayed"

**Giải pháp:**
1. Mở pgAdmin
2. Query Tool
3. Chạy: `SELECT * FROM auction_rooms;`
4. Nếu empty → Import lại `data/data.sql`

## 📸 Screenshots Để Tham Khảo

### pgAdmin - Create Database:
```
Right-click Databases → Create → Database
Name: auction_db
Owner: postgres
```

### pgAdmin - Query Tool:
```
Tools → Query Tool
Paste SQL → Execute (F5)
Check Messages tab
```

### pgAdmin - Verify Data:
```
SELECT * FROM auction_rooms;
→ Should see 5 rows
```

## ✅ Checklist

- [ ] pgAdmin 4 đã mở
- [ ] Kết nối PostgreSQL thành công
- [ ] Database `auction_db` đã tạo
- [ ] Schema imported (7 tables)
- [ ] Data imported (5 rooms, 15+ items)
- [ ] Verify data OK
- [ ] Password đã sửa trong code
- [ ] libpq.dll đã copy (nếu cần)
- [ ] App build thành công
- [ ] App chạy và connect DB OK

## 🎉 Hoàn Thành!

Bây giờ bạn có thể demo app với:
- Database thực tế
- Hình ảnh đẹp
- UI mượt mà
- Tất cả tính năng hoạt động

**Thời gian:** 10-15 phút
**Độ khó:** ⭐ (Rất dễ)
**Công cụ:** Chỉ cần pgAdmin (GUI)

---

**Tip:** Bookmark trang pgAdmin để dễ quản lý database sau này!
