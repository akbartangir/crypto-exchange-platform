#ifndef FILEREADER_H
#define FILEREADER_H

#include "OrderBookEntry.h"
#include <vector>

class FileReader {
  private:
    static OrderBookEntry stringsToOBE(std::vector<std::string> strings);

  public:
    FileReader() = default;
    ~FileReader();

    static std::vector<OrderBookEntry> readCSV(std::string csvFilePath);
    static std::vector<std::string> tokenise(std::string line, char separator);
    static OrderBookEntry stringsToOBE(std::string price, std::string amount,
                                       std::string timestamp,
                                       std::string product,
                                       OrderBookType orderBookType);
};

#endif // FILEREADER_H
