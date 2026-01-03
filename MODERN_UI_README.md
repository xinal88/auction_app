# 🎨 Modern Auction Application UI

A **minimalist, professional, and elegant** Qt-based auction application with a premium design system.

## ✨ Features

### 🎯 Design Principles
- **Modern minimalism** with generous white space
- **Card-based layout** with rounded corners and soft shadows
- **Subtle animations** for bids, countdown, and notifications
- **Focus on clarity, speed, and trust**

### 🎨 Design System
- **Typography**: Inter/SF Pro with clear hierarchy
- **Colors**:
  - Primary: Indigo/Deep Blue (#4F46E5) - main actions
  - Success: Green (#10B981) - successful bids
  - Warning: Amber (#F59E0B) - last 30-second warning
  - Danger: Red (#EF4444) - errors and outbid states
  - Neutral: White/light gray backgrounds

### 📱 Core Screens

#### 1. **Welcome/Authentication Screen**
- Clean login and registration forms
- Tabbed interface for easy switching
- Real-time validation and feedback
- Premium hero section with value proposition

#### 2. **Home/Explore Screen**
- Search bar with quick filters (Live, Upcoming, My Rooms)
- Featured auction rooms grid
- Item cards with status badges (LIVE, UPCOMING, SOLD)
- User info and balance display
- Quick access to account and logout

#### 3. **Auction Room Screen** (Three-Column Layout)
- **Left Column**: Upcoming item queue
- **Center Column**: 
  - Current item with large image
  - Real-time countdown timer
  - Current price display
  - Bid input with quick increment buttons (+10K, +50K, +100K)
  - Place Bid and Buy Now buttons
- **Right Column**:
  - Participants list with host indicator
  - Live chat with real-time messages

#### 4. **Account Management Screen**
- Profile information display
- Virtual balance with large, clear display
- Deposit money with quick amount buttons
- Redeem money functionality
- Auction history table

### ⚡ Special Features

#### Countdown Timer
- Large, readable display
- **Automatic warning** when 30 seconds remain (changes to amber)
- **Auto-reset** to 30 seconds when new bid arrives in final 30 seconds
- Emits signals for timeout and warning threshold

#### Status Badges
- **LIVE**: Red badge with pulsing dot
- **UPCOMING**: Blue badge
- **SOLD**: Gray badge
- **WARNING**: Amber badge for urgent states

#### Interactive Elements
- Hover effects on all buttons and cards
- Click animations
- Real-time status updates
- Toast notifications for actions

## 🚀 Quick Start

### Prerequisites
- Qt 5.12+ or Qt 6.x
- C++11 compiler (GCC, Clang, or MSVC)
- qmake or Qt Creator

### Build Instructions

#### Option 1: Using Qt Creator (Recommended)
1. Open Qt Creator
2. File → Open File or Project
3. Navigate to `auction_app/modern_auction_app.pro`
4. Click "Configure Project"
5. Click the green "Run" button (▶️)

#### Option 2: Using Command Line (Windows)
```powershell
cd auction_app
qmake modern_auction_app.pro
mingw32-make
.\build\modern_auction_app.exe
```

#### Option 3: Using Command Line (Linux/macOS)
```bash
cd auction_app
qmake modern_auction_app.pro
make
./build/modern_auction_app
```

### One-Line Build & Run
```bash
# Windows (PowerShell)
cd auction_app && qmake modern_auction_app.pro && mingw32-make && .\build\modern_auction_app.exe

# Linux/macOS
cd auction_app && qmake modern_auction_app.pro && make && ./build/modern_auction_app
```

## 📖 Usage Guide

### 1. Login/Register
- Launch the application
- Choose "Login" or "Register" tab
- **Login**: Enter username and password
- **Register**: Fill in all fields (username, password, email, bank info)
- Click the respective button

### 2. Explore Auctions
- Browse featured auction items
- Use filters: All, Live, Upcoming, My Rooms
- Click on any item card to join the auction room
- Click "Create Room" to start your own auction

### 3. Participate in Auction
- View current item details and countdown
- Enter bid amount or use quick increment buttons
- Click "Place Bid" to submit your bid
- Click "Buy Now" for instant purchase
- Chat with other participants in real-time
- View upcoming items in the queue

### 4. Manage Account
- Click "Account" button in top bar
- View your profile and current balance
- Deposit money using quick amount buttons or custom amount
- Redeem money from your virtual balance
- View your auction history

## 🎯 Demo Features

The application includes **demo data** for testing:
- Sample auction items with different statuses
- Mock participants and chat messages
- Simulated login (any username/password works)
- Starting balance of 5,000,000 VND
- Pre-populated auction history

## 🏗️ Architecture

### Single-File Design
All code is in `modern_auction_app.cpp` for easy deployment and review:
- **Design System**: Colors, fonts, spacing constants
- **Custom Widgets**: Badge, Card, CountdownTimer
- **Screens**: WelcomeScreen, HomeScreen, AuctionRoomScreen, AccountScreen
- **Main App**: ModernAuctionApp with navigation and state management

### Key Components
```cpp
DesignSystem          // Color palette, typography, spacing
Badge                 // Status indicators (LIVE, UPCOMING, SOLD)
Card                  // Container with rounded corners and shadow
CountdownTimer        // Real-time countdown with warning
WelcomeScreen         // Login/Register
HomeScreen            // Browse auctions
AuctionRoomScreen     // Three-column bidding interface
AccountScreen         // Balance and history management
ModernAuctionApp      // Main window with navigation
```

## 🎨 Customization

### Change Colors
Edit the `DesignSystem` namespace in `modern_auction_app.cpp`:
```cpp
const QString PRIMARY = "#4F46E5";  // Change to your brand color
const QString SUCCESS = "#10B981";  // Change success color
// ... etc
```

### Adjust Spacing
```cpp
const int SPACING_MD = 16;  // Increase for more space
const int RADIUS_LG = 12;   // Increase for rounder corners
```

### Modify Timer Duration
```cpp
CountdownTimer *timer = new CountdownTimer(180);  // 180 seconds = 3 minutes
```

## 📦 File Structure
```
auction_app/
├── modern_auction_app.cpp      # Main application (all code)
├── modern_auction_app.pro      # Qt project file
├── MODERN_UI_README.md         # This file
└── build/                      # Build output (created automatically)
    └── modern_auction_app      # Executable
```

## 🐛 Troubleshooting

### Qt not found
```bash
# Add Qt to PATH (Windows example)
set PATH=C:\Qt\6.10.1\mingw_64\bin;%PATH%
```

### Build errors
```bash
# Clean and rebuild
qmake modern_auction_app.pro
make clean
make
```

### Application doesn't start
- Check Qt version (5.12+ or 6.x required)
- Ensure all Qt DLLs are in PATH
- Run from Qt Creator for better error messages

## 🎓 Learning Resources

- **Qt Documentation**: https://doc.qt.io/
- **Qt Widgets**: https://doc.qt.io/qt-6/qtwidgets-index.html
- **Qt Layouts**: https://doc.qt.io/qt-6/layout.html
- **Qt Signals & Slots**: https://doc.qt.io/qt-6/signalsandslots.html

## 📝 License

This is a student project for HUST Network Programming course.

## 👨‍💻 Author

Created for HUST Auction Application Project
Version 2.0 - Modern UI Edition

---

**Enjoy your premium auction experience! 🏛️✨**

