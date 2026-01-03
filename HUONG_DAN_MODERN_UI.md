# 🎨 Hướng Dẫn Giao Diện Modern Auction UI

## 📋 Tổng Quan

Đây là giao diện **hiện đại, tối giản, chuyên nghiệp** cho ứng dụng đấu giá trực tuyến, được thiết kế theo tiêu chuẩn cao cấp với Qt/C++.

## ✨ Đặc Điểm Nổi Bật

### 🎯 Thiết Kế
- **Minimalist**: Giao diện tối giản, chuyên nghiệp
- **Card-based**: Bố cục dạng thẻ với góc bo tròn
- **Modern**: Màu sắc hiện đại, bóng đổ mềm mại
- **Premium**: Cảm giác cao cấp, đáng tin cậy

### 🎨 Hệ Thống Màu Sắc
- **Indigo (#4F46E5)**: Màu chính - nút bấm, hành động
- **Xanh lá (#10B981)**: Thành công, tiền, trạng thái tích cực
- **Vàng cam (#F59E0B)**: Cảnh báo, 30 giây cuối
- **Đỏ (#EF4444)**: Lỗi, nguy hiểm, bị trả giá cao hơn

### 📱 Các Màn Hình

#### 1. **Màn Hình Chào Mừng** (Đăng Nhập/Đăng Ký)
- Form đăng nhập và đăng ký
- Chuyển đổi tab dễ dàng
- Xác thực thời gian thực
- Thiết kế hero section cao cấp

#### 2. **Màn Hình Trang Chủ** (Khám Phá)
- Thanh tìm kiếm với bộ lọc nhanh
- Lưới các phòng đấu giá nổi bật
- Thẻ item với badge trạng thái (LIVE, UPCOMING, SOLD)
- Hiển thị thông tin user và số dư

#### 3. **Màn Hình Phòng Đấu Giá** (Bố Cục 3 Cột)
- **Cột Trái**: Hàng đợi items sắp tới
- **Cột Giữa**: 
  - Item hiện tại với hình ảnh lớn
  - Đồng hồ đếm ngược thời gian thực
  - Hiển thị giá hiện tại
  - Nhập giá đấu với nút tăng nhanh
  - Nút "Đặt Giá" và "Mua Ngay"
- **Cột Phải**:
  - Danh sách người tham gia
  - Chat trực tiếp

#### 4. **Màn Hình Quản Lý Tài Khoản**
- Thông tin hồ sơ
- Số dư ảo với hiển thị lớn, rõ ràng
- Nạp tiền với các nút số tiền nhanh
- Rút tiền
- Bảng lịch sử đấu giá

## 🚀 Cách Chạy Nhanh Nhất

### Sử Dụng Qt Creator (Khuyến Nghị)

1. **Mở Qt Creator**
2. **File → Open File or Project**
3. Chọn file: `auction_app/modern_auction_app.pro`
4. Click **Configure Project**
5. Click nút **Run** màu xanh (▶️)

**Xong! Ứng dụng sẽ tự động build và chạy! 🎉**

### Sử Dụng Command Line

#### Windows
```powershell
cd auction_app
.\build_modern_ui.bat
```

#### Linux/macOS
```bash
cd auction_app
chmod +x build_modern_ui.sh
./build_modern_ui.sh
```

## 🎮 Hướng Dẫn Sử Dụng

### Bước 1: Đăng Nhập
- **Username**: Nhập bất kỳ (ví dụ: "alice")
- **Password**: Nhập bất kỳ (chế độ demo)
- Click **🔐 Sign In**

### Bước 2: Khám Phá Đấu Giá
- Xem các items nổi bật
- Click vào thẻ item để vào phòng đấu giá
- Dùng bộ lọc: All, Live, Upcoming

### Bước 3: Tham Gia Phòng Đấu Giá
- Xem item hiện tại và đồng hồ đếm ngược
- Nhập số tiền đấu giá hoặc dùng nút nhanh (+10K, +50K, +100K)
- Click **🔨 Place Bid** để đặt giá
- Hoặc click **⚡ Buy Now** để mua ngay
- Chat với người tham gia khác

### Bước 4: Quản Lý Tài Khoản
- Click nút **Account** ở thanh trên
- Xem số dư: 5,000,000 VND (ban đầu)
- Nạp tiền bằng các nút nhanh
- Xem lịch sử đấu giá

## 🎯 Tính Năng Đặc Biệt

### ⏱️ Đồng Hồ Đếm Ngược
- Đếm ngược thời gian thực
- Khi còn **30 giây**, chuyển sang màu **vàng cam** (cảnh báo)
- Trong app thật, giá mới sẽ reset timer về 30s

### 💬 Chat Trực Tiếp
- Gõ tin nhắn trong ô chat
- Nhấn Enter hoặc click Send
- Xem tin nhắn hiện lên ngay lập tức

### 💰 Tăng Giá Nhanh
- Click nút **+10K**, **+50K**, hoặc **+100K**
- Số tiền tự động cộng vào ô đấu giá
- Đấu giá nhanh và dễ dàng!

### 🎯 Badge Trạng Thái
- **● LIVE** (Đỏ): Đấu giá đang diễn ra
- **UPCOMING** (Xanh): Sắp bắt đầu
- **SOLD** (Xám): Đã kết thúc

## 📁 Cấu Trúc File

```
auction_app/
├── modern_auction_app.cpp      ← Toàn bộ code (1 file duy nhất!)
├── modern_auction_app.pro      ← File project Qt
├── MODERN_UI_README.md         ← Tài liệu đầy đủ (English)
├── UI_DESIGN_GUIDE.md          ← Hướng dẫn thiết kế
├── QUICK_START_MODERN_UI.md    ← Hướng dẫn nhanh (English)
├── HUONG_DAN_MODERN_UI.md      ← File này (Tiếng Việt)
├── build_modern_ui.bat         ← Script build Windows
├── build_modern_ui.sh          ← Script build Linux/macOS
└── build/                      ← Thư mục build (tự tạo)
    └── modern_auction_app.exe  ← File chạy
```

## 🐛 Xử Lý Lỗi

### Lỗi "qmake not found"
**Giải pháp**: Thêm Qt vào PATH
```powershell
# Windows
set PATH=C:\Qt\6.10.1\mingw_64\bin;%PATH%
```

### Lỗi build
**Giải pháp**:
1. Clean build: **Build → Clean All**
2. Rebuild: **Build → Rebuild All**
3. Kiểm tra output trong tab "Compile Output"

### Ứng dụng không chạy
**Giải pháp**:
1. Kiểm tra phiên bản Qt (cần 5.12+ hoặc 6.x)
2. Chạy từ Qt Creator để xem lỗi rõ hơn
3. Kiểm tra các file DLL của Qt

## 💡 Mẹo Hay

### Thay Đổi Kích Thước
- Kéo viền cửa sổ để thay đổi kích thước
- Tối thiểu khuyến nghị: 1200x800
- Trải nghiệm tốt nhất: 1400x900 trở lên

### Phím Tắt
- **Enter** ở ô password → Đăng nhập
- **Enter** ở ô chat → Gửi tin nhắn
- **Ctrl+Q** → Thoát ứng dụng

### Chế Độ Demo
- Tất cả dữ liệu đều giả lập (không cần server thật)
- Đăng nhập với bất kỳ username/password nào
- Số dư ban đầu: 5,000,000 VND
- Có sẵn items mẫu và tin nhắn chat

## 🎨 Tùy Chỉnh Thiết Kế

Để thay đổi màu sắc, khoảng cách, font chữ:

1. Mở file `modern_auction_app.cpp`
2. Tìm namespace `DesignSystem` (dòng ~35)
3. Thay đổi các giá trị:

```cpp
const QString PRIMARY = "#4F46E5";  // Màu chính
const QString SUCCESS = "#10B981";  // Màu thành công
const int SPACING_MD = 16;          // Khoảng cách
const int RADIUS_LG = 12;           // Bo góc
```

## 📚 Tài Liệu

- **README đầy đủ**: `MODERN_UI_README.md` (English)
- **Hướng dẫn thiết kế**: `UI_DESIGN_GUIDE.md` (English)
- **Hướng dẫn nhanh**: `QUICK_START_MODERN_UI.md` (English)
- **Qt Docs**: https://doc.qt.io/

## 🎯 Kết Nối Với Server Thật

Để kết nối UI này với server đấu giá thật:

1. Thêm tích hợp network client
2. Thay dữ liệu demo bằng API calls thật
3. Implement WebSocket cho chat real-time
4. Thêm xác thực với server

Xem `src/client/network_client.h` trong project chính để tham khảo.

## ✨ Điểm Nổi Bật

### 🎨 Thiết Kế Hiện Đại
- Giao diện tối giản, chuyên nghiệp
- Bố cục dạng thẻ
- Bóng đổ mềm và góc bo tròn
- Bảng màu cao cấp

### ⚡ Phần Tử Thời Gian Thực
- Đồng hồ đếm ngược trực tiếp
- Tin nhắn chat tức thì
- Cập nhật số dư động
- Badge trạng thái

### 🎯 Thân Thiện Người Dùng
- Điều hướng rõ ràng
- Nút hành động nhanh
- Bố cục trực quan
- Thông báo hữu ích

---

**Chúc bạn có trải nghiệm đấu giá cao cấp! 🏛️✨**

Cần trợ giúp? Xem tài liệu đầy đủ trong `MODERN_UI_README.md`

