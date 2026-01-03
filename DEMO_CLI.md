# 🖥️ HƯỚNG DẪN DEMO VỚI CLI CLIENT

## Build CLI Client

```bash
cd /mnt/f/AI_project/[HUST]Auction_Application_v1/auction_app

# Build CLI client
make -f Makefile.cli clean
make -f Makefile.cli

# Kiểm tra file đã tạo
ls -lh auction_client_cli
```

## Chạy Demo

### Terminal 1: Server

```bash
cd /mnt/f/AI_project/[HUST]Auction_Application_v1/auction_app

# Kill server cũ nếu có
pkill -9 auction_server

# Chạy server
./auction_server
```

Đợi thấy: `Server is listening on port 5500...`

### Terminal 2: Client 1 (Alice)

```bash
cd /mnt/f/AI_project/[HUST]Auction_Application_v1/auction_app
./auction_client_cli
```

**Thao tác:**
1. Chọn `1` - Login
2. Username: `alice`
3. Password: `pass123`
4. Chọn `5` - Create room
5. Room name: `Auction Room`
6. Chọn `8` - Create item
   - Item name: `iPhone 15 Pro Max`
   - Description: `Brand new, sealed`
   - Start price: `20000000`
   - Buy now price: `30000000`
   - Duration: `120` (2 phút)
7. Chọn `7` - View items (xem item vừa tạo)

### Terminal 3: Client 2 (Bob)

```bash
cd /mnt/f/AI_project/[HUST]Auction_Application_v1/auction_app
./auction_client_cli
```

**Thao tác:**
1. Chọn `1` - Login
2. Username: `bob`
3. Password: `pass123`
4. Chọn `4` - List rooms
5. Chọn `6` - Join room
6. Room ID: `1` (hoặc ID hiển thị từ list)
7. Chọn `7` - View items
8. Chọn `9` - Place bid
   - Item ID: `1`
   - Bid amount: `21000000`

**Alice sẽ thấy notification:**
```
🔔 NEW BID on Item #1: 21000000 VND by bob
```

### Test Chat

**Bob (Terminal 3):**
- Chọn `10` - Send chat
- Message: `Hello Alice!`

**Alice (Terminal 2) sẽ thấy:**
```
💬 [bob]: Hello Alice!
```

### Test Timer Auto-Reset

**Alice bid lại:**
- Chọn `9` - Place bid
- Item ID: `1`
- Bid amount: `22000000`

**Bob sẽ thấy:**
```
🔔 NEW BID on Item #1: 22000000 VND by alice
```

Timer sẽ reset về 30s nếu còn < 30s.

### Test Item Sold

Đợi hết thời gian, cả Alice và Bob sẽ thấy:
```
🎉 ITEM SOLD! Item #1 sold to alice for 22000000 VND
```

---

## Tính năng đã implement

✅ Login/Register  
✅ Deposit money  
✅ Create/Join room  
✅ List rooms  
✅ Create item  
✅ View items  
✅ Place bid  
✅ Real-time bid notifications  
✅ Chat in room  
✅ Item sold notification  
✅ Timer auto-reset khi bid  

---

## Accounts có sẵn

| Username | Password | Balance |
|----------|----------|---------|
| alice    | pass123  | 50,000,000 VND |
| bob      | pass123  | 30,000,000 VND |
| charlie  | pass123  | 15,000,000 VND |

---

## Troubleshooting

### Build lỗi

```bash
# Kiểm tra dependencies
sudo apt-get install -y build-essential libpq-dev

# Build lại
make -f Makefile.cli clean
make -f Makefile.cli
```

### Connection refused

```bash
# Kiểm tra server đang chạy
ps aux | grep auction_server

# Kiểm tra port
netstat -tulpn | grep 5500
```

### Database error

```bash
# Restart PostgreSQL
sudo service postgresql restart

# Check database
sudo -u postgres psql -d auction_db -c "SELECT * FROM users;"
```

---

**Chúc bạn demo thành công! 🎉**
