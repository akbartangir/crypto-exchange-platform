#include "Wallet.h"
#include "FileReader.h"

#include <iostream>

Wallet::Wallet() {}

void Wallet::insertCurrency(const std::string& type, const double amount) {
    double balance;

    if (amount < 0) {
        throw std::exception{};
    }

    if (currencies.count(type) == 0) {
        balance = 0;
    } else {
        balance = currencies[type];
    }

    balance += amount;
    currencies[type] = balance;
}

bool Wallet::removeCurrency(const std::string& type, double amount) {

    if (amount < 0) {
        return false;
    }

    if (currencies.count(type) == 0) {
        return false;
    } else {
        if (containsCurrency(type, amount)) {
            currencies[type] -= amount;
            return true;
        } else {
            return false;
        }
    }
}

bool Wallet::containsCurrency(const std::string& type, const double amount) {
    if (currencies.count(type) == 0) {
        return false;
    } else {
        return currencies[type] >= amount;
    }
}

bool Wallet::canFulFillOrder(const OrderBookEntry& order) {
    std::vector<std::string> currencies =
        FileReader::tokenise(order.product, '/');

    if (order.orderType == OrderBookType::ask) {
        double amount = order.amount;
        std::string currency = currencies[0];
        std::cout << "Wallet::canFulFillOrder " << currency << " : " << amount
                  << '\n';
        return containsCurrency(currency, amount);
    } else if (order.orderType == OrderBookType::bid) {
        double amount = order.amount * order.price;
        std::string currency = currencies[1];
        std::cout << "Wallet::canFulFillOrder " << currency << " : " << amount
                  << '\n';
        return containsCurrency(currency, amount);
    }

    return false;
}

void Wallet::processSale(OrderBookEntry& sale) {
    std::vector<std::string> currs = FileReader::tokenise(sale.product, '/');

    if (sale.orderType == OrderBookType::asksale) {
        double outgoingAmount = sale.amount;
        std::string outgoingCurrency = currs[0];
        double incomingAmount = sale.amount * sale.price;
        std::string incomingCurrency = currs[1];

        currencies[incomingCurrency] += incomingAmount;
        currencies[outgoingCurrency] -= outgoingAmount;
    } else if (sale.orderType == OrderBookType::bidsale) {
        double incomingAmount = sale.amount;
        std::string incomingCurrency = currs[0];
        double outgoingAmount = sale.amount * sale.price;
        std::string outgoingCurrency = currs[1];

        currencies[incomingCurrency] += incomingAmount;
        currencies[outgoingCurrency] -= outgoingAmount;
    }
}

std::string Wallet::toString() const {
    std::string s;
    for (std::pair<std::string, double> pair : currencies) {
        std::string currency = pair.first;
        double amount = pair.second;
        s += currency + " : " + std::to_string(amount) + "\n";
    }
    return s;
}
