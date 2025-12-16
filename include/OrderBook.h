#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include "OrderBookEntry.h"

#include <string>
#include <vector>

class OrderBook {
  public:
    OrderBook(std::string file);
    ~OrderBook();

    std::vector<std::string> getKnownProducts();
    std::vector<OrderBookEntry>
    getOrders(OrderBookType type, std::string product, std::string timestamp);
    std::string getEarliestTime();
    std::string getNextTime(std::string timestamp);
    static double getMeanPrice(const std::vector<OrderBookEntry>& orders);
    static double getHighPrice(std::vector<OrderBookEntry>& orders);
    static double getLowPrice(std::vector<OrderBookEntry>& orders);

    void insertOrder(OrderBookEntry& order);
    std::vector<OrderBookEntry> matchAsksToBids(std::string product,
                                                std::string timestamp);

  private:
    std::vector<OrderBookEntry> orders;
};

#endif // ORDERBOOK_H
