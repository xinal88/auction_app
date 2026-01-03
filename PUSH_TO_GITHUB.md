# Hướng Dẫn Push Lên GitHub

## Bước 1: Clean Up (Thực hiện thủ công)

### Xóa các file không cần thiết:

```bash
# Trong folder auction_app, xóa các file sau:

# Object files
*.o
moc_*.cpp
moc_*.o
moc_predefs.h

# Makefiles
Makefile.*

# Log files
*.log
.qmake.stash

# Test files
test_*.cpp
test_*.pro

# Old UI files
modern_auction_*.cpp
modern_auction_*.pro
premium_*.cpp
premium_*.pro
simple_*.cpp
simple_*.pro

# Old .pro files (giữ lại elite_auction_final.pro)
auction_app.pro
auction_client.pro
elite_auction_app.pro
elite_auction_app_simple.pro

# Compiled binaries
auction_client
auction_client_cli
auction_server

# Old documentation (giữ lại những file quan trọng)
BUILD_WINDOWS.md
BUILD.md
CAI_TIEN_UI_DATABASE.md
CLEANUP_*.*
COMPLETE_FIX_SUMMARY.md
COMPLETION_REPORT.md
DATABASE_INTEGRATION.md
DEMO_CLI.md
DIALOGS_UPDATE_COMPLETE.md
DOCS_INDEX.md
DOCUMENTATION_INDEX.md
ELITE_COMPLETION_STATUS.md
ELITE_FIXES_APPLIED.md
FEATURES.md
FINAL_FIX_COMPLETE.md
FINAL_SETUP_GUIDE.md
FIX_BUILD_ERROR.md
HUONG_DAN_CHAY.md
HUONG_DAN_CHAY_CLIENT.md
HUONG_DAN_CHAY_QT_WINDOWS.md
HUONG_DAN_MO_UI.md
HUONG_DAN_MODERN_UI.md
HUONG_DAN_PREMIUM_UI.md
HUONG_DAN_QT_UI.md
LOGIN_FIX_COMPLETE.md
MODERN_UI_*.md
PRE_DEMO_CHECKLIST.md
PREMIUM_*.md
PROJECT_SUMMARY.md
QUICK_DEMO_GUIDE.md
QUICK_FIX.txt
QUICK_REFERENCE_DIALOGS.md
QUICK_START_MODERN_UI.md
QUICK_START_PREMIUM.md
README_FINAL.md
README_SETUP.md
REORGANIZE_*.*
SETUP_GUIDE.md
START_HERE_MODERN_UI.md
START_HERE_PREMIUM.md
START_HERE_WINDOWS.md
SUMMARY_IMPROVEMENTS.md
SUA_LOI_GIAO_DIEN_CUOI_CUNG.md
SUA_LOI_LOGIN_HOAN_TAT.md
TIMER_FEATURE.md
UI_DESIGN_GUIDE.md
WHAT_WAS_DONE.md

# Old build scripts
build_client.sh
build_elite_ui.bat
build_modern_ui.*
build_premium_ui.*
build_ui.bat
run_modern_ui.*
run_premium_ui.*
run_ui.bat
run_server.sh
setup_database.sh
setup_db.sh
find_postgresql.bat
reorganize.bat

# Folders
-p/
build/ (xóa nội dung, giữ folder)
```

## Bước 2: Đổi tên README

```bash
# Xóa README.md cũ
del README.md

# Đổi tên README_NEW.md thành README.md
ren README_NEW.md README.md
```

## Bước 3: Tạo docs folder

```bash
# Tạo folder docs
mkdir docs

# Di chuyển các file documentation quan trọng vào docs/
move BACKEND_HOAN_CHINH.md docs/
move CAI_TIEN_HOAN_CHINH.md docs/
move SETUP_USING_PGADMIN.md docs/
move HUONG_DAN_CHAY_ELITE_QT.md docs/
move QUICK_START_ELITE.md docs/
move ELITE_UI_README.md docs/
move START_HERE.md docs/
move BUILD_FINAL_INSTRUCTIONS.md docs/
move SETUP_WINDOWS_COMPLETE.md docs/
move HOW_TO_OPEN_IN_QT.md docs/
move HUONG_DAN_SETUP_DATABASE.md docs/
move QUICK_START.md docs/
```

## Bước 4: Push lên GitHub

### 4.1. Kiểm tra remote
```bash
git remote -v
```

Nếu chưa có remote, thêm:
```bash
git remote add origin https://github.com/mtrung12/auction_app.git
```

### 4.2. Tạo nhánh UI mới
```bash
# Đảm bảo đang ở folder auction_app
cd auction_app

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

# Tạo và checkout nhánh UI
git checkout -b UI

# Push lên GitHub
git push -u origin UI
```

### 4.3. Nếu gặp lỗi authentication

Sử dụng Personal Access Token:
```bash
# Khi được hỏi password, nhập Personal Access Token thay vì password
# Hoặc cấu hình:
git config --global credential.helper store
```

## Bước 5: Verify

Sau khi push, kiểm tra trên GitHub:
1. Vào https://github.com/mtrung12/auction_app
2. Chuyển sang nhánh "UI"
3. Kiểm tra files đã được push đúng

## Files Quan Trọng Cần Giữ

### Source Code
- elite_*.cpp
- elite_*.h
- elite_auction_final.pro
- elite_resources.qrc

### Database
- data/schema.sql
- data/data.sql

### Server (nếu cần)
- src/server/*
- src/client_cli/*

### Documentation
- README.md (mới)
- docs/*.md
- yêu cầu project.txt
- use_case_diagram.png
- UseCase Diagram.asta

### Scripts
- setup_db_simple.bat
- setup_database_windows.bat
- check_postgresql.bat
- run_elite_ui.bat

### Config
- .gitignore

## Cấu Trúc Folder Sau Khi Clean

```
auction_app/
├── .git/
├── .gitignore
├── README.md
├── elite_auction_final.pro
├── elite_*.cpp/h
├── data/
│   ├── schema.sql
│   └── data.sql
├── docs/
│   └── *.md
├── src/
│   ├── server/
│   └── client_cli/
├── setup_*.bat
└── yêu cầu project.txt
```

## Troubleshooting

### Nếu git push bị reject
```bash
# Pull trước
git pull origin UI --rebase

# Sau đó push lại
git push origin UI
```

### Nếu muốn force push (cẩn thận!)
```bash
git push -f origin UI
```

### Nếu có conflict
```bash
# Resolve conflicts manually
# Sau đó:
git add .
git rebase --continue
git push origin UI
```

---

**Lưu ý**: Backup code trước khi thực hiện cleanup!
