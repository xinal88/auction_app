# Hướng dẫn chạy Elite Auction UI trên Qt Creator

## Bước 1: Cài đặt Qt Creator

### Download Qt
1. Truy cập: https://www.qt.io/download-open-source
2. Download Qt Online Installer
3. Chạy installer

### Cài đặt Components
Trong Qt Installer, chọn:
- ✅ Qt 5.15.2 (hoặc cao hơn)
- ✅ MinGW 8.1.0 64-bit (hoặc MSVC 2019)
- ✅ Qt Creator
- ✅ Qt Charts (optional)

### Kiểm tra cài đặt
1. Mở Qt Creator
2. Menu: Help → About Qt Creator
3. Kiểm tra version Qt Creator và Qt

## Bước 2: Mở Project trong Qt Creator

### Cách 1: Từ Qt Creator
1. **Mở Qt Creator**
2. Click **"Open Project"** hoặc File → Open File or Project
3. Navigate đến thư mục: `auction_app/`
4. Chọn file: **`elite_auction_app.pro`**
5. Click **"Open"**

### Cách 2: Double-click file .pro
1. Mở Windows Explorer
2. Navigate đến `auction_app/`
3. Double-click file **`elite_auction_app.pro`**
4. Qt Creator sẽ tự động mở

## Bước 3: Configure Project

Sau khi mở project, Qt Creator sẽ hiển thị màn hình "Configure Project":

### Chọn Kit
1. Chọn **Desktop Qt 5.15.2 MinGW 64-bit** (hoặc version bạn đã cài)
2. Đảm bảo có dấu ✅ bên cạnh kit
3. Click **"Configure Project"**

### Nếu không thấy Kit
1. Menu: Tools → Options
2. Chọn tab **Kits**
3. Click **"Add"** để thêm kit mới
4. Configure:
   - **Name**: Desktop Qt 5.15.2 MinGW 64-bit
   - **Compiler**: MinGW (C và C++)
   - **Qt version**: Qt 5.15.2
   - **CMake Tool**: (auto-detect)
5. Click **"OK"**

## Bước 4: Kiểm tra Project Structure

Trong Qt Creator, bạn sẽ thấy cấu trúc project:

```
elite_auction_app
├── elite_auction_app.pro          ← Project file
├── Headers
│   ├── elite_login_window.h
│   ├── elite_main_window.h
│   ├── elite_auction_room.h
│   ├── elite_account_window.h
│   └── elite_network_client.h
├── Sources
│   ├── elite_auction_main.cpp
│   ├── elite_login_window.cpp
│   ├── elite_main_window.cpp
│   ├── elite_auction_room.cpp
│   ├── elite_account_window.cpp
│   └── elite_network_client.cpp
└── Resources
    └── elite_resources.qrc
```

## Bước 5: Build Project

### Build từ Menu
1. Menu: **Build → Build Project "elite_auction_app"**
2. Hoặc nhấn: **Ctrl + B**
3. Hoặc click icon 🔨 (Build) trên toolbar

### Chọn Build Mode
Ở góc dưới bên trái, chọn:
- **Debug**: Để debug (chậm hơn, có debug info)
- **Release**: Để chạy nhanh (khuyến nghị)

### Theo dõi Build Process
1. Xem tab **"Compile Output"** ở dưới
2. Đợi đến khi thấy: **"Build succeeded"**
3. Nếu có lỗi, xem phần Troubleshooting bên dưới

## Bước 6: Run Application

### Chạy từ Qt Creator
1. Click nút **▶ Run** (màu xanh lá) trên toolbar
2. Hoặc nhấn: **Ctrl + R**
3. Hoặc Menu: **Build → Run**

### Ứng dụng sẽ khởi động
- Màn hình **Welcome Back** (Login) sẽ hiển thị
- Giao diện minimalist, professional
- Sẵn sàng để sử dụng!

## Bước 7: Sử dụng Application

### Login Screen
1. Nhập email (bất kỳ)
2. Nhập password (bất kỳ)
3. Click **"Sign In"**

### Main Window
- **Explore**: Xem các phòng đấu giá
- **Rooms**: Phòng của bạn
- **Account**: Quản lý tài khoản
- Click vào room card để vào phòng đấu giá

### Auction Room
- **Left panel**: Upcoming items
- **Center panel**: Current item, timer, bidding
- **Right panel**: Chat & participants
- Click **"← Leave Room"** để quay lại

## Troubleshooting

### Lỗi: "Cannot find file: elite_auction_app.pro"
**Giải pháp:**
1. Đảm bảo bạn đang ở đúng thư mục `auction_app/`
2. File .pro phải tồn tại
3. Thử mở lại Qt Creator

### Lỗi: "No valid kits found"
**Giải pháp:**
1. Menu: Tools → Options → Kits
2. Click **"Auto-detect"**
3. Hoặc thêm kit manually (xem Bước 3)

### Lỗi Build: "qmake: command not found"
**Giải pháp:**
1. Kiểm tra Qt đã cài đúng
2. Menu: Tools → Options → Kits → Qt Versions
3. Click **"Add"** và browse đến qmake.exe:
   - Ví dụ: `C:\Qt\5.15.2\mingw81_64\bin\qmake.exe`

### Lỗi Build: "mingw32-make: command not found"
**Giải pháp:**
1. Kiểm tra MinGW đã cài
2. Menu: Tools → Options → Kits → Compilers
3. Click **"Auto-detect"**
4. Hoặc add manually:
   - C: `C:\Qt\Tools\mingw810_64\bin\gcc.exe`
   - C++: `C:\Qt\Tools\mingw810_64\bin\g++.exe`

### Lỗi: "Cannot find -lQt5Widgets"
**Giải pháp:**
1. Kiểm tra Qt version trong .pro file
2. Đảm bảo Qt 5.15+ đã cài
3. Clean và rebuild:
   - Menu: Build → Clean All
   - Menu: Build → Rebuild All

### Lỗi: "undefined reference to vtable"
**Giải pháp:**
1. Menu: Build → **Clean All**
2. Menu: Build → **Run qmake**
3. Menu: Build → **Rebuild All**

### Application không chạy
**Giải pháp:**
1. Kiểm tra Build Mode (Debug hoặc Release)
2. Xem tab **"Application Output"** để xem lỗi
3. Đảm bảo không có process cũ đang chạy:
   - Task Manager → End process

### UI không hiển thị đúng
**Giải pháp:**
1. Kiểm tra Qt version >= 5.15
2. Thử resize window
3. Restart application

### Lỗi: "This application failed to start because no Qt platform plugin could be initialized"
**Giải pháp:**
1. Copy Qt DLLs vào thư mục executable:
   ```
   Qt5Core.dll
   Qt5Gui.dll
   Qt5Widgets.dll
   Qt5Network.dll
   ```
2. Hoặc chạy từ Qt Creator (khuyến nghị)

## Debug Application

### Chạy với Debugger
1. Click nút **🐛 Debug** (bên cạnh Run)
2. Hoặc nhấn: **F5**
3. Application sẽ chạy trong debug mode

### Set Breakpoints
1. Click vào số dòng trong code editor
2. Dấu 🔴 đỏ sẽ xuất hiện
3. Chạy debug, app sẽ dừng tại breakpoint

### Debug Controls
- **F5**: Continue
- **F10**: Step Over
- **F11**: Step Into
- **Shift+F11**: Step Out
- **Shift+F5**: Stop Debugging

## Tips & Tricks

### 1. Auto-format Code
- Chọn code
- Nhấn: **Ctrl + I** (indent)
- Hoặc: **Ctrl + Shift + I** (format)

### 2. Quick Search
- **Ctrl + K**: Open Locator
- Gõ tên file để mở nhanh
- Gõ tên function để jump đến

### 3. Build Shortcuts
- **Ctrl + B**: Build
- **Ctrl + R**: Run
- **Ctrl + Shift + B**: Rebuild All

### 4. View Shortcuts
- **F4**: Switch Header/Source
- **Ctrl + Tab**: Switch files
- **Alt + 0**: Show/Hide sidebar

### 5. Code Navigation
- **F2**: Follow symbol (jump to definition)
- **Ctrl + Click**: Jump to definition
- **Alt + Left**: Go back
- **Alt + Right**: Go forward

## Customize Qt Creator

### Theme
1. Menu: Tools → Options → Environment
2. Tab: **Interface**
3. Chọn Theme: Dark hoặc Light

### Font Size
1. Menu: Tools → Options → Text Editor
2. Tab: **Font & Colors**
3. Adjust font size

### Editor Settings
1. Menu: Tools → Options → Text Editor
2. Tab: **Behavior**
3. Configure:
   - Tab size: 4
   - Indent: Spaces
   - Auto-indent: ✅

## Export Executable

### Tạo Standalone Executable
1. Build ở mode **Release**
2. Tìm file .exe trong:
   - `build-elite_auction_app-Desktop_Qt_5_15_2_MinGW_64_bit-Release/release/`
3. Copy file .exe ra thư mục mới
4. Sử dụng **windeployqt** để copy DLLs:

```bash
cd path/to/your/exe
C:\Qt\5.15.2\mingw81_64\bin\windeployqt.exe elite_auction_app.exe
```

5. Bây giờ bạn có thể chạy .exe trên máy khác!

## Project Settings

### Thay đổi Build Directory
1. Click vào **Projects** (sidebar trái)
2. Tab: **Build**
3. Thay đổi **Build directory**

### Add Defines
Trong file .pro, thêm:
```qmake
DEFINES += MY_DEFINE
```

### Add Libraries
Trong file .pro, thêm:
```qmake
LIBS += -L/path/to/lib -lmylib
```

## Keyboard Shortcuts Summary

| Action | Shortcut |
|--------|----------|
| Build | Ctrl + B |
| Run | Ctrl + R |
| Debug | F5 |
| Stop | Shift + F5 |
| Switch Header/Source | F4 |
| Find | Ctrl + F |
| Find in Files | Ctrl + Shift + F |
| Go to Line | Ctrl + L |
| Comment | Ctrl + / |
| Save All | Ctrl + Shift + S |

## Kết luận

Bây giờ bạn đã biết cách:
✅ Mở project trong Qt Creator
✅ Configure và build project
✅ Run và debug application
✅ Troubleshoot các lỗi thường gặp
✅ Sử dụng shortcuts hiệu quả

**Chúc bạn code vui vẻ với Elite Auction UI!** 🚀

---

## Liên hệ & Hỗ trợ

Nếu gặp vấn đề:
1. Đọc phần Troubleshooting
2. Check Qt documentation: https://doc.qt.io/
3. Qt Forum: https://forum.qt.io/

## Resources

- Qt Documentation: https://doc.qt.io/qt-5/
- Qt Examples: https://doc.qt.io/qt-5/qtexamples.html
- Qt Widgets: https://doc.qt.io/qt-5/qtwidgets-index.html
