# Quick Start - Elite Auction UI

## Chạy nhanh trong 3 bước

### Bước 1: Mở Qt Creator
- Khởi động **Qt Creator**
- File → **Open File or Project**
- Chọn: `auction_app/elite_auction_app.pro`

### Bước 2: Build
- Nhấn **Ctrl + B** (hoặc click icon 🔨)
- Đợi build xong (xem "Build succeeded")

### Bước 3: Run
- Nhấn **Ctrl + R** (hoặc click nút ▶)
- Ứng dụng sẽ khởi động!

---

## Hoặc dùng Command Line

```bash
cd auction_app
build_elite_ui.bat
run_elite_ui.bat
```

---

## Cấu trúc Files

```
elite_auction_app.pro          ← Mở file này trong Qt Creator
elite_auction_main.cpp         ← Entry point
elite_login_window.h/cpp       ← Login screen
elite_main_window.h/cpp        ← Main window (Explore, Rooms, Account)
elite_auction_room.h/cpp       ← Auction room (3-column layout)
elite_account_window.h/cpp     ← Account management
elite_network_client.h/cpp     ← Network client
```

---

## Tính năng chính

✅ **Login** - Welcome screen minimalist
✅ **Explore** - Search & filter auction rooms
✅ **Auction Room** - 3-column layout với timer, bidding, chat
✅ **Account** - Balance, bank info, activity history
✅ **Real-time Timer** - Countdown với warning state (30s)
✅ **Quick Bids** - +50K, +100K, +500K buttons
✅ **Buy Now** - Mua ngay với giá cố định
✅ **Chat** - Real-time messaging

---

## Troubleshooting nhanh

**Lỗi build?**
- Menu: Build → Clean All
- Menu: Build → Run qmake
- Menu: Build → Rebuild All

**Không có Kit?**
- Tools → Options → Kits
- Click "Auto-detect"

**Không chạy được?**
- Kiểm tra Build Mode: Release
- Xem Application Output tab

---

## Đọc thêm

- **Chi tiết**: `HUONG_DAN_CHAY_ELITE_QT.md`
- **Features**: `ELITE_UI_README.md`
- **User Guide**: `HUONG_DAN_ELITE_UI.md`

---

**Enjoy coding!** 🚀
