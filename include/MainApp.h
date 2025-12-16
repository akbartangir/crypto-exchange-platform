#ifndef MAINAPP_H
#define MAINAPP_H

#include "OrderBook.h"
#include "OrderBookEntry.h"
#include "Wallet.h"

class MainApp {
  public:
    MainApp();
    void init();

  private:
    void displayMenu();
    void displayHelp();
    void displayExchangeStats();
    void enterAsk();
    void enterBid();
    void displayWallet();
    void gotoNextTimeFrame();
    int getUserOption();
    void processUserOption(int choice);
    void displayStatisticsForType(const std::string& product,
                                  OrderBookType type,
                                  const std::string& typeName);

    std::string currentTime;

    OrderBook orderBook{"../data/20200317.csv"};
    // OrderBook orderBook{"../data/test.csv"};

    Wallet wallet;
};

#endif // MAINAPP_H
