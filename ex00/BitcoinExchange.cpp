# include "BitcoinExchange.hpp"
#include <cstdlib>
#include <string>

BitcoinExchange::BitcoinExchange(){}

BitcoinExchange::~BitcoinExchange(){}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other){
    (void)other;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other){
    (void)other;
    return *this;
}

BitcoinExchange::BitcoinExchange(const char *filename)
{
    parse_csv(filename);
}

double    BitcoinExchange::getRate(std::string date)
{
    if(!parse_date(date))
    {
        std::cerr << ("Error: invalid date\n");
        return -1;
    }
    std::map<std::string, double>::iterator it = data.lower_bound(date);
    if(it == data.end())
        --it;
    else if(it->first != date)
    {
        if (it == data.begin())
        {
            std::cerr << ("Error: No earlier date available\n");    
            return -1;
        }
        --it;
    }
    double rate = it->second;
    return rate;
}

void     BitcoinExchange::read_csv(std::ifstream &file)
{   
    std::string line;
    std::getline(file, line); //skip the header
    while(std::getline(file, line))
    {
        size_t pos = line.find(',', 0);
        if(pos == std::string::npos)
            continue;
        std::string date = line.substr(0, pos);
        std::string rate_str = line.substr(pos + 1);
        double rate = std::strtod(rate_str.c_str(), NULL);
        data[date] = rate;
    }
    return ;
}

void    BitcoinExchange::parse_csv(const char *filename)
{
    std::ifstream file(filename);
    if(!file.is_open())
        throw std::runtime_error("Could no open CSV file");
    read_csv(file);
    if(data.empty())
        throw std::runtime_error("CSV file Contains No Data");

}

bool IsLeapYear(int year)
{
    return((year % 4 == 0) || (year % 100 != 0 && year % 400 == 0));
}

int daysInMonth(int month, int year)
{
    static const int days[] =
    {
        31, // Jan
        28, // Feb
        31, // Mar
        30, // Apr
        31, // May
        30, // Jun
        31, // Jul
        31, // Aug
        30, // Sep
        31, // Oct
        30, // Nov
        31  // Dec
    };
    if(month == 2 && IsLeapYear(year))
        return 29;
    return days[month - 1];
}

int BitcoinExchange::parse_date(std::string date)
{
    size_t pos = date.find('-', 0);
    if(pos == std::string::npos)
        return 0;
    char *rest;
    std::string str_year = date.substr(0, pos);
    double year = strtod(str_year.c_str(), &rest);
    if(*rest != 0 || year < 0 || str_year.size() != 4)
        return 0;

    size_t pos1 = date.find('-', pos+1);
    if(pos1 == std::string::npos)
        return 0;
    
    std::string str_mounth = date.substr(pos + 1, pos1 - (pos + 1));
    double month = strtod(str_mounth.c_str(), &rest);
    if(*rest || !(month > 0 && month <= 12) || str_mounth.size() != 2)
        return 0;

    std::string str_day = date.substr(pos1 + 1);
    double day = strtod(str_day.c_str(), &rest);
    if(!(day > 0 && day <= daysInMonth(month, year)) || str_day.size() != 2)
        return 0;
    return 1;
}
