@echo off
echo ========================================
echo Checking PostgreSQL Installation
echo ========================================
echo.

REM Check common PostgreSQL installation paths
echo Searching for PostgreSQL...
echo.

set FOUND=0

if exist "C:\Program Files\PostgreSQL\16\bin\psql.exe" (
    echo [FOUND] PostgreSQL 16: C:\Program Files\PostgreSQL\16\bin
    set FOUND=1
)

if exist "C:\Program Files\PostgreSQL\15\bin\psql.exe" (
    echo [FOUND] PostgreSQL 15: C:\Program Files\PostgreSQL\15\bin
    set FOUND=1
)

if exist "C:\Program Files\PostgreSQL\14\bin\psql.exe" (
    echo [FOUND] PostgreSQL 14: C:\Program Files\PostgreSQL\14\bin
    set FOUND=1
)

if exist "C:\Program Files\PostgreSQL\13\bin\psql.exe" (
    echo [FOUND] PostgreSQL 13: C:\Program Files\PostgreSQL\13\bin
    set FOUND=1
)

if exist "C:\Program Files\PostgreSQL\12\bin\psql.exe" (
    echo [FOUND] PostgreSQL 12: C:\Program Files\PostgreSQL\12\bin
    set FOUND=1
)

echo.

if "%FOUND%"=="0" (
    echo ========================================
    echo PostgreSQL NOT FOUND!
    echo ========================================
    echo.
    echo Please install PostgreSQL:
    echo 1. Download from: https://www.postgresql.org/download/windows/
    echo 2. Run the installer
    echo 3. Remember the password you set for postgres user
    echo 4. Run this script again to verify
    echo.
) else (
    echo ========================================
    echo PostgreSQL is installed!
    echo ========================================
    echo.
    echo Next step: Run setup_database_windows.bat
    echo.
)

pause
