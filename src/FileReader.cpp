#include "FileReader.h"
#include <fstream>
#include <iostream>

FileReader::~FileReader() {}

std::vector<OrderBookEntry> FileReader::readCSV(std::string csvFilePath) {
    std::vector<OrderBookEntry> entries;
    std::ifstream csvFile{csvFilePath};
    std::string line;

    if (csvFile.is_open()) {
        while (std::getline(csvFile, line)) {
            try {
                OrderBookEntry obe = stringsToOBE(tokenise(line, ','));
                entries.push_back(obe);
            } catch (const std::exception& e) {
                std::cout << "FileReader::readCSV - bad line \n";
            }
        } // end of while
    }

    std::cout << "readCSV: " << entries.size() << '\n';
    return entries;
}

std::vector<std::string> FileReader::tokenise(std::string line,
                                              char separator) {
    std::vector<std::string> tokens;
    std::string token;
    size_t start, end;

    start = line.find_first_not_of(separator, 0);
    do {
        end = line.find_first_of(separator, start);

        if (start == line.length() || start == end)
            break;
        if (end != 0)
            token = line.substr(start, end - start);
        else
            token = line.substr(start, line.length() - start);
        tokens.push_back(token);
        start = end + 1;
    } while (end != std::string::npos);

    return tokens;
}

OrderBookEntry FileReader::stringsToOBE(std::vector<std::string> tokens) {
    double price, amount;

    if (tokens.size() != 5) // check bad line
    {
        std::cout << " FileReader::stringsToOBE - Bad line\n";
        throw std::exception{};
    }

    try {
        price = std::stod(tokens[3]);
        amount = std::stod(tokens[4]);
    } catch (const std::exception& e) {
        std::cout << "Bad float: " << tokens[3] << '\n';
        std::cout << "Bad float: " << tokens[4] << '\n';
        throw;
    }

    OrderBookEntry obe{price, amount, tokens[0], tokens[1],
                       OrderBookEntry::stringToOrderBookType(tokens[2])};

    return obe;
}

OrderBookEntry FileReader::stringsToOBE(std::string priceStr,
                                        std::string amountStr,
                                        std::string timestamp,
                                        std::string product,
                                        OrderBookType orderBookType) {
    double price, amount;
    try {
        price = std::stod(priceStr);
        amount = std::stod(amountStr);
    } catch (const std::exception& e) {
        std::cout << "FileReader::stringsToOBE - Bad float: " << priceStr
                  << '\n';
        std::cout << "FileReader::stringsToOBE - Bad float: " << amountStr
                  << '\n';
        throw;
    }

    OrderBookEntry obe{price, amount, timestamp, product, orderBookType};

    return obe;
}
