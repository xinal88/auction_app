# Elite Auction UI - Modern Minimalist Design

## Tổng quan

Elite Auction UI là giao diện đấu giá trực tuyến hiện đại với thiết kế minimalist, chuyên nghiệp và elegant. Ứng dụng được xây dựng bằng Qt C++ với focus vào trải nghiệm người dùng cao cấp.

## Đặc điểm thiết kế

### Design Principles
- **Modern Minimalism**: Sử dụng white space hợp lý, layout sạch sẽ
- **Card-based Layout**: Tất cả nội dung được tổ chức trong cards với rounded corners
- **Soft Shadows**: Shadow nhẹ nhàng tạo depth
- **Smooth Animations**: Transitions mượt mà cho các tương tác
- **Professional Color Scheme**: 
  - Primary: Indigo (#4F46E5) - Actions chính
  - Green: Success states và Buy Now
  - Amber: Warnings (30 giây cuối)
  - Red: Errors và Live badges
  - Neutral: White/Light gray backgrounds

### Typography
- Font: Segoe UI (Windows), Inter (fallback)
- Clear hierarchy với font sizes và weights khác nhau
- Readable và professional

## Cấu trúc ứng dụng

### 1. Login Window (elite_login_window.cpp)
- Welcome screen với branding
- Clean login form
- Email và password inputs
- Sign in button với hover effects
- Link to sign up

### 2. Main Window (elite_main_window.cpp)
- **Navigation Bar**: Logo, menu items (Explore, Rooms, Account), balance display, Create Room button
- **Explore Page**: 
  - Search bar với filters (Live, Upcoming)
  - Grid of auction room cards
  - Room cards hiển thị: image, title, description, host, participants, status badge
- **Rooms Page**: Danh sách rooms của user
- **Account Page**: Thông tin tài khoản

### 3. Auction Room (elite_auction_room.cpp)
**Three-column layout:**

**Left Panel - Upcoming Items:**
- Danh sách items sắp đấu giá
- Hiển thị tên và giá khởi điểm
- Scrollable list

**Center Panel - Current Item:**
- Large item image
- Item title và description
- Start price và Current bid
- **Countdown Timer**: 
  - Hiển thị thời gian còn lại
  - Warning state (amber) khi còn 30 giây
  - Auto-reset khi có bid mới trong 30 giây cuối
- Bid input với validation
- Quick bid buttons (+50K, +100K, +500K)
- Place Bid button (primary action)
- Buy Now button (green, prominent)

**Right Panel - Chat & Participants:**
- Participants count
- Real-time chat display
- Message input với send button
- Scrollable chat history

### 4. Account Window (elite_account_window.cpp)
- Profile information với avatar
- User ID, email, status badge
- **Financial Cards**:
  - Available Balance
  - Bank Account info
  - Member Since date
- **Action Buttons**:
  - Deposit Money (primary)
  - Withdraw Money (amber)
  - Bank Information (secondary)
- **Recent Activity**:
  - Activity timeline
  - Status badges (Won, Completed, Participated)

## Cài đặt và Build

### Yêu cầu
- Qt 5.15 hoặc cao hơn
- MinGW hoặc MSVC compiler
- qmake

### Build trên Windows

1. **Sử dụng script tự động:**
```bash
build_elite_ui.bat
```

2. **Build thủ công:**
```bash
qmake elite_auction_app.pro
mingw32-make
```

3. **Chạy ứng dụng:**
```bash
run_elite_ui.bat
```
hoặc
```bash
release\elite_auction_app.exe
```

### Build trên Linux/Mac

```bash
qmake elite_auction_app.pro
make
./elite_auction_app
```

## Cấu trúc files

```
elite_auction_app.pro          # Qt project file
elite_auction_main.cpp         # Entry point
elite_login_window.h/cpp       # Login screen
elite_main_window.h/cpp        # Main application window
elite_auction_room.h/cpp       # Auction room interface
elite_account_window.h/cpp     # Account management
elite_network_client.h/cpp     # Network communication
elite_resources.qrc            # Resources file
build_elite_ui.bat            # Build script (Windows)
run_elite_ui.bat              # Run script (Windows)
```

## Tính năng chính

### Authentication
- ✅ Welcome screen với branding
- ✅ Login form với validation
- ✅ Sign up link

### Explore & Discovery
- ✅ Search auction rooms
- ✅ Filter by status (Live, Upcoming)
- ✅ Room cards với preview
- ✅ Click to join room

### Auction Room
- ✅ Three-column responsive layout
- ✅ Upcoming items queue
- ✅ Current item display với large image
- ✅ Real-time countdown timer
- ✅ Timer warning state (30 seconds)
- ✅ Bid input với quick increment buttons
- ✅ Place Bid action
- ✅ Buy Now action
- ✅ Real-time chat
- ✅ Participants list

### Account Management
- ✅ Profile overview
- ✅ Balance display
- ✅ Bank account information
- ✅ Deposit money
- ✅ Withdraw money
- ✅ Activity history
- ✅ Status badges

## UI Components

### Buttons
- **Primary Button**: Indigo background, white text (main actions)
- **Secondary Button**: White background, border (secondary actions)
- **Link Button**: Transparent, underlined text
- **Quick Bid Buttons**: Light gray, compact

### Input Fields
- Clean borders với focus states
- Placeholder text
- Proper padding và sizing
- Focus indicator (indigo border)

### Cards
- White background
- Rounded corners (16px)
- Soft shadows
- Hover effects

### Badges
- **Live**: Red background
- **Upcoming**: Amber background
- **Active**: Green background
- **Won/Completed/Participated**: Various colors

### Timer Display
- Large, prominent display
- Normal state: Indigo
- Warning state: Amber (last 30 seconds)
- Bold, easy-to-read font

## Customization

Bạn có thể customize colors và styles trong các hàm `getStyleSheet()` của mỗi window:

```cpp
QString EliteMainWindow::getStyleSheet()
{
    return R"(
        #primaryButton {
            background-color: #4F46E5;  // Change this
            color: white;
            // ...
        }
    )";
}
```

## Best Practices

1. **Consistent Spacing**: Sử dụng spacing nhất quán (10px, 15px, 20px, 30px)
2. **Color Palette**: Giữ nguyên color scheme để maintain consistency
3. **Typography**: Sử dụng font sizes theo hierarchy
4. **Shadows**: Subtle shadows (blur 20px, offset 4px, opacity 15-20%)
5. **Border Radius**: Consistent rounded corners (8px, 12px, 16px)
6. **Hover States**: Luôn có hover effects cho interactive elements

## Responsive Design

Layout tự động adjust với window size:
- Three-column layout trong auction room
- Scrollable areas cho long content
- Fixed widths cho side panels
- Flexible center panel

## Performance

- Efficient Qt layouts
- Minimal redraws
- Optimized stylesheets
- Smooth animations

## Future Enhancements

- [ ] Real network integration
- [ ] Database connection
- [ ] Image upload và display
- [ ] Advanced filters
- [ ] Notifications system
- [ ] Mobile responsive version
- [ ] Dark mode
- [ ] Multi-language support

## Support

Để được hỗ trợ hoặc báo lỗi, vui lòng tạo issue trong repository.

## License

MIT License - Free to use and modify.
