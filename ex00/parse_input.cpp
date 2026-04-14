#include "BitcoinExchange.hpp"

int parse_date(std::string date)
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



int  parse_value(std::string value)
{
    char *rest;
    double val = strtod(value.c_str(), &rest);
    if(*rest)
        return 0;
    
    if(val < 0)
    {
        std::cout << "Error: not a positive number\n";
        return 0;
    }
    if(val > 1000)
    {
        std::cout << "Error: too large number\n";
        return 0;
    }
    return 1;
}

void    read_file(std::ifstream &file, std::map<std::string, double> &map)
{
    std::string line;
    while(std::getline(file, line))
    {
        size_t pos = line.find('|', 0);
        if(pos == std::string::npos)
        {
            std::cout << "Error: bad input => " << line << std::endl;
        }
        std::string date = line.substr(0, pos);
        std::string value = line.substr(pos + 1);
        if(!parse_date(date) || !parse_value(value))
            continue;
        convert_print(map, date, value);
    }
}

int parse_input(char *filename, std::map<std::string, double> &data)
{
    std::ifstream file(filename);
    if(!file.is_open())
    {
        std::cout << "Error: could not open input file" << std::endl;
        return 0;
    }
    read_file(file, data);
    return 1;
}

