# 🚀 Hướng Dẫn Clean Up và Push Lên GitHub

## Cách 1: Sử Dụng PowerShell Script (Khuyến Nghị)

### Bước 1: Mở PowerShell trong folder auction_app
```powershell
# Click chuột phải trong folder auction_app
# Chọn "Open in Terminal" hoặc "Open PowerShell window here"
```

### Bước 2: Cho phép chạy script
```powershell
Set-ExecutionPolicy -Scope Process -ExecutionPolicy Bypass
```

### Bước 3: Chạy cleanup script
```powershell
.\cleanup_and_push.ps1
```

Script sẽ tự động:
- ✅ Xóa tất cả files rác (.o, .log, moc_*, etc.)
- ✅ Xóa old documentation
- ✅ Xóa test files
- ✅ Xóa old UI files
- ✅ Tạo folder docs/
- ✅ Di chuyển documentation vào docs/
- ✅ Đổi tên README_NEW.md thành README.md

### Bước 4: Push lên GitHub
```bash
# Kiểm tra status
git status

# Add tất cả files
git add .

# Commit
git commit -m "feat: Complete Elite UI with full backend integration

- Modern Qt 6 UI with custom styling
- Full database integration (PostgreSQL)
- User management (Register/Login)
- Money management (Deposit/Withdraw/Bank info)
- Auction rooms (Create/Join/Browse/Search/Filter)
- Real-time bidding with validation
- Buy now functionality
- Live chat in rooms
- Countdown timer
- Activity history and transaction logs
- Image support from URLs
- Demo mode (works without database)
- Clean project structure
- Complete documentation"

# Tạo nhánh UI
git checkout -b UI

# Push lên GitHub
git push -u origin UI
```

---

## Cách 2: Thủ Công (Nếu Script Không Chạy)

### Bước 1: Xóa Files Rác

Trong folder `auction_app`, xóa các files sau:

#### Object files và build artifacts
```
*.o
*.obj
moc_*.cpp
moc_*.o
moc_predefs.h
Makefile.*
*.log
.qmake.stash
```

#### Test files
```
test_elite_compile.cpp
test_qt.cpp
test_qt.pro
```

#### Old UI files
```
modern_auction_ui.cpp
modern_auction_app.cpp
modern_auction_app.pro
premium_auction_ui.cpp
premium_modern_auction.cpp
premium_auction_ui.pro
premium_modern_auction.pro
simple_auction_main.cpp
simple_auction_client.pro
```

#### Old .pro files (giữ lại elite_auction_final.pro)
```
auction_app.pro
auction_client.pro
elite_auction_app.pro
elite_auction_app_simple.pro
```

#### Compiled binaries
```
auction_client
auction_client_cli
auction_server
```

#### Old build scripts
```
build_client.sh
build_elite_ui.bat
build_modern_ui.bat
build_modern_ui.sh
build_premium_ui.bat
build_premium_ui.sh
build_ui.bat
run_modern_ui.bat
run_modern_ui.sh
run_premium_ui.bat
run_premium_ui.sh
run_ui.bat
run_server.sh
setup_database.sh
setup_db.sh
find_postgresql.bat
reorganize.bat
```

#### Old documentation (xóa hết, giữ lại những file quan trọng)
Xóa tất cả các file .md NGOẠI TRỪ:
- BACKEND_HOAN_CHINH.md
- CAI_TIEN_HOAN_CHINH.md
- SETUP_USING_PGADMIN.md
- HUONG_DAN_CHAY_ELITE_QT.md
- QUICK_START_ELITE.md
- ELITE_UI_README.md
- START_HERE.md
- BUILD_FINAL_INSTRUCTIONS.md
- SETUP_WINDOWS_COMPLETE.md
- HOW_TO_OPEN_IN_QT.md
- HUONG_DAN_SETUP_DATABASE.md
- QUICK_START.md

#### Folders
```
-p/ (xóa toàn bộ)
build/ (xóa nội dung, giữ folder)
```

### Bước 2: Tổ Chức Lại

#### 2.1. Đổi tên README
```bash
del README.md
ren README_NEW.md README.md
```

#### 2.2. Tạo folder docs
```bash
mkdir docs
```

#### 2.3. Di chuyển documentation vào docs/
```bash
move BACKEND_HOAN_CHINH.md docs\
move CAI_TIEN_HOAN_CHINH.md docs\
move SETUP_USING_PGADMIN.md docs\
move HUONG_DAN_CHAY_ELITE_QT.md docs\
move QUICK_START_ELITE.md docs\
move ELITE_UI_README.md docs\
move START_HERE.md docs\
move BUILD_FINAL_INSTRUCTIONS.md docs\
move SETUP_WINDOWS_COMPLETE.md docs\
move HOW_TO_OPEN_IN_QT.md docs\
move HUONG_DAN_SETUP_DATABASE.md docs\
move QUICK_START.md docs\
```

### Bước 3: Push lên GitHub

```bash
# Kiểm tra remote
git remote -v

# Nếu chưa có, thêm remote
git remote add origin https://github.com/mtrung12/auction_app.git

# Kiểm tra status
git status

# Add tất cả files
git add .

# Commit
git commit -m "feat: Complete Elite UI with full backend integration"

# Tạo nhánh UI
git checkout -b UI

# Push
git push -u origin UI
```

---

## Cấu Trúc Folder Sau Khi Clean

```
auction_app/
├── .git/
├── .gitignore
├── README.md
├── elite_auction_final.pro
├── elite_auction_main.cpp
├── elite_login_window.cpp/h
├── elite_main_window.cpp/h
├── elite_auction_room.cpp/h
├── elite_account_window.cpp/h
├── elite_dialogs.cpp/h
├── elite_database.cpp/h
├── elite_network_client.cpp/h
├── elite_resources.qrc
├── data/
│   ├── schema.sql
│   └── data.sql
├── docs/
│   ├── BACKEND_HOAN_CHINH.md
│   ├── CAI_TIEN_HOAN_CHINH.md
│   ├── SETUP_USING_PGADMIN.md
│   ├── HUONG_DAN_CHAY_ELITE_QT.md
│   ├── QUICK_START_ELITE.md
│   ├── ELITE_UI_README.md
│   ├── START_HERE.md
│   ├── BUILD_FINAL_INSTRUCTIONS.md
│   ├── SETUP_WINDOWS_COMPLETE.md
│   ├── HOW_TO_OPEN_IN_QT.md
│   ├── HUONG_DAN_SETUP_DATABASE.md
│   └── QUICK_START.md
├── src/
│   ├── server/
│   │   ├── server.c
│   │   ├── handlers.c
│   │   ├── session_manager.c/h
│   │   └── auction_timer.c/h
│   └── client_cli/
│       └── client_cli.c
├── setup_db_simple.bat
├── setup_database_windows.bat
├── check_postgresql.bat
├── run_elite_ui.bat
├── yêu cầu project.txt
├── use_case_diagram.png
└── UseCase Diagram.asta
```

---

## Troubleshooting

### Lỗi: "git push rejected"
```bash
# Pull trước
git pull origin UI --rebase

# Sau đó push lại
git push origin UI
```

### Lỗi: "Authentication failed"
Sử dụng Personal Access Token:
1. Vào GitHub Settings > Developer settings > Personal access tokens
2. Generate new token (classic)
3. Copy token
4. Khi git push hỏi password, paste token vào

### Lỗi: "Cannot run script"
```powershell
# Cho phép chạy script
Set-ExecutionPolicy -Scope Process -ExecutionPolicy Bypass

# Sau đó chạy lại
.\cleanup_and_push.ps1
```

### Muốn xem files sẽ bị xóa trước
```powershell
# Dry run - chỉ xem, không xóa
Get-ChildItem -Path "*.o", "*.log", "moc_*" -Recurse
```

---

## Kiểm Tra Sau Khi Push

1. Vào https://github.com/mtrung12/auction_app
2. Chuyển sang nhánh "UI"
3. Kiểm tra:
   - ✅ Có README.md mới
   - ✅ Có folder docs/
   - ✅ Có tất cả elite_*.cpp/h files
   - ✅ Có data/schema.sql và data.sql
   - ✅ Có .gitignore
   - ✅ Không có files rác (.o, .log, moc_*, etc.)

---

## Lưu Ý Quan Trọng

⚠️ **BACKUP CODE TRƯỚC KHI CHẠY SCRIPT!**

Script sẽ xóa vĩnh viễn các files. Nếu không chắc chắn:
1. Copy toàn bộ folder auction_app ra nơi khác
2. Chạy script trên bản copy
3. Kiểm tra kết quả
4. Nếu OK, áp dụng cho bản chính

---

## Hỗ Trợ

Nếu gặp vấn đề:
1. Đọc kỹ error message
2. Check PUSH_TO_GITHUB.md
3. Thử cách thủ công (Cách 2)
4. Backup và thử lại

---

**Chúc bạn push thành công! 🚀**
