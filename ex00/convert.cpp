#include "BitcoinExchange.hpp"

void    convert_print(std::map<std::string, double> &data, std::string date,  std::string value)
{
    std::map<std::string, double>::iterator it = data.lower_bound(date);
    if(it->first != date && it != data.begin())
        --it;
    double value_d = strtod(value.c_str(), 0);
    double rate = it->second;
    double result = rate * value_d;
    std::cout << date <<" => "<< value_d << " = " << result <<  "\n";
}