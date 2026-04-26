# include "BitcoinExchange.hpp"
# include "exception"
BitcoinExchange::BitcoinExchange(const char *filename)
{
    parse_csv(filename);
}

double    BitcoinExchange::getRate(std::string date)
{
    if(!parse_date(date))
        throw std::runtime_error("Error: invalid date");
    std::map<std::string, double>::iterator it = data.lower_bound(date);
    if(it == data.end())
        --it;
    if(it->first != date)
    {
        if (it == data.begin())
            throw std::runtime_error("Error: No earlier date available");    
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
        throw std::runtime_error("CSV file contains to Data");

}
int BitcoinExchange::parse_date(std::string date)
{
    size_t pos = date.find('-', 0);
    if(pos == std::string::npos)
        return 0;
    char *rest;
    strtod((date.substr(0, pos)).c_str(), &rest);
    if(*rest != 0)
    {
        return 0;
    }
    size_t pos1 = date.find('-', pos+1);
    if(pos1 == std::string::npos)
    {
        return 0;
    }
    strtod((date.substr(pos + 1, pos1 - (pos + 1))).c_str(), &rest);
    if(*rest)
    {
        return 0;
    }
    
    return 1;
}
