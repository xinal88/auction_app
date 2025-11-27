# Hướng dẫn Build và Chạy Auction Application

## Yêu cầu hệ thống

### Server (C)
- GCC compiler
- PostgreSQL development libraries (`libpq-dev`)
- pthread library
- Make

### Client (Qt/C++)
- Qt 5 hoặc Qt 6
- Qt Creator (khuyến nghị) hoặc qmake
- C++ compiler (g++/clang)

## Cài đặt Dependencies

### Ubuntu/Debian
```bash
# Server dependencies
sudo apt-get update
sudo apt-get install build-essential libpq-dev postgresql postgresql-contrib

# Client dependencies (Qt)
sudo apt-get install qt5-default qtcreator
```

### Windows
- Cài đặt MinGW hoặc MSVC
- Cài đặt PostgreSQL từ https://www.postgresql.org/download/windows/
- Cài đặt Qt từ https://www.qt.io/download

## Setup Database

1. Khởi động PostgreSQL service:
```bash
sudo service postgresql start
```

2. Tạo database và user:
```bash
sudo -u postgres psql -f data/create_user.sql
sudo -u postgres createdb -O trung auction_db
```

3. Import schema và data:
```bash
psql -U trung -d auction_db -f data/schema.sql
psql -U trung -d auction_db -f data/data.sql
```

## Build Server

```bash
cd auction_app
make clean
make server
```

Hoặc build và chạy luôn:
```bash
make run
```

## Build Client

### Sử dụng Qt Creator
1. Mở Qt Creator
2. File -> Open File or Project
3. Chọn file `.pro` trong thư mục `src/client`
4. Configure project với kit phù hợp
5. Build -> Build Project
6. Run

### Sử dụng command line
```bash
cd src/client
qmake
make
./auction_client  # Linux
# hoặc
auction_client.exe  # Windows
```

## Chạy ứng dụng

### 1. Khởi động Server
```bash
./auction_server
```

Server sẽ lắng nghe trên port 5500.

### 2. Khởi động Client
- Chạy client application
- Nhập server address: `localhost` hoặc `127.0.0.1`
- Port: `5500`
- Đăng nhập hoặc đăng ký tài khoản mới

## Test với dữ liệu mẫu

Database đã có sẵn 10 users test:
- Username: `alice`, `bob`, `charlie`, `david`, `emma`, `frank`, `hannah`, `ian`, `julia`, `kevin`
- Password: `pass123` (cho tất cả)

## Troubleshooting

### Server không kết nối được database
- Kiểm tra PostgreSQL service đang chạy: `sudo service postgresql status`
- Kiểm tra thông tin kết nối trong `src/server/main.c`
- Kiểm tra user và password trong database

### Client không kết nối được server
- Kiểm tra server đang chạy
- Kiểm tra firewall không block port 5500
- Thử kết nối với `127.0.0.1` thay vì `localhost`

### Lỗi compile
- Đảm bảo đã cài đủ dependencies
- Kiểm tra đường dẫn include của PostgreSQL: `pg_config --includedir`
- Với Qt, đảm bảo đã chọn đúng kit trong Qt Creator

## Cấu trúc Project

```
auction_app/
├── src/
│   ├── server/          # Server C code
│   │   ├── main.c
│   │   ├── server.c
│   │   ├── handlers.c
│   │   ├── session_manager.c
│   │   └── db_adapter.c
│   ├── client/          # Client Qt code
│   │   ├── main.cpp
│   │   ├── network_client.cpp
│   │   ├── login_window.cpp
│   │   └── main_window.cpp
│   └── common/          # Shared protocol definitions
│       ├── protocol.h
│       └── utils.c
├── data/                # Database scripts
│   ├── schema.sql
│   └── data.sql
└── Makefile            # Server build file
```

## Logs

- Server log: `server.log` (trong thư mục chạy server)
- Client log: `client.log` (trong thư mục chạy client)
