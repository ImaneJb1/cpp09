#pragma once

#include "iostream"
#include "map"
#include "fstream"
#include "climits"

class BitcoinExchange
{
  private:
    std::map<std::string, double> data;
    void   parse_csv(const char *filename);
    void     read_csv(std::ifstream &file);
  public:
    BitcoinExchange(const char *filename);
    double   getRate(std::string date);
  private:
    int parse_date(std::string date);
    // int parse_input(const char *filename);
    // void    convert_print(std::string input, std::string value);
    // int  parse_value(std::string value);
    // void    read_file(std::ifstream &file);

};
