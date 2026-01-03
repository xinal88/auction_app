# Manual Reorganization Instructions

Do đường dẫn có ký tự đặc biệt, bạn cần reorganize thủ công.

---

## Bước 1: Tạo cấu trúc thư mục

Trong Windows Explorer, tạo folder:
```
auction_app/src/client/ui/
auction_app/bin/
```

---

## Bước 2: Di chuyển Elite UI files

Di chuyển các files sau từ `auction_app/` vào `auction_app/src/client/ui/`:

- [x] elite_login_window.h
- [x] elite_login_window.cpp
- [x] elite_main_window.h
- [x] elite_main_window.cpp
- [x] elite_auction_room.h
- [x] elite_auction_room.cpp
- [x] elite_account_window.h
- [x] elite_account_window.cpp
- [x] elite_dialogs.h
- [x] elite_dialogs.cpp
- [x] elite_network_client.h
- [x] elite_network_client.cpp
- [x] elite_auction_main.cpp

---

## Bước 3: Xóa files không cần thiết

### Documentation files (xóa tất cả .md trừ README.md):
- BUILD_WINDOWS.md
- BUILD.md
- COMPLETION_REPORT.md
- DATABASE_INTEGRATION.md
- DEMO_CLI.md
- DIALOGS_UPDATE_COMPLETE.md
- DOCS_INDEX.md
- ELITE_COMPLETION_STATUS.md
- ELITE_FIXES_APPLIED.md
- ELITE_UI_README.md
- FEATURES.md
- FINAL_FIX_COMPLETE.md
- HOW_TO_OPEN_IN_QT.md
- HUONG_DAN_*.md (tất cả)
- MODERN_UI_*.md
- PREMIUM_*.md
- PRE_DEMO_CHECKLIST.md
- PROJECT_SUMMARY.md
- QUICK_*.md (trừ REORGANIZE_PLAN.md tạm thời)
- SETUP_GUIDE.md
- START_HERE_*.md
- TIMER_FEATURE.md
- UI_DESIGN_GUIDE.md

### Old UI files:
- modern_auction_ui.cpp
- modern_auction_app.cpp
- modern_auction_app.pro
- premium_auction_ui.cpp
- premium_auction_ui.pro
- premium_modern_auction.cpp
- premium_modern_auction.pro
- simple_auction_main.cpp
- simple_auction_client.pro

### Test files:
- test_qt.cpp
- test_qt.pro
- test_elite_compile.cpp

### Compiled files:
- *.o (tất cả)
- *.log (tất cả)
- moc_*.cpp
- moc_*.o
- moc_predefs.h

### Build files:
- Makefile
- Makefile.cli
- Makefile.win
- .qmake.stash

### Old executables:
- auction_client
- auction_server
- auction_client_cli

### Old project files:
- auction_client.pro
- elite_auction_app.pro (đã thay bằng auction_app.pro)

### Old scripts:
- build_client.sh
- build_modern_ui.bat/sh
- build_premium_ui.bat/sh
- run_modern_ui.bat/sh
- run_premium_ui.bat/sh
- run_server.sh
- setup_database.sh
- setup_db.sh

### Misc:
- UseCase Diagram.asta
- UseCase Diagram.asta.lock
- use_case_diagram.png
- yêu cầu project.txt

### Folders:
- -p/
- .qtcreator/

---

## Bước 4: Cập nhật includes trong UI files

Sau khi move files, cần update includes:

### Trong tất cả UI files, thay đổi:
```cpp
// Old
#include "elite_login_window.h"

// New (nếu cần)
#include "elite_login_window.h"  // Vẫn giữ nguyên vì .pro đã set INCLUDEPATH
```

Không cần thay đổi includes vì `.pro` file đã set:
```qmake
INCLUDEPATH += src/client/ui \
               src/common
```

---

## Bước 5: Cập nhật build scripts

### build_ui.bat:
```batch
@echo off
echo Building AuctionHub...

REM Clean
if exist Makefile del Makefile
if exist bin\AuctionHub.exe del bin\AuctionHub.exe

REM Generate Makefile
qmake auction_app.pro

REM Build
mingw32-make

echo.
if exist bin\AuctionHub.exe (
    echo Build successful!
    echo Executable: bin\AuctionHub.exe
) else (
    echo Build failed!
)
pause
```

### run_ui.bat:
```batch
@echo off
if exist bin\AuctionHub.exe (
    echo Starting AuctionHub...
    start bin\AuctionHub.exe
) else (
    echo AuctionHub.exe not found!
    echo Please build first using build_ui.bat
    pause
)
```

---

## Bước 6: Verify cấu trúc cuối cùng

```
auction_app/
├── bin/
├── data/
│   ├── schema.sql
│   ├── data.sql
│   └── create_user.sql
├── src/
│   ├── common/
│   │   ├── protocol.h
│   │   ├── protocol_header.h
│   │   ├── protocol_payloads.h
│   │   ├── protocol_types.h
│   │   ├── utils.h
│   │   └── utils.c
│   ├── server/
│   │   ├── handler/
│   │   ├── server.c
│   │   ├── auction_timer.c/h
│   │   ├── client_manager.c/h
│   │   ├── db_adapter.c/h
│   │   └── network_utils.c/h
│   └── client/
│       ├── ui/
│       │   ├── elite_login_window.h/cpp
│       │   ├── elite_main_window.h/cpp
│       │   ├── elite_auction_room.h/cpp
│       │   ├── elite_account_window.h/cpp
│       │   ├── elite_dialogs.h/cpp
│       │   ├── elite_network_client.h/cpp
│       │   └── elite_auction_main.cpp
│       ├── main_window.ui
│       └── login_window.ui
├── auction_app.pro
├── elite_resources.qrc
├── build_ui.bat
├── run_ui.bat
└── README.md
```

---

## Bước 7: Test build

1. Mở Qt Creator
2. Open Project: `auction_app.pro`
3. Configure với Qt kit
4. Build (Ctrl + B)
5. Run (Ctrl + R)

Hoặc dùng command line:
```bash
qmake auction_app.pro
mingw32-make
bin\AuctionHub.exe
```

---

## ✅ Checklist

- [ ] Tạo folders: src/client/ui/, bin/
- [ ] Move 13 Elite UI files vào src/client/ui/
- [ ] Xóa tất cả .md files (trừ README.md)
- [ ] Xóa old UI files (modern, premium, simple)
- [ ] Xóa test files
- [ ] Xóa compiled files (*.o, *.log, moc_*)
- [ ] Xóa old build files (Makefile*, .qmake.stash)
- [ ] Xóa old executables
- [ ] Xóa old .pro files
- [ ] Xóa old scripts
- [ ] Xóa misc files (diagrams, etc.)
- [ ] Xóa folders (-p, .qtcreator)
- [ ] Update build_ui.bat
- [ ] Update run_ui.bat
- [ ] Test build in Qt Creator
- [ ] Test run application

---

## 🎉 Done!

Sau khi hoàn thành, project sẽ có cấu trúc clean, organized và ready for development!
