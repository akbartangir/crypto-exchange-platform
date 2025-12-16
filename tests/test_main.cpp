#include <gtest/gtest.h>
#include "OrderBook.h"
#include "OrderBookEntry.h"
#include "Wallet.h"

// Basic sanity test
TEST(OrderBookEntryTest, StringToOrderBookType) {
    EXPECT_EQ(OrderBookEntry::stringToOrderBookType("bid"), OrderBookType::bid);
    EXPECT_EQ(OrderBookEntry::stringToOrderBookType("ask"), OrderBookType::ask);
    EXPECT_EQ(OrderBookEntry::stringToOrderBookType("unknown_type"), OrderBookType::unknown);
}

// Test OrderBookEntry creation
TEST(OrderBookEntryTest, Constructor) {
    OrderBookEntry entry(100.5, 2.0, "2020/03/17 17:01:24.884492", "BTC/USDT", OrderBookType::bid, "user1");
    
    EXPECT_EQ(entry.price, 100.5);
    EXPECT_EQ(entry.amount, 2.0);
    EXPECT_EQ(entry.timestamp, "2020/03/17 17:01:24.884492");
    EXPECT_EQ(entry.product, "BTC/USDT");
    EXPECT_EQ(entry.orderType, OrderBookType::bid);
    EXPECT_EQ(entry.username, "user1");
}

// Test price comparison functions
TEST(OrderBookEntryTest, CompareFunctions) {
    OrderBookEntry e1(100.0, 1.0, "2020/03/17 17:01:24", "BTC/USDT", OrderBookType::bid);
    OrderBookEntry e2(200.0, 1.0, "2020/03/17 17:01:25", "BTC/USDT", OrderBookType::bid);
    
    EXPECT_TRUE(OrderBookEntry::compareByPriceAsc(e1, e2));
    EXPECT_FALSE(OrderBookEntry::compareByPriceDesc(e1, e2));
    EXPECT_TRUE(OrderBookEntry::compareByTimestamp(e1, e2));
}

// Test mean price calculation
TEST(OrderBookTest, GetMeanPrice) {
    std::vector<OrderBookEntry> orders;
    orders.push_back(OrderBookEntry(100.0, 1.0, "2020/03/17 17:01:24", "BTC/USDT", OrderBookType::bid));
    orders.push_back(OrderBookEntry(200.0, 1.0, "2020/03/17 17:01:24", "BTC/USDT", OrderBookType::bid));
    orders.push_back(OrderBookEntry(300.0, 1.0, "2020/03/17 17:01:24", "BTC/USDT", OrderBookType::bid));
    
    EXPECT_DOUBLE_EQ(OrderBook::getMeanPrice(orders), 200.0);
}

// Test mean price with empty vector
TEST(OrderBookTest, GetMeanPriceEmpty) {
    std::vector<OrderBookEntry> orders;
    EXPECT_DOUBLE_EQ(OrderBook::getMeanPrice(orders), 0.0);
}

// Test high and low price
TEST(OrderBookTest, GetHighLowPrice) {
    std::vector<OrderBookEntry> orders;
    orders.push_back(OrderBookEntry(150.0, 1.0, "2020/03/17 17:01:24", "BTC/USDT", OrderBookType::bid));
    orders.push_back(OrderBookEntry(200.0, 1.0, "2020/03/17 17:01:24", "BTC/USDT", OrderBookType::bid));
    orders.push_back(OrderBookEntry(100.0, 1.0, "2020/03/17 17:01:24", "BTC/USDT", OrderBookType::bid));
    
    EXPECT_DOUBLE_EQ(OrderBook::getHighPrice(orders), 200.0);
    EXPECT_DOUBLE_EQ(OrderBook::getLowPrice(orders), 100.0);
}
