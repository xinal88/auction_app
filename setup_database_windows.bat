@echo off
echo ========================================
echo Setup PostgreSQL Database for Auction App
echo ========================================
echo.

REM Find PostgreSQL installation
set PGPATH=
if exist "C:\Program Files\PostgreSQL\16\bin\psql.exe" set PGPATH=C:\Program Files\PostgreSQL\16\bin
if exist "C:\Program Files\PostgreSQL\15\bin\psql.exe" set PGPATH=C:\Program Files\PostgreSQL\15\bin
if exist "C:\Program Files\PostgreSQL\14\bin\psql.exe" set PGPATH=C:\Program Files\PostgreSQL\14\bin
if exist "C:\Program Files\PostgreSQL\13\bin\psql.exe" set PGPATH=C:\Program Files\PostgreSQL\13\bin
if exist "C:\Program Files\PostgreSQL\12\bin\psql.exe" set PGPATH=C:\Program Files\PostgreSQL\12\bin

if "%PGPATH%"=="" (
    echo ERROR: PostgreSQL not found!
    echo.
    echo Please install PostgreSQL from: https://www.postgresql.org/download/windows/
    echo Or manually set PGPATH in this script.
    echo.
    pause
    exit /b 1
)

echo Found PostgreSQL at: %PGPATH%
echo.

REM Set PostgreSQL bin to PATH temporarily
set PATH=%PGPATH%;%PATH%

REM Get password
set /p PGPASSWORD="Enter PostgreSQL password for user 'postgres': "
echo.

REM Create database
echo Step 1: Creating database 'auction_db'...
"%PGPATH%\createdb.exe" -U postgres auction_db 2>nul
if errorlevel 1 (
    echo Database might already exist, continuing...
) else (
    echo Database created successfully!
)
echo.

REM Import schema
echo Step 2: Importing schema...
"%PGPATH%\psql.exe" -U postgres -d auction_db -f data\schema.sql
if errorlevel 1 (
    echo ERROR: Failed to import schema!
    pause
    exit /b 1
)
echo Schema imported successfully!
echo.

REM Import data
echo Step 3: Importing demo data...
"%PGPATH%\psql.exe" -U postgres -d auction_db -f data\data.sql
if errorlevel 1 (
    echo ERROR: Failed to import data!
    pause
    exit /b 1
)
echo Demo data imported successfully!
echo.

REM Verify
echo Step 4: Verifying database...
"%PGPATH%\psql.exe" -U postgres -d auction_db -c "SELECT COUNT(*) as room_count FROM auction_rooms;"
"%PGPATH%\psql.exe" -U postgres -d auction_db -c "SELECT COUNT(*) as item_count FROM auction_items;"
echo.

echo ========================================
echo Database setup completed successfully!
echo ========================================
echo.
echo Database: auction_db
echo Rooms: 5
echo Items: 15+
echo Users: 10
echo.
echo Next steps:
echo 1. Open elite_main_window.cpp
echo 2. Update password on line ~20
echo 3. Run: build_elite_ui.bat
echo 4. Run: run_elite_ui.bat
echo.
pause
