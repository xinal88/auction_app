# Hướng dẫn sử dụng Elite Auction UI

## Giới thiệu

Elite Auction UI là giao diện đấu giá trực tuyến hiện đại với thiết kế minimalist, chuyên nghiệp. Ứng dụng được thiết kế theo các nguyên tắc UX/UI cao cấp với focus vào trải nghiệm người dùng.

## Cài đặt

### Yêu cầu hệ thống
- Windows 10 trở lên
- Qt 5.15 hoặc cao hơn
- MinGW hoặc MSVC compiler

### Cài đặt Qt
1. Download Qt từ: https://www.qt.io/download
2. Cài đặt Qt với MinGW compiler
3. Thêm Qt bin vào PATH:
   - Ví dụ: `C:\Qt\5.15.2\mingw81_64\bin`
   - Ví dụ: `C:\Qt\Tools\mingw810_64\bin`

## Build ứng dụng

### Cách 1: Sử dụng script tự động (Khuyến nghị)

```bash
cd auction_app
build_elite_ui.bat
```

Script sẽ tự động:
1. Clean build cũ
2. Generate Makefile từ .pro file
3. Compile source code
4. Tạo executable trong thư mục `release/`

### Cách 2: Build thủ công

```bash
cd auction_app
qmake elite_auction_app.pro
mingw32-make
```

## Chạy ứng dụng

### Cách 1: Sử dụng script

```bash
run_elite_ui.bat
```

### Cách 2: Chạy trực tiếp

```bash
release\elite_auction_app.exe
```

## Hướng dẫn sử dụng

### 1. Màn hình đăng nhập

Khi khởi động ứng dụng, bạn sẽ thấy màn hình Welcome:

- **Email**: Nhập email của bạn
- **Password**: Nhập mật khẩu
- **Sign In**: Click để đăng nhập
- **Sign up**: Link để đăng ký tài khoản mới

*Lưu ý: Trong phiên bản demo, bạn có thể click Sign In trực tiếp để vào ứng dụng.*

### 2. Trang chủ - Explore

Sau khi đăng nhập, bạn sẽ thấy trang Explore với:

#### Navigation Bar (Thanh điều hướng)
- **🔨 AuctionHub**: Logo và tên ứng dụng
- **Explore**: Khám phá các phòng đấu giá
- **Rooms**: Phòng đấu giá của bạn
- **Account**: Quản lý tài khoản
- **💰 Balance**: Hiển thị số dư hiện tại
- **+ Create Room**: Tạo phòng đấu giá mới

#### Tìm kiếm và lọc
- **Search bar**: Tìm kiếm phòng đấu giá theo tên
- **🔴 Live**: Lọc các phòng đang diễn ra
- **📅 Upcoming**: Lọc các phòng sắp diễn ra

#### Danh sách phòng đấu giá
Mỗi card hiển thị:
- **Hình ảnh**: Preview của phòng
- **Status badge**: LIVE (đỏ) hoặc UPCOMING (vàng)
- **Tên phòng**: Tiêu đề phòng đấu giá
- **Mô tả**: Mô tả ngắn về phòng
- **Host**: Người tạo phòng
- **👥 Participants**: Số người tham gia

**Click vào card để vào phòng đấu giá**

### 3. Phòng đấu giá - Auction Room

Khi vào phòng, bạn sẽ thấy layout 3 cột:

#### Cột trái - Upcoming Items (Items sắp đấu giá)
- Danh sách các items sẽ được đấu giá tiếp theo
- Hiển thị tên và giá khởi điểm
- Có thể scroll để xem thêm

#### Cột giữa - Current Item (Item hiện tại)
Đây là khu vực chính để đấu giá:

**Thông tin item:**
- **Hình ảnh lớn**: Ảnh của sản phẩm
- **Tên item**: Tiêu đề sản phẩm
- **Mô tả**: Chi tiết về sản phẩm

**Thông tin giá:**
- **Start Price**: Giá khởi điểm
- **Current Bid**: Giá đấu hiện tại (màu indigo, nổi bật)

**Countdown Timer:**
- Hiển thị thời gian còn lại
- **Trạng thái bình thường**: Nền xanh indigo
- **Trạng thái cảnh báo**: Nền vàng amber khi còn 30 giây
- **Tự động reset**: Timer reset về 30 giây nếu có bid mới trong 30 giây cuối

**Đặt giá:**
1. **Your Bid input**: Nhập số tiền bạn muốn đấu
   - Phải cao hơn current bid ít nhất 10,000 đ
2. **Quick bid buttons**: 
   - **+50K**: Tăng 50,000 đ
   - **+100K**: Tăng 100,000 đ
   - **+500K**: Tăng 500,000 đ
3. **Place Bid**: Click để đặt giá (nút indigo)
4. **🛒 Buy Now**: Mua ngay với giá cố định (nút xanh lá)

#### Cột phải - Chat & Participants

**Participants:**
- Hiển thị số người tham gia
- Danh sách người trong phòng

**Chat:**
- Xem tin nhắn real-time từ mọi người
- Gửi tin nhắn bằng cách:
  1. Nhập tin nhắn vào ô "Type a message..."
  2. Click nút 📤 hoặc nhấn Enter

**Leave Room:**
- Click nút "← Leave Room" ở góc trên bên trái để rời phòng

### 4. Tài khoản - Account

Click "Account" trên navigation bar để xem:

#### Profile Information
- **👤 Avatar**: Icon người dùng
- **User ID**: Mã số người dùng
- **Email**: Email đăng ký
- **Status**: Trạng thái tài khoản (Active)

#### Financial Cards
**💰 Available Balance:**
- Hiển thị số dư khả dụng
- Dùng để đấu giá và mua items

**🏦 Bank Account:**
- Thông tin tài khoản ngân hàng
- "Not set" nếu chưa cập nhật

**📅 Member Since:**
- Ngày tham gia AuctionHub

#### Action Buttons
**💵 Deposit Money:**
- Nạp tiền vào tài khoản
- Click để mở dialog nạp tiền

**💸 Withdraw Money:**
- Rút tiền về tài khoản ngân hàng
- Cần có thông tin ngân hàng

**🏦 Bank Information:**
- Cập nhật thông tin ngân hàng
- Số tài khoản, tên ngân hàng

#### Recent Activity
Xem lịch sử hoạt động:
- **Participated**: Tham gia phòng đấu giá
- **Won**: Thắng đấu giá
- **Completed**: Giao dịch hoàn thành

### 5. Rooms - Phòng của tôi

Click "Rooms" để xem:
- Các phòng bạn đã tạo
- Các phòng bạn đang tham gia
- Quản lý phòng của bạn

## Tính năng nổi bật

### 1. Real-time Countdown Timer
- Timer đếm ngược chính xác từng giây
- Cảnh báo khi còn 30 giây (đổi màu vàng)
- Tự động reset khi có bid mới trong 30 giây cuối
- Hiển thị rõ ràng, dễ đọc

### 2. Quick Bid Buttons
- Tăng giá nhanh với các mức cố định
- Tiết kiệm thời gian khi đấu giá
- Tránh nhập sai số tiền

### 3. Buy Now Option
- Mua ngay với giá cố định
- Kết thúc đấu giá ngay lập tức
- Đảm bảo có được item

### 4. Real-time Chat
- Trò chuyện với người tham gia khác
- Thảo luận về items
- Tạo không khí sôi động

### 5. Clean, Modern UI
- Giao diện sạch sẽ, dễ sử dụng
- Colors và typography chuyên nghiệp
- Smooth animations và transitions
- Responsive với window size

## Tips sử dụng

### Đấu giá hiệu quả
1. **Theo dõi timer**: Chú ý đến countdown timer
2. **Sử dụng quick bids**: Nhanh hơn khi đấu giá gấp
3. **Chuẩn bị sẵn số tiền**: Nhập trước số tiền bạn muốn đấu
4. **Đấu trong 30 giây cuối**: Timer sẽ reset, bạn có thêm thời gian

### Quản lý tài chính
1. **Nạp tiền trước**: Đảm bảo có đủ balance
2. **Cập nhật bank info**: Để rút tiền dễ dàng
3. **Theo dõi activity**: Xem lịch sử giao dịch

### Tạo phòng đấu giá
1. Click **+ Create Room**
2. Nhập thông tin phòng
3. Thêm items để đấu giá
4. Mời người tham gia

## Troubleshooting

### Không build được
- Kiểm tra Qt đã cài đúng chưa
- Kiểm tra PATH có Qt bin chưa
- Thử clean và build lại

### Không chạy được
- Kiểm tra file .exe trong thư mục release/
- Đảm bảo có Qt DLLs trong PATH
- Thử chạy từ Qt Creator

### UI không hiển thị đúng
- Kiểm tra Qt version (cần 5.15+)
- Thử resize window
- Restart ứng dụng

## Keyboard Shortcuts

- **Enter** trong chat input: Gửi tin nhắn
- **Enter** trong bid input: Đặt giá
- **Esc**: Đóng dialogs

## Liên hệ & Hỗ trợ

Nếu gặp vấn đề hoặc có câu hỏi, vui lòng:
1. Kiểm tra phần Troubleshooting
2. Đọc ELITE_UI_README.md
3. Tạo issue trong repository

## Phát triển tiếp

Các tính năng sẽ được thêm:
- Kết nối server thật
- Upload hình ảnh
- Notifications
- Dark mode
- Mobile version
- Multi-language

---

**Chúc bạn có trải nghiệm đấu giá tuyệt vời với Elite Auction UI!** 🎉
