# 🚀 BẮT ĐẦU TẠI ĐÂY - WINDOWS

## ⚡ Cách Dễ Nhất (Khuyến Nghị)

### 📖 Dùng pgAdmin (GUI - Không Cần Command Line)

**→ Đọc file: `SETUP_USING_PGADMIN.md`**

Chỉ cần:
1. Mở pgAdmin 4
2. Tạo database
3. Copy-paste SQL
4. Sửa password trong code
5. Build & Run

**Thời gian:** 10 phút
**Độ khó:** ⭐ (Rất dễ)

---

## 🖥️ Cách Dùng Command Line (Nâng Cao)

### 1️⃣ Tìm PostgreSQL
```bash
find_postgresql.bat
```

### 2️⃣ Setup Database
```bash
setup_db_simple.bat
```
Nhập path và password khi được hỏi.

### 3️⃣ Cấu Hình & Chạy

**A. Sửa password:**
- Mở file: `elite_main_window.cpp`
- Dòng ~20: Thay `""` bằng password của bạn

**B. Build & Run:**
```bash
build_elite_ui.bat
run_elite_ui.bat
```

---

## 📚 Tài Liệu Chi Tiết

### Khuyến Nghị (Dễ Nhất):
- **`SETUP_USING_PGADMIN.md`** ⭐⭐⭐ - Dùng GUI, rất dễ!

### Nếu Muốn Chi Tiết:
- `SETUP_WINDOWS_COMPLETE.md` - Hướng dẫn đầy đủ
- `QUICK_DEMO_GUIDE.md` - Hướng dẫn demo

---

## 🐛 Lỗi Thường Gặp

### "PostgreSQL not found"
→ Cài PostgreSQL: https://www.postgresql.org/download/windows/

### "QPSQL driver not loaded"
→ Copy `libpq.dll` từ PostgreSQL bin vào Qt bin
→ Chi tiết trong `SETUP_USING_PGADMIN.md`

### "Password authentication failed"
→ Kiểm tra password trong `elite_main_window.cpp` dòng 20

### "Database does not exist"
→ Làm theo `SETUP_USING_PGADMIN.md` để tạo database

---

## ✅ Checklist

- [ ] PostgreSQL đã cài (có pgAdmin 4)
- [ ] Database đã tạo qua pgAdmin
- [ ] Schema & data đã import
- [ ] Password đã sửa trong code
- [ ] App build thành công
- [ ] App chạy và thấy "Database connected successfully!"

---

## 🎯 Kết Quả Mong Đợi

Khi chạy thành công:
- ✅ 5 auction rooms với hình ảnh đẹp
- ✅ Filter Live/Upcoming hoạt động
- ✅ Click vào room → Xem items
- ✅ Buy Now → Popup confirmation
- ✅ Balance hiển thị từ database

---

## 🎓 Lựa Chọn Của Bạn

### Bạn Thích GUI? (Dễ)
→ Đọc: **`SETUP_USING_PGADMIN.md`**

### Bạn Thích Command Line? (Nâng cao)
→ Dùng: `setup_db_simple.bat`

### Bạn Muốn Hiểu Sâu? (Chi tiết)
→ Đọc: `SETUP_WINDOWS_COMPLETE.md`

---

**Khuyến nghị:** Dùng pgAdmin (GUI) - Dễ nhất! ⭐

**Thời gian:** 10-15 phút
**Độ khó:** ⭐ (Rất dễ với pgAdmin)

🎉 **Let's go!**
