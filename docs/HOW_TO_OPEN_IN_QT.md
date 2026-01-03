# 🎯 Cách Mở và Chạy trong Qt Creator

## 📋 Hướng Dẫn Chi Tiết (Có Hình Minh Họa)

### Bước 1: Mở Qt Creator
1. Tìm và mở **Qt Creator** trên máy tính
2. Nếu chưa cài, tải tại: https://www.qt.io/download

### Bước 2: Mở Project
1. Click menu **File** → **Open File or Project...**
2. Hoặc nhấn tổ hợp phím: **Ctrl+O** (Windows/Linux) hoặc **Cmd+O** (macOS)

### Bước 3: Chọn File .pro
1. Navigate đến thư mục: `auction_app/`
2. Chọn file: **`premium_modern_auction.pro`**
3. Click **Open**

### Bước 4: Configure Project
1. Qt Creator sẽ hiển thị màn hình "Configure Project"
2. Chọn **Kit** phù hợp (ví dụ: Desktop Qt 6.10.1 MinGW 64-bit)
3. Click **Configure Project**

### Bước 5: Build và Run
1. Click nút **Run** (▶️) màu xanh ở góc trái dưới
2. Hoặc nhấn **Ctrl+R** (Windows/Linux) hoặc **Cmd+R** (macOS)
3. Qt Creator sẽ tự động:
   - Build project
   - Compile code
   - Chạy ứng dụng

### Bước 6: Sử Dụng
1. Ứng dụng sẽ mở ra
2. Đăng nhập với username/password bất kỳ
3. Khám phá các tính năng!

## 🎮 Các Nút Quan Trọng trong Qt Creator

| Nút | Tên | Chức Năng | Phím Tắt |
|-----|-----|-----------|----------|
| ▶️ | Run | Chạy ứng dụng | Ctrl+R |
| 🔨 | Build | Build project | Ctrl+B |
| 🧹 | Clean | Xóa build files | - |
| 🛑 | Stop | Dừng ứng dụng | - |
| 🐛 | Debug | Chạy debug mode | F5 |

## 📂 Cấu Trúc Project trong Qt Creator

Sau khi mở, bạn sẽ thấy:

```
premium_modern_auction
├── premium_modern_auction.pro    ← Project file
└── Sources
    └── premium_modern_auction.cpp ← Code chính
```

## 🔧 Troubleshooting

### Lỗi: "No valid kits found"
**Giải pháp:**
1. Tools → Options → Kits
2. Click "Add" để thêm kit mới
3. Chọn compiler và Qt version

### Lỗi: "qmake not found"
**Giải pháp:**
1. Tools → Options → Kits → Qt Versions
2. Click "Add" và chọn qmake.exe
3. Thường ở: `C:\Qt\6.x\mingw_64\bin\qmake.exe`

### Lỗi build
**Giải pháp:**
1. Build → Clean All
2. Build → Rebuild All
3. Xem tab "Compile Output" để biết lỗi chi tiết

### Ứng dụng không chạy
**Giải pháp:**
1. Kiểm tra tab "Application Output"
2. Đảm bảo không có lỗi compile
3. Thử chạy ở Debug mode (F5)

## 💡 Tips

### Xem Code
- Click vào `premium_modern_auction.cpp` trong panel trái
- Code sẽ hiển thị ở panel giữa
- Có syntax highlighting và auto-complete

### Search trong Code
- **Ctrl+F**: Tìm trong file hiện tại
- **Ctrl+Shift+F**: Tìm trong toàn project

### Format Code
- **Ctrl+I**: Auto-indent
- **Ctrl+Shift+I**: Format toàn file

### Build Modes
- **Debug**: Chạy chậm hơn, có thể debug
- **Release**: Chạy nhanh hơn, tối ưu

Chọn mode ở góc trái dưới (Debug/Release)

## 🎯 Quick Actions

### Chạy Nhanh
```
1. Ctrl+O → Chọn premium_modern_auction.pro
2. Configure Project
3. Ctrl+R → Run
```

### Debug
```
1. F5 → Start Debugging
2. F9 → Set breakpoint
3. F10 → Step over
4. F11 → Step into
```

## 📚 Tài Liệu Qt Creator

- **Help → Qt Creator Manual**: Hướng dẫn đầy đủ
- **Help → About Qt Creator**: Thông tin version
- **Examples**: File → Examples → Xem ví dụ

## ✅ Checklist

Trước khi chạy, đảm bảo:
- ✅ Qt Creator đã cài đặt
- ✅ Qt 5.12+ hoặc 6.x đã cài
- ✅ Compiler (MinGW/MSVC/g++) đã cài
- ✅ File `premium_modern_auction.pro` tồn tại
- ✅ File `premium_modern_auction.cpp` tồn tại

## 🎉 Kết Quả Mong Đợi

Sau khi chạy thành công:
1. ✅ Cửa sổ ứng dụng mở ra
2. ✅ Màn hình đăng nhập hiển thị
3. ✅ UI đẹp, hiện đại
4. ✅ Không có lỗi trong console

## 📞 Cần Trợ Giúp?

Xem thêm:
- `PREMIUM_UI_README.md` - Hướng dẫn đầy đủ
- `HUONG_DAN_PREMIUM_UI.md` - Hướng dẫn tiếng Việt
- `QUICK_START_PREMIUM.md` - Hướng dẫn nhanh

---

**Chúc bạn thành công! 🏛️✨**

