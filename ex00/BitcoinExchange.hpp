#pragma once

#include "iostream"
#include "map"
#include "fstream"
#include "climits"
# include "exception"
#include <iostream>
#include <deque>
#include <iomanip>
#include <fstream>
#include <cctype>

class BitcoinExchange
{
  private:
    std::map<std::string, double> data;
    void   parse_csv(const char *filename);
    void     read_csv(std::ifstream &file);
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange &other);
    BitcoinExchange &operator=(const BitcoinExchange &other);
    
  public:
    ~BitcoinExchange();
    BitcoinExchange(const char *filename);
    double   getRate(std::string date);
  private:
    int parse_date(std::string date);

};
