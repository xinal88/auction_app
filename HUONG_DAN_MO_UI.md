# 🎨 HƯỚNG DẪN MỞ VÀ XEM UI TRONG QT CREATOR

## Bước 1: Mở Qt Creator

1. Khởi động **Qt Creator**
2. Bạn sẽ thấy màn hình Welcome

## Bước 2: Mở file .ui để xem giao diện

### Cách 1: Mở trực tiếp file .ui

1. **File** → **Open File or Project**
2. Navigate đến: `F:\AI_project\[HUST]Auction_Application_v1\auction_app\src\client\`
3. Chọn file: **`login_window.ui`**
4. Click **Open**

Bạn sẽ thấy giao diện Login Window trong Qt Designer!

### Cách 2: Mở qua Project

1. **File** → **Open File or Project**
2. Chọn: `F:\AI_project\[HUST]Auction_Application_v1\auction_app\auction_client.pro`
3. Configure project với MinGW kit
4. Trong **Projects panel** bên trái, expand **src/client**
5. Double-click vào **`login_window.ui`** hoặc **`main_window.ui`**

## Bước 3: Xem và chỉnh sửa UI

Khi file `.ui` mở, bạn sẽ thấy:

### Bên trái: Widget Box
- Kéo thả các widgets (Button, Label, LineEdit, etc.)

### Giữa: Design Canvas
- Xem và chỉnh sửa giao diện trực quan
- Click vào widget để chọn
- Kéo để di chuyển/resize

### Bên phải: Property Editor
- Thay đổi properties của widget đã chọn
- objectName, text, styleSheet, etc.

## Bước 4: Chuyển đổi giữa các chế độ

Ở dưới cùng bên trái, có 3 nút:

1. **Design** - Chế độ thiết kế (kéo thả)
2. **Edit** - Chế độ chỉnh sửa code
3. **Debug** - Chế độ debug

## Các file UI đã tạo

### 1. login_window.ui
Giao diện đăng nhập với:
- ✅ Title "Auction Application"
- ✅ Username input
- ✅ Password input (ẩn ký tự)
- ✅ Login button (màu xanh lá)
- ✅ Register button (màu xanh dương)
- ✅ Status label
- ✅ Styling đẹp với màu sắc và bo góc

### 2. main_window.ui
Giao diện chính với 3 tabs:

**Tab 1: Account (💰)**
- Balance display (số dư)
- Deposit input + button
- Transaction history list

**Tab 2: Rooms (🏠)**
- Room list
- Create/Join/Refresh buttons

**Tab 3: Auction (🔨)**
- Current room display
- Item list
- Create item + Bid buttons
- Chat box với input

## Bước 5: Preview UI

Để xem UI chạy thực tế:

1. Trong Qt Designer, click **Form** → **Preview** (Ctrl+Alt+R)
2. Hoặc build và run project

## Bước 6: Chỉnh sửa UI

### Thay đổi text
1. Click vào widget (ví dụ: loginButton)
2. Bên phải, tìm property **text**
3. Đổi thành text mới

### Thay đổi màu sắc
1. Click vào widget
2. Tìm property **styleSheet**
3. Click vào nút **...** để mở editor
4. Thêm CSS:
```css
background-color: #FF5722;
color: white;
border-radius: 10px;
```

### Thêm widget mới
1. Từ Widget Box bên trái, kéo widget vào canvas
2. Đặt tên trong property **objectName**
3. Adjust position và size

### Sắp xếp với Layout
1. Chọn nhiều widgets (Ctrl+Click)
2. Right-click → **Lay Out** → chọn layout type:
   - **Vertically** (xếp dọc)
   - **Horizontally** (xếp ngang)
   - **In Grid** (lưới)

## Bước 7: Build và Run

1. Click **Build** (🔨) hoặc Ctrl+B
2. Click **Run** (▶️) hoặc Ctrl+R
3. Ứng dụng sẽ mở với UI bạn vừa thiết kế!

## Tips

### Xem cả 2 file UI
- Mở **login_window.ui** trong tab 1
- Mở **main_window.ui** trong tab 2
- Chuyển qua lại giữa các tabs

### Zoom in/out
- Ctrl + Mouse Wheel
- Hoặc View → Zoom In/Out

### Undo/Redo
- Ctrl+Z / Ctrl+Y

### Copy/Paste widgets
- Ctrl+C / Ctrl+V

## Troubleshooting

### Không thấy Design mode
- Click vào file .ui trong Projects panel
- Hoặc File → Open File → chọn .ui file

### UI không đẹp khi run
- Kiểm tra styleSheet đã được apply chưa
- Build lại project (Clean → Build)

### Widgets bị chồng lên nhau
- Sử dụng Layouts để tự động sắp xếp
- Right-click → Lay Out

---

**Bây giờ bạn có thể mở Qt Creator và xem UI ngay! 🎉**

Chỉ cần:
1. Mở Qt Creator
2. File → Open File
3. Chọn `login_window.ui` hoặc `main_window.ui`
4. Xem và chỉnh sửa!
