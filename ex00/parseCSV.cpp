#include "BitcoinExchange.hpp"

void     read_csv(std::ifstream &file)
{   
    std::string line;
    std::map<std::string, double> map;
    std::getline(file, line); //skip the header
    while(std::getline(file, line))
    {
        size_t pos = line.find(',', 0);
        if(pos == std::string::npos)
            continue;
        std::string date = line.substr(0, pos);
        std::string rate_str = line.substr(pos + 1);
        double rate = std::strtod(rate_str.c_str(), NULL);
        map[date] = rate;
    }
    std::map<std::string, double>::iterator it;
    for(it = map.begin(); it != map.end(); ++it)
    {
        std::cout << it->first << " : " << it->second << "\n";
    }
}

int    parse_csv(void)
{
    std::ifstream file("data.csv");
    if(!file.is_open())
    {
        std::cout << "Error: could not open CSV file" << std::endl;
        return 0;
    }
    read_csv(file);
    return 1;
}
