# 🏛️ Hướng Dẫn Premium Modern Auction UI

## 🚀 Chạy Nhanh Nhất (3 Bước)

### Cách 1: Dùng Qt Creator (Khuyến Nghị ⭐)

1. Mở **Qt Creator**
2. **File → Open File or Project** → Chọn `premium_modern_auction.pro`
3. Click nút **Run** (▶️)

**Xong! 🎉**

### Cách 2: Dùng Command Line

**Windows:**
```powershell
cd auction_app
.\build_premium_ui.bat
.\run_premium_ui.bat
```

**Linux/macOS:**
```bash
cd auction_app
chmod +x build_premium_ui.sh run_premium_ui.sh
./build_premium_ui.sh
./run_premium_ui.sh
```

## 🎮 Hướng Dẫn Sử Dụng

### 1️⃣ Đăng Nhập
- Username: nhập bất kỳ (ví dụ: `alice`)
- Password: nhập bất kỳ
- Click **🔐 Sign In**

### 2️⃣ Trang Chủ
- Xem số dư: **5,000,000 VND** (ban đầu)
- Xem các items đấu giá
- Click **View Auction** để vào phòng

### 3️⃣ Phòng Đấu Giá

**Cột Trái**: Hàng đợi items sắp tới

**Cột Giữa**: Item hiện tại
- Xem countdown timer (⏱️)
- Nhập giá đấu
- Dùng nút +10K, +50K, +100K
- Click **🔨 Place Bid** hoặc **⚡ Buy Now**

**Cột Phải**: Chat & Participants
- Xem người tham gia
- Chat với mọi người

### 4️⃣ Quản Lý Tài Khoản
- Click nút **Account**
- **Nạp tiền**: Click 100K, 500K, 1M, 5M hoặc nhập số tiền
- **Rút tiền**: Nhập số tiền và click Redeem
- Xem lịch sử đấu giá

## ✨ Tính Năng Đặc Biệt

### ⏱️ Countdown Timer
- Đếm ngược thời gian thực
- **Chuyển màu vàng** khi còn 30 giây
- **Reset về 30s** khi có bid mới trong 30s cuối

### 💬 Live Chat
- Gửi tin nhắn real-time
- Hiển thị username và thời gian
- Auto-scroll

### 💰 Quản Lý Tiền
- Nạp tiền nhanh
- Rút tiền với validation
- Cập nhật số dư ngay lập tức

## 🎨 Thiết Kế

### Màu Sắc
- 🔵 **Indigo**: Nút chính
- 🟢 **Green**: Thành công, tiền
- 🟡 **Amber**: Cảnh báo 30s
- 🔴 **Red**: Lỗi, nguy hiểm

### Phong Cách
- ✅ Minimalist - Tối giản
- ✅ Card-based - Dạng thẻ
- ✅ Modern - Hiện đại
- ✅ Professional - Chuyên nghiệp

## 📁 Files Quan Trọng

```
auction_app/
├── premium_modern_auction.cpp      ← Code chính
├── premium_modern_auction.pro      ← Qt project
├── build_premium_ui.bat            ← Build Windows
├── run_premium_ui.bat              ← Run Windows
├── PREMIUM_UI_README.md            ← Hướng dẫn đầy đủ
└── HUONG_DAN_PREMIUM_UI.md         ← File này
```

## 🐛 Lỗi Thường Gặp

### "qmake not found"
**Giải pháp**: Thêm Qt vào PATH
```powershell
# Windows
set PATH=C:\Qt\6.10.1\mingw_64\bin;%PATH%
```

### Build lỗi
**Giải pháp**:
1. Xóa thư mục `build`
2. Chạy lại build script

### Không chạy được
**Giải pháp**:
1. Kiểm tra Qt đã cài đúng chưa
2. Chạy từ Qt Creator để xem log

## 💡 Mẹo Hay

### Phím Tắt
- **Enter** ở password → Đăng nhập
- **Enter** ở chat → Gửi tin nhắn

### Thay Đổi Số Dư Ban Đầu
Mở `premium_modern_auction.cpp`, tìm dòng:
```cpp
int64_t _balance = 5000000  // Thay số này
```

### Thay Đổi Màu Sắc
Tìm namespace `DesignSystem`:
```cpp
const QString PRIMARY = "#4F46E5";  // Thay màu này
```

## 📊 Thống Kê

- **Code**: 2,150 dòng C++
- **Màn hình**: 4 (Welcome, Home, Auction, Account)
- **Components**: 50+ widgets
- **Tính năng**: 20+ features

## 🎯 Điểm Nổi Bật

✅ **Thiết kế hiện đại** - Minimalist, card-based  
✅ **Countdown timer** - Real-time với reset logic  
✅ **Live chat** - Gửi nhận tin nhắn tức thì  
✅ **3-column layout** - Queue | Current | Chat  
✅ **Account management** - Deposit, redeem, history  
✅ **Responsive** - Tự động điều chỉnh kích thước  
✅ **Smooth animations** - Hiệu ứng mượt mà  
✅ **Premium colors** - Bảng màu chuyên nghiệp  

## 🎓 Yêu Cầu

- **Qt**: 5.12+ hoặc 6.x
- **Compiler**: MinGW/MSVC (Windows), g++ (Linux), Clang (macOS)
- **RAM**: 2GB+
- **Màn hình**: 1200x800+

## 📞 Hỗ Trợ

Xem hướng dẫn đầy đủ: `PREMIUM_UI_README.md`

---

**Chúc bạn đấu giá vui vẻ! 🏛️✨**

Version 3.0 Premium Edition | HUST Auction Team

