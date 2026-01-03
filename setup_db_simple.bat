@echo off
echo ========================================
echo PostgreSQL Database Setup
echo ========================================
echo.

REM Prompt for PostgreSQL path
set /p PGPATH="Enter PostgreSQL bin path (e.g., C:\Program Files\PostgreSQL\16\bin): "

REM Check if path exists
if not exist "%PGPATH%\psql.exe" (
    echo ERROR: psql.exe not found in %PGPATH%
    echo Please check the path and try again.
    pause
    exit /b 1
)

echo.
echo Found PostgreSQL at: %PGPATH%
echo.

REM Get password
set /p PGPASSWORD="Enter PostgreSQL password for user postgres: "
echo.

REM Create database
echo Creating database...
"%PGPATH%\createdb.exe" -U postgres auction_db 2>nul
if errorlevel 1 (
    echo Database might already exist, continuing...
) else (
    echo Database created!
)
echo.

REM Import schema
echo Importing schema...
"%PGPATH%\psql.exe" -U postgres -d auction_db -f data\schema.sql
if errorlevel 1 (
    echo ERROR: Failed to import schema
    pause
    exit /b 1
)
echo Schema imported!
echo.

REM Import data
echo Importing data...
"%PGPATH%\psql.exe" -U postgres -d auction_db -f data\data.sql
if errorlevel 1 (
    echo ERROR: Failed to import data
    pause
    exit /b 1
)
echo Data imported!
echo.

REM Verify
echo Verifying...
"%PGPATH%\psql.exe" -U postgres -d auction_db -c "SELECT COUNT(*) FROM auction_rooms;"
echo.

echo ========================================
echo Setup completed successfully!
echo ========================================
echo.
echo Next steps:
echo 1. Edit elite_main_window.cpp line 20
echo 2. Change password to: %PGPASSWORD%
echo 3. Run: build_elite_ui.bat
echo 4. Run: run_elite_ui.bat
echo.
pause
