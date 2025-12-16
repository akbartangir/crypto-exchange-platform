#include "OrderBook.h"
#include "FileReader.h"
#include "OrderBookEntry.h"

#include <algorithm>
#include <map>

OrderBook::OrderBook(std::string file) {
    orders = FileReader::readCSV(file);
}

OrderBook::~OrderBook() {}

std::vector<std::string> OrderBook::getKnownProducts() {
    std::vector<std::string> products;
    std::map<std::string, bool> prodMap;

    for (OrderBookEntry& e : orders) {
        prodMap[e.product] = true;
    }

    for (auto const& e : prodMap) {
        products.push_back(e.first);
    }

    return products;
}

std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type,
                                                 std::string product,
                                                 std::string timestamp) {
    std::vector<OrderBookEntry> orders_sub;

    for (OrderBookEntry& e : orders) {
        if (e.orderType == type && e.product == product &&
            e.timestamp == timestamp) {
            orders_sub.push_back(e);
        }
    }

    return orders_sub;
}

double OrderBook::getHighPrice(std::vector<OrderBookEntry>& orders) {
    double max = orders[0].price;
    for (OrderBookEntry& e : orders) {
        if (e.price > max)
            max = e.price;
    }

    return max;
}

double OrderBook::getLowPrice(std::vector<OrderBookEntry>& orders) {
    double min = orders[0].price;
    for (OrderBookEntry& e : orders) {
        if (e.price < min)
            min = e.price;
    }

    return min;
}

std::string OrderBook::getEarliestTime() {
    return orders[0].timestamp;
}

std::string OrderBook::getNextTime(std::string timestamp) {
    std::string next_timestamp{""};
    for (OrderBookEntry& e : orders) {
        if (e.timestamp > timestamp) {
            next_timestamp = e.timestamp;
            break;
        }
    }

    if (next_timestamp == "") {
        next_timestamp = orders[0].timestamp;
    }

    return next_timestamp;
}

/**
 * @brief Calculates the mean price of the given orders.
 *
 * This function takes a vector of OrderBookEntry objects and calculates the
 * mean price of all the orders. If the vector is empty, the function returns
 * 0.0.
 *
 * @param orders A vector of OrderBookEntry objects representing the orders.
 * @return double The mean price of the orders. Returns 0.0 if the vector is
 * empty.
 */
double OrderBook::getMeanPrice(const std::vector<OrderBookEntry>& orders) {
    if (orders.empty())
        return 0.0;
    double sum = 0.0;
    for (const OrderBookEntry& e : orders) {
        sum += e.price;
    }
    return sum / orders.size();
}

void OrderBook::insertOrder(OrderBookEntry& order) {
    orders.push_back(order);
    std::sort(orders.begin(), orders.end(), OrderBookEntry::compareByTimestamp);
}

std::vector<OrderBookEntry> OrderBook::matchAsksToBids(std::string product,
                                                       std::string timestamp) {
    std::vector<OrderBookEntry> asks =
        getOrders(OrderBookType::ask, product, timestamp);

    std::vector<OrderBookEntry> bids =
        getOrders(OrderBookType::bid, product, timestamp);

    std::vector<OrderBookEntry> sales;

    std::sort(asks.begin(), asks.end(), OrderBookEntry::compareByPriceAsc);
    std::sort(bids.begin(), bids.end(), OrderBookEntry::compareByPriceDesc);

    for (OrderBookEntry& ask : asks) {
        for (OrderBookEntry& bid : bids) {
            if (bid.price >= ask.price) {
                OrderBookEntry sale{ask.price, 0, timestamp, product,
                                    OrderBookType::asksale};

                if (bid.username == "simuser") {
                    sale.username = "simuser";
                    sale.orderType = OrderBookType::bidsale;
                } else if (ask.username == "simuser") {
                    sale.username = "simuser";
                    sale.orderType = OrderBookType::asksale;
                }

                if (bid.amount == ask.amount) {
                    sale.amount = ask.amount;
                    sales.push_back(sale);
                    bid.amount = 0;
                    break;
                }

                if (bid.amount > ask.amount) {
                    sale.amount = ask.amount;
                    sales.push_back(sale);
                    bid.amount -= ask.amount;
                    break;
                }

                if (bid.amount < ask.amount && bid.amount > 0) {
                    sale.amount = bid.amount;
                    sales.push_back(sale);
                    ask.amount -= bid.amount;
                    bid.amount = 0;
                    continue;
                }
            }
        }
    }

    return sales;
}
