@echo off
echo ========================================
echo Finishing cleanup...
echo ========================================
echo.

REM Rename README
echo [1/3] Renaming README...
if exist README_NEW.md (
    del /Q README.md 2>nul
    ren README_NEW.md README.md
    echo Done!
) else (
    echo README_NEW.md not found, skipping...
)

REM Create docs folder
echo [2/3] Creating docs folder...
if not exist docs mkdir docs
echo Done!

REM Move documentation
echo [3/3] Moving documentation to docs...
if exist BACKEND_HOAN_CHINH.md move BACKEND_HOAN_CHINH.md docs\ 2>nul
if exist CAI_TIEN_HOAN_CHINH.md move CAI_TIEN_HOAN_CHINH.md docs\ 2>nul
if exist SETUP_USING_PGADMIN.md move SETUP_USING_PGADMIN.md docs\ 2>nul
if exist HUONG_DAN_CHAY_ELITE_QT.md move HUONG_DAN_CHAY_ELITE_QT.md docs\ 2>nul
if exist QUICK_START_ELITE.md move QUICK_START_ELITE.md docs\ 2>nul
if exist ELITE_UI_README.md move ELITE_UI_README.md docs\ 2>nul
if exist START_HERE.md move START_HERE.md docs\ 2>nul
if exist BUILD_FINAL_INSTRUCTIONS.md move BUILD_FINAL_INSTRUCTIONS.md docs\ 2>nul
if exist SETUP_WINDOWS_COMPLETE.md move SETUP_WINDOWS_COMPLETE.md docs\ 2>nul
if exist HOW_TO_OPEN_IN_QT.md move HOW_TO_OPEN_IN_QT.md docs\ 2>nul
if exist HUONG_DAN_SETUP_DATABASE.md move HUONG_DAN_SETUP_DATABASE.md docs\ 2>nul
if exist QUICK_START.md move QUICK_START.md docs\ 2>nul
if exist CLEANUP_MANUAL.md move CLEANUP_MANUAL.md docs\ 2>nul
echo Done!

echo.
echo ========================================
echo Cleanup completed successfully!
echo ========================================
echo.
echo Project structure:
echo   auction_app/
echo   ├── README.md (new)
echo   ├── elite_*.cpp/h
echo   ├── data/
echo   ├── docs/ (new)
echo   └── src/
echo.
echo Next steps:
echo   1. git status
echo   2. git add .
echo   3. git commit -m "feat: Complete Elite UI with full backend"
echo   4. git checkout -b UI
echo   5. git push -u origin UI
echo.
pause
