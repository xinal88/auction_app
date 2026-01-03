# 🚀 Quick Start - Premium Modern Auction UI

## ⚡ 30-Second Start

### Using Qt Creator (Recommended)
1. Open Qt Creator
2. File → Open → `premium_modern_auction.pro`
3. Click Run ▶️

### Using Command Line

**Windows:**
```powershell
cd auction_app
.\build_premium_ui.bat && .\run_premium_ui.bat
```

**Linux/macOS:**
```bash
cd auction_app && chmod +x *.sh && ./build_premium_ui.sh && ./run_premium_ui.sh
```

## 🎮 First Steps

1. **Login**: Enter any username/password → Click "Sign In"
2. **Explore**: View featured auction items on home screen
3. **Join Auction**: Click "View Auction" on any item card
4. **Place Bid**: 
   - Enter amount or use +10K/+50K/+100K buttons
   - Click "Place Bid"
5. **Chat**: Type message and press Enter
6. **Account**: Click "Account" button to manage balance

## ✨ Key Features

- ⏱️ **Real-time countdown** with 30-second warning
- 💬 **Live chat** with participants
- 💰 **Account management** (deposit/redeem)
- 🎨 **Modern minimalist** design
- 📱 **Responsive** three-column layout

## 📋 Requirements

- Qt 5.12+ or 6.x
- C++ compiler (MinGW/MSVC/g++/Clang)
- 1200x800+ screen resolution

## 🐛 Troubleshooting

**"qmake not found"**
```bash
# Add Qt to PATH
export PATH=/path/to/Qt/6.x/bin:$PATH  # Linux/macOS
set PATH=C:\Qt\6.x\mingw_64\bin;%PATH%  # Windows
```

**Build fails**
```bash
rm -rf build && ./build_premium_ui.sh  # Clean rebuild
```

## 📚 Full Documentation

See `PREMIUM_UI_README.md` for complete guide.

---

**Enjoy premium auction experience! 🏛️✨**

