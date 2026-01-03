# 🏛️ Premium Modern Auction Application

## 📋 Tổng Quan

Ứng dụng đấu giá trực tuyến **cao cấp, hiện đại, tối giản** được thiết kế theo tiêu chuẩn chuyên nghiệp với Qt/C++.

### ✨ Phiên Bản 3.0 - Premium Edition

Đây là phiên bản **hoàn chỉnh nhất** với thiết kế UI hiện đại, chuyên nghiệp và đầy đủ tính năng.

## 🎯 Đặc Điểm Nổi Bật

### 🎨 Thiết Kế Hiện Đại
- **Minimalist Design**: Giao diện tối giản, sạch sẽ với khoảng trắng hợp lý
- **Card-Based Layout**: Bố cục dạng thẻ với góc bo tròn và bóng đổ mềm mại
- **Premium Color Scheme**: 
  - 🔵 Indigo (#4F46E5) - Màu chính cho các hành động
  - 🟢 Green (#10B981) - Thành công, tiền, trạng thái tích cực
  - 🟡 Amber (#F59E0B) - Cảnh báo, 30 giây cuối
  - 🔴 Red (#EF4444) - Lỗi, nguy hiểm, bị trả giá cao hơn
- **Typography**: Inter/SF Pro với phân cấp rõ ràng
- **Smooth Animations**: Hiệu ứng chuyển động mượt mà

### 🚀 Tính Năng Đầy Đủ

#### 1. **Màn Hình Chào Mừng** (Authentication)
- ✅ Đăng nhập với username/password
- ✅ Đăng ký tài khoản mới
- ✅ Tab switching mượt mà
- ✅ Validation thời gian thực
- ✅ Hero section cao cấp với icon và slogan

#### 2. **Màn Hình Trang Chủ** (Home/Explore)
- ✅ Thanh navigation với logo và search
- ✅ Hiển thị user info và số dư
- ✅ Bộ lọc nhanh: All, Live, Upcoming
- ✅ Lưới items với card design
- ✅ Badge trạng thái: 🔴 LIVE, 📅 UPCOMING, SOLD
- ✅ Hiển thị giá hiện tại và countdown
- ✅ Nút "View Auction" để vào phòng

#### 3. **Màn Hình Phòng Đấu Giá** (Auction Room)
**Bố cục 3 cột chuyên nghiệp:**

**Cột Trái - Hàng Đợi:**
- ✅ Danh sách items sắp tới
- ✅ Hiển thị tên và giá khởi điểm
- ✅ Scroll được khi có nhiều items

**Cột Giữa - Item Hiện Tại:**
- ✅ Hình ảnh item lớn với gradient đẹp
- ✅ Tên và mô tả chi tiết
- ✅ **Đồng hồ đếm ngược thời gian thực**
  - Cập nhật mỗi giây
  - Chuyển màu vàng cam khi còn 30 giây
  - **Reset về 30s khi có bid mới trong 30s cuối**
- ✅ Hiển thị giá khởi điểm và giá hiện tại
- ✅ Ô nhập giá đấu với validation
- ✅ Nút tăng nhanh: +10K, +50K, +100K
- ✅ Nút "🔨 Place Bid" và "⚡ Buy Now"
- ✅ Kiểm tra minimum bid (+10,000 VND)

**Cột Phải - Chat & Participants:**
- ✅ Danh sách người tham gia
- ✅ Hiển thị host với icon 👑
- ✅ **Live chat thời gian thực**
  - Gửi tin nhắn
  - Hiển thị timestamp
  - Auto-scroll to bottom
  - Format đẹp với màu sắc

#### 4. **Màn Hình Quản Lý Tài Khoản** (Account Management)
- ✅ Thông tin profile (username, email)
- ✅ **Hiển thị số dư lớn, rõ ràng**
- ✅ **Nạp tiền (Deposit)**:
  - Nhập số tiền tùy ý
  - Nút nhanh: 100K, 500K, 1M, 5M
  - Cập nhật số dư ngay lập tức
- ✅ **Rút tiền (Redeem)**:
  - Kiểm tra số dư
  - Validation amount
- ✅ **Lịch sử đấu giá**:
  - Bảng hiển thị items đã đấu
  - Giá, trạng thái (Won/Outbid), ngày tháng

## 🚀 Cách Chạy Nhanh Nhất

### ✅ Phương Pháp 1: Qt Creator (Khuyến Nghị)

1. **Mở Qt Creator**
2. **File → Open File or Project**
3. Chọn file: `auction_app/premium_modern_auction.pro`
4. Click **Configure Project**
5. Click nút **Run** màu xanh (▶️)

**Xong! Ứng dụng sẽ tự động build và chạy! 🎉**

### ✅ Phương Pháp 2: Command Line

#### Windows
```powershell
cd auction_app
.\build_premium_ui.bat
.\run_premium_ui.bat
```

#### Linux/macOS
```bash
cd auction_app
chmod +x build_premium_ui.sh run_premium_ui.sh
./build_premium_ui.sh
./run_premium_ui.sh
```

## 🎮 Hướng Dẫn Sử Dụng Chi Tiết

### Bước 1: Đăng Nhập
1. Nhập **Username**: bất kỳ (ví dụ: "alice")
2. Nhập **Password**: bất kỳ (chế độ demo)
3. Click **🔐 Sign In**
4. Hoặc chuyển sang tab **Register** để tạo tài khoản mới

### Bước 2: Khám Phá Trang Chủ
- Xem thông tin user và số dư ở góc phải trên
- Dùng thanh search để tìm kiếm
- Click các nút filter: **All**, **🔴 Live**, **📅 Upcoming**
- Xem các item cards với:
  - Hình ảnh gradient đẹp
  - Badge trạng thái
  - Giá hiện tại
  - Countdown timer
- Click **View Auction** để vào phòng đấu giá

### Bước 3: Tham Gia Đấu Giá
**Trong phòng đấu giá:**

1. **Xem item hiện tại** ở cột giữa
2. **Theo dõi countdown** - chú ý khi còn 30 giây (màu vàng)
3. **Đặt giá:**
   - Nhập số tiền vào ô bid
   - Hoặc dùng nút +10K, +50K, +100K để tăng nhanh
   - Click **🔨 Place Bid**
4. **Mua ngay:** Click **⚡ Buy Now** để mua với giá Buy Now
5. **Chat:** Gõ tin nhắn và nhấn Enter hoặc Send
6. **Xem queue:** Cột trái hiển thị items sắp tới
7. **Xem participants:** Cột phải hiển thị người tham gia

**Lưu ý:**
- Giá đấu tối thiểu phải cao hơn giá hiện tại ít nhất 10,000 VND
- Khi bạn đặt giá trong 30 giây cuối, timer sẽ reset về 30 giây
- Bạn sẽ nhận thông báo khi đặt giá thành công

### Bước 4: Quản Lý Tài Khoản
1. Click nút **Account** ở trang chủ
2. **Xem số dư** hiện tại (ban đầu: 5,000,000 VND)
3. **Nạp tiền:**
   - Click nút nhanh (100K, 500K, 1M, 5M)
   - Hoặc nhập số tiền tùy ý
   - Click **💳 Deposit**
4. **Rút tiền:**
   - Nhập số tiền muốn rút
   - Click **💸 Redeem**
5. **Xem lịch sử** đấu giá ở bảng bên dưới

### Bước 5: Đăng Xuất
- Click nút **Logout** ở góc phải trên
- Xác nhận logout
- Quay về màn hình đăng nhập

## 📁 Cấu Trúc File

```
auction_app/
├── premium_modern_auction.cpp      ← Code chính (2100+ dòng)
├── premium_modern_auction.pro      ← Qt project file
├── build_premium_ui.bat            ← Build script Windows
├── build_premium_ui.sh             ← Build script Linux/macOS
├── run_premium_ui.bat              ← Run script Windows
├── run_premium_ui.sh               ← Run script Linux/macOS
├── PREMIUM_UI_README.md            ← File này
└── build/                          ← Thư mục build (tự tạo)
    └── premium_modern_auction.exe  ← Executable
```

## 🎨 Design System

### Màu Sắc
- **Primary (Indigo)**: #4F46E5 - Nút chính, links, highlights
- **Success (Green)**: #10B981 - Thành công, tiền, positive states
- **Warning (Amber)**: #F59E0B - Cảnh báo, 30s countdown
- **Danger (Red)**: #EF4444 - Lỗi, nguy hiểm, outbid
- **Background**: #FFFFFF - Nền trắng
- **Surface**: #F9FAFB - Nền xám nhạt
- **Border**: #E5E7EB - Viền
- **Text Primary**: #111827 - Chữ chính
- **Text Secondary**: #6B7280 - Chữ phụ

### Typography
- **Font Family**: Inter, SF Pro, Segoe UI
- **Font Sizes**:
  - Timer: 48px (monospace)
  - Heading: 36px
  - Title: 24px
  - Large: 18px
  - Base: 14px
  - Small: 12px

### Spacing
- XS: 4px
- SM: 8px
- MD: 16px (default)
- LG: 24px
- XL: 32px

### Border Radius
- SM: 6px
- MD: 8px
- LG: 12px
- XL: 16px
- Full: 9999px (pills)

## 🔧 Yêu Cầu Hệ Thống

### Phần Mềm
- **Qt**: 5.12+ hoặc 6.x (khuyến nghị 6.x)
- **Compiler**:
  - Windows: MinGW hoặc MSVC
  - Linux: g++ 7+
  - macOS: Clang (Xcode Command Line Tools)
- **qmake**: Đi kèm với Qt

### Phần Cứng
- **RAM**: 2GB+ (khuyến nghị 4GB+)
- **Màn hình**: 1200x800 trở lên (khuyến nghị 1400x900+)
- **CPU**: Dual-core trở lên

## 🐛 Xử Lý Lỗi

### Lỗi "qmake not found"
**Nguyên nhân**: Qt chưa được thêm vào PATH

**Giải pháp Windows**:
```powershell
set PATH=C:\Qt\6.10.1\mingw_64\bin;%PATH%
```

**Giải pháp Linux/macOS**:
```bash
export PATH=/usr/local/Qt-6.x/bin:$PATH
```

### Lỗi build
**Giải pháp**:
1. Clean build directory: `rm -rf build/*`
2. Chạy lại qmake: `qmake premium_modern_auction.pro`
3. Build lại: `make` hoặc `mingw32-make`

### Ứng dụng không chạy
**Kiểm tra**:
1. File executable có tồn tại không?
2. Các DLL của Qt có trong PATH không?
3. Chạy từ Qt Creator để xem log chi tiết

### Lỗi "cannot find -lQt6Widgets"
**Giải pháp**: Cài đặt Qt development packages
```bash
# Ubuntu/Debian
sudo apt-get install qt6-base-dev

# Fedora
sudo dnf install qt6-qtbase-devel
```

## 💡 Mẹo & Thủ Thuật

### Phím Tắt
- **Enter** ở ô password → Đăng nhập
- **Enter** ở ô chat → Gửi tin nhắn
- **Enter** ở ô bid → Đặt giá (nếu focus)

### Tùy Chỉnh Màu Sắc
Mở file `premium_modern_auction.cpp`, tìm namespace `DesignSystem` (dòng ~70):

```cpp
const QString PRIMARY = "#4F46E5";  // Thay đổi màu chính
const QString SUCCESS = "#10B981";  // Thay đổi màu success
// ... các màu khác
```

### Thay Đổi Số Dư Ban Đầu
Tìm class `UserAccount` (dòng ~520):

```cpp
UserAccount(QString _user = "demo_user", QString _email = "demo@auction.com",
            int64_t _balance = 5000000)  // Thay đổi số này
```

### Thay Đổi Thời Gian Countdown
Tìm `loadDemoData()` trong `AuctionRoomScreen` (dòng ~1550):

```cpp
currentItem = AuctionItem(1, "🏺 Antique Vase",
                         "...",
                         800000, 2000000,
                         300,  // Thay đổi số giây này
                         "LIVE");
```

## 🎯 Tính Năng Nổi Bật

### ⏱️ Countdown Timer với Reset Logic
- Đếm ngược từ thời gian ban đầu
- Cập nhật mỗi giây
- **Chuyển màu vàng cam** khi còn 30 giây
- **Tự động reset về 30 giây** khi có bid mới trong 30s cuối
- Dừng khi hết giờ hoặc Buy Now

### 💬 Live Chat System
- Gửi tin nhắn real-time
- Hiển thị username và timestamp
- Format HTML đẹp với màu sắc
- Auto-scroll to bottom
- Lưu lịch sử chat

### 💰 Account Management
- Hiển thị số dư lớn, rõ ràng
- Nạp tiền với validation
- Rút tiền với kiểm tra số dư
- Lịch sử đấu giá đầy đủ
- Cập nhật real-time

### 🎨 Modern UI Components
- Card-based layout với shadow
- Badge system (LIVE, UPCOMING, SOLD)
- Gradient backgrounds
- Smooth hover effects
- Responsive design
- Toast notifications

## 📊 Thống Kê Code

- **Tổng số dòng**: ~2,150 dòng
- **Ngôn ngữ**: C++ với Qt Framework
- **Số màn hình**: 4 (Welcome, Home, Auction Room, Account)
- **Số components**: 50+ widgets
- **Design tokens**: 40+ (colors, spacing, fonts)

## 🔄 Chế Độ Demo

Ứng dụng hiện đang chạy ở **chế độ demo** với:
- ✅ Đăng nhập với bất kỳ username/password
- ✅ Số dư ban đầu: 5,000,000 VND
- ✅ 6 items mẫu (3 LIVE, 2 UPCOMING, 1 SOLD)
- ✅ 5 participants mẫu
- ✅ Chat messages mẫu
- ✅ Lịch sử đấu giá mẫu

**Để kết nối với server thật:**
1. Tích hợp `NetworkClient` từ `src/client/network_client.h`
2. Thay thế dữ liệu demo bằng API calls
3. Implement WebSocket cho chat real-time
4. Thêm authentication với server

## 🎓 Kiến Trúc Code

### Design Patterns
- **MVC Pattern**: Tách biệt UI và logic
- **Observer Pattern**: Signals & Slots của Qt
- **Singleton Pattern**: DesignSystem namespace
- **Factory Pattern**: Utils::createCard(), createButton()

### Code Organization
```
premium_modern_auction.cpp
├── DesignSystem (namespace)      ← Colors, fonts, styles
├── Utils (namespace)             ← Helper functions
├── Data Models                   ← AuctionItem, ChatMessage, UserAccount
├── WelcomeScreen (class)         ← Authentication UI
├── HomeScreen (class)            ← Explore auctions UI
├── AuctionRoomScreen (class)     ← Live bidding UI
├── AccountScreen (class)         ← Account management UI
├── PremiumAuctionApp (class)     ← Main window & navigation
└── main()                        ← Entry point
```

## 🚀 Roadmap Tương Lai

### Version 3.1 (Planned)
- [ ] Kết nối với server thật
- [ ] WebSocket cho real-time updates
- [ ] Notifications system
- [ ] Search functionality
- [ ] Filter by category, price range
- [ ] User profile editing

### Version 3.2 (Planned)
- [ ] Image upload cho items
- [ ] Multiple auction rooms
- [ ] Private rooms với password
- [ ] Admin panel
- [ ] Statistics dashboard

### Version 4.0 (Future)
- [ ] Mobile responsive (QML)
- [ ] Dark mode
- [ ] Multi-language support
- [ ] Payment integration
- [ ] Email notifications

## 📝 License

MIT License - Free to use and modify

## 👥 Credits

- **Design**: Inspired by modern web auction platforms
- **Framework**: Qt Framework (The Qt Company)
- **Icons**: Unicode Emoji
- **Fonts**: Inter, SF Pro (system fonts)

## 📞 Support

Nếu gặp vấn đề:
1. Kiểm tra phần "Xử Lý Lỗi" ở trên
2. Xem log trong Qt Creator
3. Kiểm tra Qt version: `qmake -v`
4. Đảm bảo compiler hoạt động: `g++ --version` hoặc `cl`

## 🎉 Kết Luận

Đây là phiên bản **Premium Modern Auction UI** hoàn chỉnh với:
- ✅ Thiết kế hiện đại, minimalist, chuyên nghiệp
- ✅ Đầy đủ tính năng: Login, Explore, Bidding, Account
- ✅ Real-time countdown với reset logic
- ✅ Live chat system
- ✅ Account management với deposit/redeem
- ✅ Responsive three-column layout
- ✅ Premium color scheme và typography
- ✅ Smooth animations và transitions
- ✅ Code sạch, có tổ chức, dễ maintain

**Chúc bạn có trải nghiệm đấu giá tuyệt vời! 🏛️✨**

---

**Version**: 3.0 Premium Edition
**Date**: December 2024
**Author**: HUST Auction Team
**File**: premium_modern_auction.cpp (2,150 lines)
**Project**: premium_modern_auction.pro

