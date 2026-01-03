# Fix Build Error - "No rule to make target"

## Lỗi gặp phải

```
No rule to make target 'src/client/ui/elite_auction_main.cpp', 
needed by 'debug/elite_auction_main.o'. Stop.
```

## Nguyên nhân

File `auction_app.pro` đang tìm files ở `src/client/ui/` nhưng các Elite UI files vẫn đang ở root folder `auction_app/`.

## ✅ Đã sửa

### 1. Cập nhật auction_app.pro
- Đổi paths từ `src/client/ui/` về root `.`
- Cập nhật INCLUDEPATH
- Tất cả SOURCES và HEADERS giờ trỏ đúng vị trí

### 2. Thêm missing include
- Thêm `#include <QFont>` vào `elite_auction_main.cpp`

## 🚀 Cách build lại

### Trong Qt Creator:

1. **Clean project:**
   - Build → Clean All

2. **Run qmake:**
   - Build → Run qmake

3. **Rebuild:**
   - Build → Rebuild All (Ctrl + Shift + B)

4. **Run:**
   - Build → Run (Ctrl + R)

### Hoặc Command Line:

```bash
# Clean
del Makefile
del Makefile.Debug
del Makefile.Release
del .qmake.stash

# Generate Makefile
qmake auction_app.pro

# Build
mingw32-make

# Run
bin\AuctionHub.exe
```

### Hoặc dùng script:

```bash
build_ui.bat
run_ui.bat
```

## ✅ Checklist

- [x] Sửa auction_app.pro
- [x] Thêm #include <QFont>
- [ ] Clean project
- [ ] Run qmake
- [ ] Rebuild
- [ ] Test run

## 📝 Lưu ý

Nếu vẫn gặp lỗi:

1. **Kiểm tra tất cả files tồn tại:**
   - elite_auction_main.cpp
   - elite_login_window.h/cpp
   - elite_main_window.h/cpp
   - elite_auction_room.h/cpp
   - elite_account_window.h/cpp
   - elite_dialogs.h/cpp
   - elite_network_client.h/cpp

2. **Kiểm tra elite_resources.qrc:**
   - File phải tồn tại
   - Nếu không có, tạo file rỗng hoặc xóa dòng `RESOURCES += elite_resources.qrc` trong .pro

3. **Restart Qt Creator:**
   - Đóng Qt Creator
   - Xóa file `.pro.user`
   - Mở lại và configure lại

## 🎉 Kết quả

Sau khi fix, project sẽ build thành công và tạo file `bin/AuctionHub.exe`!
