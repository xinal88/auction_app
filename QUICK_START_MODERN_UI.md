# 🚀 Quick Start - Modern Auction UI

## ⚡ Fastest Way to Run (Qt Creator)

### Step 1: Open Project
1. Launch **Qt Creator**
2. Click **File → Open File or Project**
3. Navigate to: `auction_app/modern_auction_app.pro`
4. Click **Open**

### Step 2: Configure
1. Qt Creator will ask to configure the project
2. Select your Qt kit (e.g., Desktop Qt 6.10.1 MinGW 64-bit)
3. Click **Configure Project**

### Step 3: Run
1. Click the green **Run** button (▶️) in the bottom-left corner
2. Or press **Ctrl+R** (Windows/Linux) or **Cmd+R** (macOS)
3. The application will build and launch automatically!

**That's it! 🎉**

---

## 🖥️ Command Line (Alternative)

### Windows (PowerShell)
```powershell
cd auction_app
.\build_modern_ui.bat
```

### Linux/macOS
```bash
cd auction_app
chmod +x build_modern_ui.sh
./build_modern_ui.sh
```

---

## 🎮 Using the Application

### 1️⃣ Login
- **Username**: Any username (e.g., "alice")
- **Password**: Any password (demo mode)
- Click **🔐 Sign In**

### 2️⃣ Explore Auctions
- Browse featured items
- Click on any item card to join auction
- Use filters: All, Live, Upcoming

### 3️⃣ Join Auction Room
- View current item and countdown
- Enter bid amount or use quick buttons (+10K, +50K, +100K)
- Click **🔨 Place Bid**
- Or click **⚡ Buy Now** for instant purchase
- Chat with other participants

### 4️⃣ Manage Account
- Click **Account** button in top bar
- View balance: 5,000,000 VND (starting)
- Deposit money using quick buttons
- View auction history

---

## 🎨 Key Features to Try

### ⏱️ Countdown Timer
- Watch the timer count down
- When it reaches **30 seconds**, it turns **amber** (warning)
- In real app, new bids reset timer to 30s

### 💬 Live Chat
- Type messages in the chat box
- Press Enter or click Send
- See messages appear in real-time

### 💰 Quick Bid Increments
- Click **+10K**, **+50K**, or **+100K** buttons
- Amount automatically adds to bid field
- Quick and easy bidding!

### 🎯 Status Badges
- **● LIVE** (Red): Auction is active now
- **UPCOMING** (Blue): Auction starts soon
- **SOLD** (Gray): Auction ended

---

## 📁 Project Structure

```
auction_app/
├── modern_auction_app.cpp      ← All code (single file!)
├── modern_auction_app.pro      ← Qt project file
├── MODERN_UI_README.md         ← Full documentation
├── UI_DESIGN_GUIDE.md          ← Design specifications
├── QUICK_START_MODERN_UI.md    ← This file
├── build_modern_ui.bat         ← Windows build script
├── build_modern_ui.sh          ← Linux/macOS build script
└── build/                      ← Build output (auto-created)
    └── modern_auction_app.exe  ← Executable
```

---

## 🐛 Troubleshooting

### "qmake not found"
**Solution**: Add Qt to your PATH
```powershell
# Windows example
set PATH=C:\Qt\6.10.1\mingw_64\bin;%PATH%
```

### "Cannot find -lQt6Core"
**Solution**: Make sure Qt is properly installed and kit is configured in Qt Creator

### Application doesn't start
**Solution**: 
1. Check Qt version (need 5.12+ or 6.x)
2. Run from Qt Creator for better error messages
3. Check if all Qt DLLs are accessible

### Build errors
**Solution**:
1. Clean build: **Build → Clean All**
2. Rebuild: **Build → Rebuild All**
3. Check compiler output in "Compile Output" tab

---

## 💡 Tips

### Resize Window
- Drag window edges to resize
- Minimum recommended: 1200x800
- Best experience: 1400x900 or larger

### Keyboard Shortcuts
- **Enter** in login password field → Login
- **Enter** in chat input → Send message
- **Ctrl+Q** → Quit application

### Demo Mode
- All data is simulated (no real server needed)
- Login works with any username/password
- Starting balance: 5,000,000 VND
- Sample items and chat messages included

---

## 🎯 Next Steps

### Connect to Real Server
To connect this UI to your actual auction server:

1. Add network client integration
2. Replace demo data with real API calls
3. Implement real-time WebSocket for chat
4. Add authentication with server

See `src/client/network_client.h` in the main project for reference.

### Customize Design
Edit `DesignSystem` namespace in `modern_auction_app.cpp`:
- Change colors
- Adjust spacing
- Modify fonts
- Update border radius

---

## 📚 Documentation

- **Full README**: `MODERN_UI_README.md`
- **Design Guide**: `UI_DESIGN_GUIDE.md`
- **Qt Docs**: https://doc.qt.io/

---

## ✨ Features Showcase

### 🎨 Modern Design
- Minimalist, professional interface
- Card-based layouts
- Soft shadows and rounded corners
- Premium color palette

### ⚡ Real-time Elements
- Live countdown timer
- Instant chat messages
- Dynamic balance updates
- Status badges

### 🎯 User-Friendly
- Clear navigation
- Quick action buttons
- Intuitive layouts
- Helpful feedback messages

---

**Enjoy your premium auction experience! 🏛️**

Need help? Check the full documentation in `MODERN_UI_README.md`

