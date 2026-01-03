QT += core gui widgets network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# Disable deprecated warnings
DEFINES += QT_DEPRECATED_WARNINGS

# Target name
TARGET = elite_auction_app

# Template
TEMPLATE = app

# Source files - ALL files needed
SOURCES += \
    elite_auction_main.cpp \
    elite_main_window.cpp \
    elite_login_window.cpp \
    elite_auction_room.cpp \
    elite_account_window.cpp \
    elite_network_client.cpp \
    elite_dialogs.cpp \
    elite_database.cpp

# Header files - ALL headers
HEADERS += \
    elite_main_window.h \
    elite_login_window.h \
    elite_auction_room.h \
    elite_account_window.h \
    elite_network_client.h \
    elite_dialogs.h \
    elite_database.h

# Resources
RESOURCES += elite_resources.qrc

# Default rules for deployment
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
