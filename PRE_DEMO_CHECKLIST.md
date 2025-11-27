# ✅ PRE-DEMO CHECKLIST

## Trước khi demo, check tất cả các mục sau:

---

## 🗄️ Database

- [ ] PostgreSQL service đang chạy
  ```bash
  sudo service postgresql status
  ```

- [ ] Database `auction_db` tồn tại
  ```bash
  psql -U trung -d auction_db -c "\dt"
  ```

- [ ] Có data trong tables
  ```bash
  psql -U trung -d auction_db -c "SELECT COUNT(*) FROM users;"
  # Kết quả: 10 users
  ```

- [ ] Test login credentials
  ```bash
  psql -U trung -d auction_db -c "SELECT username FROM users LIMIT 5;"
  # alice, bob, charlie, david, emma
  ```

---

## 🖥️ Server

- [ ] Server compile thành công
  ```bash
  cd auction_app
  make clean
  make server
  # Không có errors
  ```

- [ ] Server chạy được
  ```bash
  ./auction_server
  # Thấy: "Server is listening on port 5500..."
  ```

- [ ] Server log được tạo
  ```bash
  ls -la server.log
  tail -5 server.log
  ```

- [ ] Port 5500 đang listen
  ```bash
  sudo netstat -tulpn | grep 5500
  # Hoặc
  sudo lsof -i :5500
  ```

---

## 🎨 Client

- [ ] Client compile thành công
  ```bash
  qmake auction_client.pro
  make
  # Không có errors
  ```

- [ ] Client chạy được
  ```bash
  ./auction_client
  # Cửa sổ login hiện ra
  ```

- [ ] Client connect được server
  - Thấy "Connected to server successfully" trong console
  - Không có error dialog

---

## 🧪 Functional Tests

### Test 1: Login
- [ ] Login với `alice` / `pass123` thành công
- [ ] Login với sai password thất bại
- [ ] Register user mới thành công

### Test 2: Account Management
- [ ] Deposit 1,000,000 VND thành công
- [ ] Balance hiển thị đúng
- [ ] Redeem 500,000 VND thành công
- [ ] View history hiển thị transactions

### Test 3: Room Management
- [ ] Tạo phòng mới thành công
- [ ] Refresh rooms list hiển thị phòng vừa tạo
- [ ] Join phòng thành công
- [ ] Current room label cập nhật
- [ ] Leave phòng thành công

### Test 4: Auction - Create Item
- [ ] Tạo item trong phòng thành công
- [ ] Item hiển thị trong items table
- [ ] Timer bắt đầu countdown

### Test 5: Auction - Bidding
- [ ] Mở client thứ 2, login với `bob`
- [ ] Bob join cùng phòng với Alice
- [ ] Bob bid thành công
- [ ] Alice thấy bid notification ngay lập tức
- [ ] Current price cập nhật ở cả 2 clients

### Test 6: Timer System ⭐
- [ ] Tạo item với duration 60s
- [ ] Timer countdown hiển thị
- [ ] Đợi đến còn 30s
- [ ] Thấy warning (có thể check log hoặc UI highlight)
- [ ] Bid trong 30s cuối
- [ ] **Timer reset về 30s** ✅
- [ ] Đợi hết thời gian
- [ ] Item sold notification hiển thị

### Test 7: Buy Now
- [ ] Tạo item với buy_now_price
- [ ] Click "Buy Now"
- [ ] Confirmation dialog hiện ra
- [ ] Confirm → Item sold ngay lập tức
- [ ] Timer removed

### Test 8: Chat
- [ ] Gửi tin nhắn trong phòng
- [ ] Tin nhắn hiển thị với timestamp
- [ ] User khác trong phòng nhận được
- [ ] Sender name hiển thị đúng

---

## 📊 Performance Tests

- [ ] Server handle được 3+ concurrent clients
- [ ] Không có memory leaks (check với `top` hoặc `htop`)
- [ ] Response time < 1s cho mọi operations
- [ ] UI không bị freeze khi có nhiều updates

---

## 📝 Logs

- [ ] Server log ghi đầy đủ events
  ```bash
  tail -20 server.log
  # Thấy: LOGIN, BID, TIMER, etc.
  ```

- [ ] Client log ghi đầy đủ actions
  ```bash
  tail -20 client.log
  # Thấy: LOGIN, DEPOSIT, BID, etc.
  ```

- [ ] Không có ERROR logs (trừ test cases)

---

## 🔒 Security Tests

- [ ] Không thể bid khi chưa login
- [ ] Không thể join phòng khi chưa login
- [ ] Không thể bid số tiền < current_price + 10,000
- [ ] Không thể redeem nhiều hơn balance
- [ ] Session token được validate

---

## 🎯 Demo Scenarios

### Scenario 1: Quick Demo (3 phút)
1. [ ] Start server
2. [ ] Start client 1, login alice
3. [ ] Deposit money
4. [ ] Create room
5. [ ] Create item (30s duration)
6. [ ] Start client 2, login bob
7. [ ] Bob join room
8. [ ] Bob bid
9. [ ] Alice sees notification
10. [ ] Wait for timer → Item sold

### Scenario 2: Timer Reset Demo (5 phút) ⭐
1. [ ] Alice creates item (60s duration)
2. [ ] Bob joins room
3. [ ] Wait until 25s remaining
4. [ ] Bob bids
5. [ ] **Show timer reset to 30s** ✅
6. [ ] Wait until 20s
7. [ ] Alice bids
8. [ ] **Show timer reset to 30s again** ✅
9. [ ] Wait until end
10. [ ] Show item sold notification

### Scenario 3: Full Feature Demo (10 phút)
1. [ ] Login/Register
2. [ ] Deposit/Redeem
3. [ ] Create room
4. [ ] Create item
5. [ ] Multi-user bidding
6. [ ] Timer reset
7. [ ] Chat
8. [ ] Buy now
9. [ ] View history
10. [ ] Show logs

---

## 📸 Screenshots to Prepare

- [ ] Login window
- [ ] Main window - Account tab
- [ ] Main window - Rooms tab
- [ ] Main window - Auction tab
- [ ] Bid notification
- [ ] Timer countdown
- [ ] Timer reset moment ⭐
- [ ] Chat messages
- [ ] Server log
- [ ] Database tables

---

## 🎤 Presentation Points

### Giới thiệu (1 phút)
- [ ] Tên dự án
- [ ] Công nghệ sử dụng
- [ ] Kiến trúc tổng quan

### Demo tính năng cơ bản (5 phút)
- [ ] Login/Register
- [ ] Room management
- [ ] Item creation
- [ ] Bidding
- [ ] Buy now

### Demo tính năng nâng cao (5 phút)
- [ ] **Timer system với 30s warning** ⭐
- [ ] **Auto-reset timer khi bid** ⭐
- [ ] Real-time notifications
- [ ] Chat system
- [ ] Money management

### Giải thích kỹ thuật (3 phút)
- [ ] Multi-threaded server
- [ ] Binary protocol
- [ ] Session management
- [ ] Timer thread
- [ ] Database design

### Q&A (2 phút)
- [ ] Sẵn sàng trả lời câu hỏi
- [ ] Có thể show code nếu cần

---

## 🐛 Common Issues & Solutions

### Issue 1: Server không start
```bash
# Check PostgreSQL
sudo service postgresql start

# Check port
sudo lsof -i :5500
# Nếu bị chiếm → kill process hoặc đổi port
```

### Issue 2: Client không connect
```bash
# Check server đang chạy
ps aux | grep auction_server

# Check firewall
sudo ufw status
sudo ufw allow 5500
```

### Issue 3: Database error
```bash
# Reset database
dropdb -U trung auction_db
createdb -U trung auction_db
psql -U trung -d auction_db -f data/schema.sql
psql -U trung -d auction_db -f data/data.sql
```

### Issue 4: Timer không reset
```bash
# Check server log
tail -f server.log | grep "Timer reset"

# Verify trong code: handlers.c, handle_bid()
# Phải có: timer_reset(&g_timer_manager, req.item_id, 30);
```

---

## 📋 Final Checklist

Trước khi demo:

- [ ] ✅ Database running và có data
- [ ] ✅ Server compiled và running
- [ ] ✅ Client compiled và running
- [ ] ✅ Tất cả tính năng cơ bản hoạt động
- [ ] ✅ Timer system hoạt động (30s warning + reset)
- [ ] ✅ Logs được ghi đầy đủ
- [ ] ✅ Có ít nhất 2 clients để demo multi-user
- [ ] ✅ Đã test scenario timer reset
- [ ] ✅ Đã chuẩn bị câu trả lời cho Q&A
- [ ] ✅ Code clean, không có debug prints

---

## 🎯 Success Criteria

Demo thành công khi:

1. ✅ Server start không lỗi
2. ✅ Client connect được
3. ✅ Login thành công
4. ✅ Tạo room và item thành công
5. ✅ Multi-user bidding hoạt động
6. ✅ **Timer reset khi bid trong 30s cuối** ⭐
7. ✅ Real-time notifications hoạt động
8. ✅ Chat hoạt động
9. ✅ Không có crashes
10. ✅ Logs ghi đầy đủ

---

## 🚀 Ready to Demo!

Khi tất cả checkboxes đã được tick ✅, bạn sẵn sàng để demo!

**Good luck! 🎉**

---

*Last updated: November 27, 2024*
