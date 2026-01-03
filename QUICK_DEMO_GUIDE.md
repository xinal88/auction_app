# Quick Demo Guide - Elite Auction UI

## 🚀 Chạy Nhanh (5 phút)

### Bước 1: Setup Database (2 phút)
```bash
# Tạo database
createdb -U postgres auction_db

# Import schema và data
psql -U postgres -d auction_db -f data/schema.sql
psql -U postgres -d auction_db -f data/data.sql
```

### Bước 2: Cấu Hình (30 giây)
Mở `elite_main_window.cpp`, dòng ~20, sửa password:
```cpp
db->connectToDatabase("localhost", "auction_db", "postgres", "YOUR_PASSWORD")
```

### Bước 3: Build & Run (2 phút)
```bash
# Windows
build_elite_ui.bat
run_elite_ui.bat

# Linux/Mac
qmake elite_auction_app.pro && make
./elite_auction_app
```

## ✨ Tính Năng Demo

### 1. Explore Page
- ✅ 5 auction rooms với hình ảnh thực
- ✅ Filter: All / Live / Upcoming
- ✅ Click vào room để vào auction

### 2. Auction Room
- ✅ Current item với hình ảnh
- ✅ Upcoming items (sidebar trái)
- ✅ Place bid với validation
- ✅ Buy Now với confirmation popup
- ✅ Chat & participants (sidebar phải)
- ✅ Countdown timer

### 3. Database Integration
- ✅ Load rooms từ PostgreSQL
- ✅ Load items với images
- ✅ User balance từ DB
- ✅ Real-time data

## 🎯 Demo Flow

1. **Start App** → Kết nối database tự động
2. **Explore** → Xem 5 rooms với hình ảnh
3. **Filter** → Click "Live" để xem rooms đang active
4. **Enter Room** → Click "Luxury Watches Auction"
5. **View Item** → Rolex Submariner với hình ảnh
6. **Place Bid** → Nhập giá > 75,010,000
7. **Buy Now** → Click → Popup confirmation → Confirm
8. **Success** → Thông báo mua thành công

## 📊 Demo Data

### Rooms Available:
1. **Luxury Watches** (LIVE) - Rolex, Omega, Patek Philippe
2. **Vintage Electronics** (UPCOMING) - Macintosh, Walkman
3. **Art & Collectibles** (LIVE) - Prints, Vinyl, Sculptures
4. **Rare Books** (UPCOMING) - Harry Potter, Hemingway
5. **Designer Fashion** (LIVE) - Hermès, Chanel, LV

### Price Range:
- Min: 2,000,000 đ (Nintendo Game Boy)
- Max: 350,000,000 đ (Hermès Birkin)
- Average: ~50,000,000 đ

## 🐛 Troubleshooting

### "Database connection failed"
```bash
# Check PostgreSQL running
sudo systemctl status postgresql

# Check credentials in elite_main_window.cpp
```

### "QPSQL driver not loaded"
```bash
# Windows: Copy libpq.dll to Qt bin folder
# Linux: sudo apt-get install libpq-dev
```

### "No rooms displayed"
```bash
# Check data imported
psql -U postgres -d auction_db -c "SELECT * FROM auction_rooms;"
```

## 💡 Tips

1. **Fullscreen** - Press F11 để test responsive layout
2. **Multiple Rooms** - Click vào các rooms khác nhau
3. **Filters** - Test Live/Upcoming filters
4. **Buy Now** - Xem popup confirmation đẹp
5. **Images** - Đợi vài giây để images load

## 📸 Screenshots Points

1. Explore page với 5 rooms
2. Filter buttons (Live/Upcoming)
3. Room card với image và info
4. Auction room layout 3 cột
5. Current item với hình ảnh lớn
6. Upcoming items sidebar
7. Buy Now confirmation popup
8. Success message

---

**Ready to demo! 🎉**

Thời gian demo: 5-10 phút
Độ ổn định: ⭐⭐⭐⭐⭐
Wow factor: 🔥🔥🔥
