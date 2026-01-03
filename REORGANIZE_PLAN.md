# Project Reorganization Plan

## New Structure

```
auction_app/
├── bin/                          # Compiled executables
├── data/                         # Database files
│   ├── schema.sql
│   ├── data.sql
│   └── create_user.sql
├── src/
│   ├── common/                   # Shared protocol & utils
│   │   ├── protocol.h
│   │   ├── protocol_header.h
│   │   ├── protocol_payloads.h
│   │   ├── protocol_types.h
│   │   ├── utils.h
│   │   └── utils.c
│   ├── server/                   # Backend server
│   │   ├── handler/
│   │   ├── server.c
│   │   ├── auction_timer.c/h
│   │   ├── client_manager.c/h
│   │   ├── db_adapter.c/h
│   │   └── network_utils.c/h
│   └── client/                   # Frontend client
│       ├── ui/                   # Qt UI files
│       │   ├── elite_login_window.h/cpp
│       │   ├── elite_main_window.h/cpp
│       │   ├── elite_auction_room.h/cpp
│       │   ├── elite_account_window.h/cpp
│       │   ├── elite_dialogs.h/cpp
│       │   ├── elite_network_client.h/cpp
│       │   └── elite_auction_main.cpp
│       └── cli/                  # CLI client (optional)
│           └── cli.c
├── auction_app.pro               # Qt project file
├── elite_resources.qrc           # Qt resources
├── build_ui.bat                  # Build script
├── run_ui.bat                    # Run script
└── README.md                     # Main documentation
```

## Files to Keep

### Elite UI (Current working version):
- elite_login_window.h/cpp
- elite_main_window.h/cpp
- elite_auction_room.h/cpp
- elite_account_window.h/cpp
- elite_dialogs.h/cpp
- elite_network_client.h/cpp
- elite_auction_main.cpp
- elite_resources.qrc

### Backend (from trung folder):
- src/common/* (protocol files)
- src/server/* (server implementation)
- data/* (database files)

### Build files:
- auction_app.pro (new, reorganized)
- build_ui.bat
- run_ui.bat

## Files Deleted

### Documentation (old/redundant):
- All *.md files except README.md
- HUONG_DAN_*.md
- QUICK_START_*.md
- BUILD_*.md
- etc.

### Old UI versions:
- modern_auction_*.cpp/pro
- premium_auction_*.cpp/pro
- simple_auction_*.cpp/pro
- test_qt.cpp/pro

### Compiled files:
- *.o files
- *.log files
- moc_*.cpp/o
- Makefile*
- .qmake.stash

### Old executables:
- auction_client
- auction_server
- auction_client_cli

### Old project files:
- auction_client.pro
- Old .pro files

### Misc:
- UseCase Diagram files
- Old build scripts
- .qtcreator folder
- -p folder

## Next Steps

1. Move Elite UI files to src/client/ui/
2. Update includes in UI files
3. Integrate network_client with protocol
4. Create new README.md
5. Test build
