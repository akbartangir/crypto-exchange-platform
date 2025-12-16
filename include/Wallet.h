#ifndef WALLET_H
#define WALLET_H

#include <map>
#include <string>

#include "OrderBookEntry.h"

class Wallet {
  private:
    std::map<std::string, double> currencies;

  public:
    Wallet();

    /* insert currency to the wallet */
    void insertCurrency(const std::string& type, double amount);

    /* remove currency from the wallet */
    bool removeCurrency(const std::string& type, double amount);

    /* check if the wallet contains this much currency or more */
    bool containsCurrency(const std::string& type, double amount);

    /* checks if the wallet can cope with this ask or bid */
    bool canFulFillOrder(const OrderBookEntry& order);

    /* update the contents of the wallet
     * assumes the order was made by the owner of the wallet */
    void processSale(OrderBookEntry& sale);

    /* generate a string representation of the wallet */
    std::string toString() const;
};

#endif // WALLET_H
