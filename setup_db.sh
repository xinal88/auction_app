#!/bin/bash

# Script to setup PostgreSQL database for Auction Application

echo "=========================================="
echo "  Auction App - Database Setup Script"
echo "=========================================="
echo ""

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Database configuration
DB_NAME="auction_db"
DB_USER="trung"
DB_PASS="123"

echo -e "${YELLOW}Step 1: Creating database user...${NC}"
sudo -u postgres psql -c "DROP ROLE IF EXISTS $DB_USER;"
sudo -u postgres psql -c "CREATE ROLE $DB_USER WITH LOGIN SUPERUSER PASSWORD '$DB_PASS';"

if [ $? -eq 0 ]; then
    echo -e "${GREEN}✓ User created successfully${NC}"
else
    echo -e "${RED}✗ Failed to create user${NC}"
    exit 1
fi

echo ""
echo -e "${YELLOW}Step 2: Creating database...${NC}"
sudo -u postgres psql -c "DROP DATABASE IF EXISTS $DB_NAME;"
sudo -u postgres psql -c "CREATE DATABASE $DB_NAME OWNER $DB_USER;"

if [ $? -eq 0 ]; then
    echo -e "${GREEN}✓ Database created successfully${NC}"
else
    echo -e "${RED}✗ Failed to create database${NC}"
    exit 1
fi

echo ""
echo -e "${YELLOW}Step 3: Importing schema...${NC}"
PGPASSWORD=$DB_PASS psql -U $DB_USER -d $DB_NAME -f data/schema.sql

if [ $? -eq 0 ]; then
    echo -e "${GREEN}✓ Schema imported successfully${NC}"
else
    echo -e "${RED}✗ Failed to import schema${NC}"
    exit 1
fi

echo ""
echo -e "${YELLOW}Step 4: Importing sample data...${NC}"
PGPASSWORD=$DB_PASS psql -U $DB_USER -d $DB_NAME -f data/data.sql

if [ $? -eq 0 ]; then
    echo -e "${GREEN}✓ Sample data imported successfully${NC}"
else
    echo -e "${RED}✗ Failed to import sample data${NC}"
    exit 1
fi

echo ""
echo -e "${GREEN}=========================================="
echo "  Database setup completed successfully!"
echo "==========================================${NC}"
echo ""
echo "Database Information:"
echo "  - Database: $DB_NAME"
echo "  - User: $DB_USER"
echo "  - Password: $DB_PASS"
echo "  - Host: localhost"
echo ""
echo "Test users (password: pass123):"
echo "  alice, bob, charlie, david, emma,"
echo "  frank, hannah, ian, julia, kevin"
echo ""
echo "You can now run the server with: make run"
