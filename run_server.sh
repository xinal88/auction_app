#!/bin/bash

echo "=========================================="
echo "  Starting Auction Server"
echo "=========================================="
echo ""

# Check if PostgreSQL is running
if ! pgrep -x "postgres" > /dev/null; then
    echo "⚠️  PostgreSQL is not running!"
    echo "Starting PostgreSQL..."
    sudo service postgresql start
    sleep 2
fi

# Check if database exists
if ! psql -U trung -lqt | cut -d \| -f 1 | grep -qw auction_db; then
    echo "⚠️  Database 'auction_db' not found!"
    echo "Please run setup_database.sh first"
    exit 1
fi

# Build server if not exists or source changed
if [ ! -f "auction_server" ] || [ "src/server/server.c" -nt "auction_server" ]; then
    echo "Building server..."
    make clean
    make server
    if [ $? -ne 0 ]; then
        echo "❌ Build failed!"
        exit 1
    fi
    echo "✅ Build successful!"
    echo ""
fi

# Run server
echo "Starting server on port 5500..."
echo "Press Ctrl+C to stop"
echo ""
./auction_server
