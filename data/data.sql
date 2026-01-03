-- ============================
-- Insert Users
-- ============================
INSERT INTO users (username, password_hash, email, bank_account, bank_name, balance)
VALUES
('alice', 'pass123', 'alice@example.com', '001', 'Vietcombank', 50000000),
('bob', 'pass123', 'bob@example.com', '002', 'Techcombank', 30000000),
('charlie', 'pass123', 'charlie@example.com', '003', 'MB Bank', 15000000),
('david', 'pass123', 'david@example.com', '004', 'Vietinbank', 8000000),
('emma', 'pass123', 'emma@example.com', '005', 'VPBank', 12000000),
('frank', 'pass123', 'frank@example.com', '006', 'BIDV', 9500000),
('hannah', 'pass123', 'hannah@example.com', '007', 'ACB', 3000000),
('ian', 'pass123', 'ian@example.com', '008', 'BIDV', 6000000),
('julia', 'pass123', 'julia@example.com', '009', 'Techcombank', 42000000),
('kevin', 'pass123', 'kevin@example.com', '010', 'Vietcombank', 20000000);

-- ============================
-- Insert Auction Rooms
-- ============================
INSERT INTO auction_rooms (room_name, created_by, description, status, participant_count, image_url)
VALUES
('Luxury Watches Auction', 1, 'Premium collection of luxury timepieces', 'active', 12, 'https://images.unsplash.com/photo-1523170335258-f5ed11844a49'),
('Vintage Electronics', 2, 'Classic tech collectibles from the 80s and 90s', 'upcoming', 8, 'https://images.unsplash.com/photo-1550009158-9ebf69173e03'),
('Art & Collectibles', 3, 'Rare art pieces and limited edition collectibles', 'active', 15, 'https://images.unsplash.com/photo-1561214115-f2f134cc4912'),
('Rare Books Collection', 1, 'First editions and signed copies', 'upcoming', 6, 'https://images.unsplash.com/photo-1512820790803-83ca734da794'),
('Designer Fashion', 2, 'Luxury clothing and accessories', 'active', 20, 'https://images.unsplash.com/photo-1490481651871-ab68de25d43d');

-- ============================
-- Insert Items (with images)
-- ============================
INSERT INTO auction_items (room_id, item_name, description, starting_price, current_price, buy_now_price, auction_duration, status, created_by, queue_position, image_url)
VALUES
-- Room 1: Luxury Watches
(1, 'Rolex Submariner', 'Vintage 1960s Rolex Submariner in excellent condition', 50000000, 75000000, 120000000, 3600, 'active', 1, 1, 'https://images.unsplash.com/photo-1523170335258-f5ed11844a49'),
(1, 'Omega Speedmaster', 'Classic moonwatch with original box and papers', 30000000, 30000000, 45000000, 3600, 'available', 1, 2, 'https://images.unsplash.com/photo-1614164185128-e4ec99c436d7'),
(1, 'Patek Philippe Calatrava', 'Elegant dress watch in 18K gold', 80000000, 80000000, 150000000, 3600, 'available', 1, 3, 'https://images.unsplash.com/photo-1587836374828-4dbafa94cf0e'),
(1, 'Rolex Daytona', 'Rare Paul Newman dial, collector\'s item', 150000000, 150000000, 250000000, 3600, 'available', 1, 4, 'https://images.unsplash.com/photo-1622434641406-a158123450f9'),

-- Room 2: Vintage Electronics
(2, 'Apple Macintosh 128K', 'Original 1984 Macintosh in working condition', 8000000, 8000000, 15000000, 3600, 'available', 2, 1, 'https://images.unsplash.com/photo-1587831990711-23ca6441447b'),
(2, 'Sony Walkman TPS-L2', 'First generation Walkman from 1979', 3000000, 3000000, 5000000, 3600, 'available', 2, 2, 'https://images.unsplash.com/photo-1505740420928-5e560c06d30e'),
(2, 'Nintendo Game Boy', 'Original 1989 Game Boy with games', 2000000, 2000000, 4000000, 3600, 'available', 2, 3, 'https://images.unsplash.com/photo-1531525645387-7f14be1bdbbd'),

-- Room 3: Art & Collectibles
(3, 'Limited Edition Print', 'Signed lithograph by famous artist', 15000000, 15000000, 25000000, 3600, 'available', 3, 1, 'https://images.unsplash.com/photo-1561214115-f2f134cc4912'),
(3, 'Vintage Vinyl Collection', 'Rare Beatles first pressings', 10000000, 10000000, 18000000, 3600, 'available', 3, 2, 'https://images.unsplash.com/photo-1603048588665-791ca8aea617'),
(3, 'Antique Sculpture', 'Bronze sculpture from 19th century', 25000000, 25000000, 40000000, 3600, 'available', 3, 3, 'https://images.unsplash.com/photo-1578926078164-61a39d3a4f4e'),

-- Room 4: Rare Books
(4, 'First Edition Harry Potter', 'Philosopher\'s Stone first print', 50000000, 50000000, 80000000, 3600, 'available', 1, 1, 'https://images.unsplash.com/photo-1512820790803-83ca734da794'),
(4, 'Signed Hemingway Novel', 'The Old Man and the Sea, signed', 30000000, 30000000, 50000000, 3600, 'available', 1, 2, 'https://images.unsplash.com/photo-1544947950-fa07a98d237f'),

-- Room 5: Designer Fashion
(5, 'Hermès Birkin Bag', 'Rare crocodile leather Birkin 35', 200000000, 200000000, 350000000, 3600, 'available', 2, 1, 'https://images.unsplash.com/photo-1584917865442-de89df76afd3'),
(5, 'Chanel Classic Flap', 'Vintage Chanel double flap bag', 80000000, 80000000, 120000000, 3600, 'available', 2, 2, 'https://images.unsplash.com/photo-1590874103328-eac38a683ce7'),
(5, 'Louis Vuitton Trunk', 'Antique steamer trunk from 1920s', 60000000, 60000000, 100000000, 3600, 'available', 2, 3, 'https://images.unsplash.com/photo-1566150905458-1bf1fc113f0d');

-- ============================
-- Insert User Rooms (One room per user constraint)
-- ============================
INSERT INTO user_rooms (user_id, room_id, joined_at)
VALUES
(1, 1, NOW() - INTERVAL '30 MINUTES'),
(2, 1, NOW() - INTERVAL '25 MINUTES'),
(3, 1, NOW() - INTERVAL '20 MINUTES'),
(4, 1, NOW() - INTERVAL '15 MINUTES'),
(5, 2, NOW() - INTERVAL '20 HOURS'),
(6, 1, NOW() - INTERVAL '5 MINUTES'),
(7, 2, NOW() - INTERVAL '18 HOURS'),
(8, 2, NOW() - INTERVAL '16 HOURS'),
(9, 2, NOW() - INTERVAL '14 HOURS'),
(10, 2, NOW() - INTERVAL '12 HOURS');

-- ============================
-- Insert Bids
-- ============================

-- Room 1 bids
INSERT INTO bids (bid_amount, item_id, user_id, bid_time)
VALUES
(8500000, 1, 2, NOW() - INTERVAL '25 MINUTES'),
(9000000, 1, 3, NOW() - INTERVAL '20 MINUTES'),
(9500000, 1, 4, NOW() - INTERVAL '18 MINUTES'),

(9500000, 2, 2, NOW() - INTERVAL '10 MINUTES'),
(10000000, 2, 3, NOW() - INTERVAL '8 MINUTES'),

(7500000, 3, 5, NOW() - INTERVAL '5 MINUTES'),
(7800000, 3, 6, NOW() - INTERVAL '3 MINUTES');

-- Room 2 bids
INSERT INTO bids (bid_amount, item_id, user_id, bid_time)
VALUES
(52000000, 4, 7, NOW() - INTERVAL '20 HOURS'),
(54000000, 4, 7, NOW() - INTERVAL '19 HOURS'),

(23000000, 5, 8, NOW() - INTERVAL '16 HOURS'),
(25000000, 5, 9, NOW() - INTERVAL '15 HOURS'),

(16000000, 6, 10, NOW() - INTERVAL '12 HOURS'),
(17000000, 6, 7, NOW() - INTERVAL '11 HOURS');

-- Room 3 bids (Past auctions)
INSERT INTO bids (bid_amount, item_id, user_id, bid_time)
VALUES
(3500000, 7, 3, NOW() - INTERVAL '2 DAYS 18 HOURS'),
(4000000, 7, 4, NOW() - INTERVAL '2 DAYS 17 HOURS'),

(6000000, 8, 2, NOW() - INTERVAL '1 DAY 18 HOURS'),
(6500000, 8, 5, NOW() - INTERVAL '1 DAY 17 HOURS'),

(3000000, 9, 6, NOW() - INTERVAL '12 HOURS'),
(3200000, 9, 7, NOW() - INTERVAL '11 HOURS');

-- ============================
-- Insert Chat Messages
-- ============================
INSERT INTO chat_messages (room_id, user_id, message)
VALUES
(1, 2, 'Great items today!'),
(1, 3, 'Interested in the iPhone'),
(1, 4, 'Just won the iPhone 15!'),
(2, 5, 'Love this Rolex!'),
(2, 7, 'Anyone bidding on the bracelet?');

-- ============================
-- Insert Activity Logs
-- ============================
INSERT INTO activity_logs (user_id, action, details)
VALUES
(1, 'USER_LOGIN', 'Login successful'),
(2, 'USER_LOGIN', 'Login successful'),
(3, 'USER_LOGIN', 'Login successful'),
(1, 'ROOM_CREATE', 'Created room: Electronics Auction'),
(2, 'ROOM_CREATE', 'Created room: Luxury Items'),
(1, 'ITEM_CREATE', 'Created item: iPhone 15'),
(1, 'ITEM_CREATE', 'Created item: MacBook Air M2'),
(2, 'ITEM_CREATE', 'Created item: Samsung Galaxy S23'),
(2, 'BID_PLACED', 'Placed bid on iPhone 15: 8500000 VND'),
(3, 'BID_PLACED', 'Placed bid on iPhone 15: 9000000 VND'),
(4, 'BID_PLACED', 'Placed bid on iPhone 15: 9500000 VND (WINNING)'),
(4, 'ITEM_SOLD', 'Item sold to david via bid for 9500000 VND'),
(5, 'DEPOSIT', 'Deposited 30000000 VND to account'),
(2, 'CHAT_MESSAGE', 'Sent message in room 1');