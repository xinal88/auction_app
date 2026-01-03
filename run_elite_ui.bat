@echo off
echo ========================================
echo Running Elite Auction UI
echo ========================================

if exist release\elite_auction_app.exe (
    echo Starting application...
    start release\elite_auction_app.exe
) else (
    echo Application not found!
    echo Please build the application first using build_elite_ui.bat
    pause
)
