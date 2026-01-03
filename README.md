# 🔨 AuctionHub - Online Auction Application

Modern Qt-based auction application with real-time bidding, chat, and PostgreSQL database integration.

## 📋 Features

### Core Features
- ✅ **User Management**: Register, Login, Profile management
- ✅ **Money Management**: Deposit, Withdraw, Bank information
- ✅ **Auction Rooms**: Create, Join, Browse with search and filters
- ✅ **Real-time Bidding**: Place bids with validation and balance checking
- ✅ **Buy Now**: Instant purchase option
- ✅ **Live Chat**: Real-time messaging in auction rooms
- ✅ **Countdown Timer**: Visual timer for each auction
- ✅ **Activity History**: Transaction logs and bid history
- ✅ **Image Support**: Load product images from URLs

### Technical Features
- Modern Qt 6 UI with custom styling
- PostgreSQL database integration
- Real-time data updates
- Responsive layout
- Demo mode (works without database)
- Error handling and validation

## 🚀 Quick Start

### Prerequisites
- Qt 6.x (tested with 6.10.1)
- MinGW or MSVC compiler
- PostgreSQL 12+ (optional for full features)

### Build & Run

#### Windows
```bash
# 1. Open Qt Creator
# 2. Open elite_auction_final.pro
# 3. Build (Ctrl+B)
# 4. Run (Ctrl+R)
```

#### Database Setup (Optional)
```bash
# 1. Create database
createdb -U postgres auction_db

# 2. Run schema
psql -U postgres -d auction_db -f data/schema.sql

# 3. Load demo data
psql -U postgres -d auction_db -f data/data.sql

# 4. Update password in elite_main_window.cpp line 25
```

Or use pgAdmin 4 GUI - see `SETUP_USING_PGADMIN.md`

## 📁 Project Structure

```
auction_app/
├── elite_*.cpp/h           # Elite UI source files
├── elite_auction_final.pro # Qt project file
├── data/
│   ├── schema.sql         # Database schema
│   └── data.sql           # Demo data
├── src/
│   ├── server/            # C server implementation
│   └── client_cli/        # CLI client
├── docs/                  # Documentation
└── README.md
```

## 🎯 Usage

### 1. Login/Register
- Click "Sign up" to create account
- Or login with existing credentials
- Demo mode: any credentials work

### 2. Explore Auctions
- Browse auction rooms
- Search by name
- Filter by Live/Upcoming status
- Click room to join

### 3. Bidding
- Enter bid amount (min: current + 10,000 đ)
- Click "Place Bid"
- Or use quick bid buttons (+50K, +100K, +500K)

### 4. Buy Now
- Click "Buy Now" button
- Confirm purchase
- Balance deducted automatically

### 5. Manage Money
- Go to Account page
- Deposit: Add funds to balance
- Withdraw: Remove funds (requires bank info)
- Update bank information

### 6. Chat
- Type message in chat box
- Click send or press Enter
- Messages saved to database

## 🗄️ Database Schema

### Main Tables
- **users**: User accounts and balances
- **auction_rooms**: Auction room information
- **auction_items**: Items for auction
- **bids**: Bid history
- **chat_messages**: Chat logs
- **activity_logs**: Transaction history

See `data/schema.sql` for complete schema.

## 📚 Documentation

- `BACKEND_HOAN_CHINH.md` - Complete backend documentation (Vietnamese)
- `CAI_TIEN_HOAN_CHINH.md` - UI improvements documentation (Vietnamese)
- `SETUP_USING_PGADMIN.md` - Database setup with pgAdmin
- `HUONG_DAN_CHAY_ELITE_QT.md` - Running guide (Vietnamese)
- `QUICK_START_ELITE.md` - Quick start guide

## 🛠️ Development

### Build from Source
```bash
qmake elite_auction_final.pro
make
```

### Database Connection
Edit `elite_main_window.cpp` line 25:
```cpp
db->connectToDatabase("localhost", "auction_db", "postgres", "YOUR_PASSWORD");
```

### Demo Mode
App works without database connection:
- Uses demo data
- All UI features functional
- No data persistence

## 🎨 UI Components

- **Login Window**: Modern authentication UI
- **Main Window**: Browse and search rooms
- **Auction Room**: Live bidding interface
- **Account Window**: Profile and money management
- **Dialogs**: Deposit, Withdraw, Bank info, Create room, Sign up

## 🔧 Troubleshooting

### Database Connection Failed
1. Check PostgreSQL is running
2. Verify database exists: `psql -U postgres -l`
3. Check password in code
4. Ensure libpq.dll is in PATH

### Build Errors
1. Clean build folder
2. Run qmake again
3. Check Qt version (6.x required)
4. Verify all source files present

### UI Issues
1. Check Qt modules: widgets, network, sql
2. Verify stylesheet syntax
3. Check image URLs are accessible

## 📝 Requirements

From `yêu cầu project.txt`:
- ✅ User management and authentication
- ✅ Create and join auction rooms
- ✅ Item management with queue
- ✅ Real-time bidding with validation
- ✅ Buy now functionality
- ✅ Chat in rooms
- ✅ Timer with 30-second warning
- ✅ Transaction logging
- ✅ Activity history
- ✅ Search and filter
- ✅ Deposit/Withdraw money
- ✅ Bank information management

## 🤝 Contributing

This is a university project. For improvements:
1. Fork the repository
2. Create feature branch
3. Commit changes
4. Push to branch
5. Create Pull Request

## 📄 License

University project - HUST (Hanoi University of Science and Technology)

## 👥 Authors

- Student project for Network Programming course
- Qt 6 + PostgreSQL implementation
- Modern UI/UX design

## 🎓 Academic Use

This project demonstrates:
- Socket programming concepts
- Database integration
- Real-time communication
- Modern UI development
- Client-server architecture

---

**Note**: This is an educational project. Not for production use without proper security audits.

## 📞 Support

For issues or questions:
1. Check documentation in `docs/` folder
2. Review troubleshooting section
3. Check database connection
4. Verify Qt installation

---

Made with ❤️ using Qt 6 and PostgreSQL
