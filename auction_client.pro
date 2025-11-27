QT += core gui network widgets

TARGET = auction_client
TEMPLATE = app

CONFIG += c++11

SOURCES += \
    src/client/main.cpp \
    src/client/network_client.cpp \
    src/client/login_window.cpp \
    src/client/main_window.cpp \
    src/client/client_logger.cpp

HEADERS += \
    src/client/network_client.h \
    src/client/login_window.h \
    src/client/main_window.h \
    src/client/client_logger.h \
    src/common/protocol.h \
    src/common/protocol_header.h \
    src/common/protocol_types.h \
    src/common/protocol_payloads.h \
    src/common/protocol_helpers.h

INCLUDEPATH += src/common

# Windows specific
win32 {
    LIBS += -lws2_32
}

# Unix specific
unix {
    QMAKE_CXXFLAGS += -std=c++11
}
