QT += core gui network widgets

TARGET = auction_client
TEMPLATE = app

CONFIG += c++11

# Directories
COMMON_DIR = ../common

# Include paths
INCLUDEPATH += $$COMMON_DIR

# Source files
SOURCES += \
    main.cpp \
    network_client.cpp \
    login_window.cpp \
    main_window.cpp \
    client_logger.cpp

# Header files
HEADERS += \
    network_client.h \
    login_window.h \
    main_window.h \
    client_logger.h \
    $$COMMON_DIR/protocol.h \
    $$COMMON_DIR/protocol_header.h \
    $$COMMON_DIR/protocol_types.h \
    $$COMMON_DIR/protocol_payloads.h \
    $$COMMON_DIR/protocol_helpers.h

# Default rules for deployment
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
