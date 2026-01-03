# Quick Reference - Dialogs & Features

## 🎯 Các tính năng mới

### 1. Create Room Dialog
**Khi nào:** Click nút "+ Create Room"
**Làm gì:** Điền tên phòng, mô tả, chọn public/private
**Kết quả:** Tạo phòng đấu giá mới

### 2. Deposit Money Dialog
**Khi nào:** Click "💵 Deposit Money" trong Account page
**Làm gì:** Nhập số tiền hoặc chọn nhanh (1M, 5M, 10M)
**Kết quả:** Nạp tiền vào tài khoản, balance tăng

### 3. Withdraw Money Dialog
**Khi nào:** Click "💸 Withdraw Money" trong Account page
**Làm gì:** Nhập số tiền muốn rút
**Kết quả:** Rút tiền về ngân hàng, balance giảm

### 4. Bank Information Dialog
**Khi nào:** Click "🏦 Bank Information" trong Account page
**Làm gì:** Điền tên ngân hàng, số tài khoản, tên chủ tài khoản
**Kết quả:** Lưu thông tin ngân hàng để rút tiền

### 5. Chat Text Color Fixed
**Vấn đề:** Chữ chat màu trắng, không đọc được
**Đã sửa:** Chữ chat bây giờ màu đen (#1A202C)
**Kết quả:** Đọc chat dễ dàng hơn

---

## 🔨 Build & Run

```bash
cd auction_app
qmake elite_auction_app.pro
mingw32-make
release\elite_auction_app.exe
```

Hoặc:
```bash
build_elite_ui.bat
run_elite_ui.bat
```

---

## 📝 Files quan trọng

- `elite_dialogs.h/cpp` - Tất cả dialogs
- `elite_account_window.cpp` - Deposit/Withdraw/Bank
- `elite_main_window.cpp` - Create Room
- `elite_auction_room.cpp` - Chat color fix
- `DATABASE_INTEGRATION.md` - Hướng dẫn kết nối DB

---

## ✅ Checklist

- [x] Create Room dialog
- [x] Deposit Money dialog
- [x] Withdraw Money dialog
- [x] Bank Info dialog
- [x] Chat text color fix
- [x] Success messages
- [x] Input validation
- [x] Database guide
- [ ] Connect to actual database (optional)

---

**All done! Ready to use!** 🎉
