#include "BitcoinExchange.hpp"

std::map<std::string, double>     &read_csv(std::ifstream &file, std::map<std::string, double> &data)
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
    return data;
}

std::map<std::string, double>   &parse_csv(std::map<std::string, double> &data)
{
    std::ifstream file("data.csv");
    if(!file.is_open())
    {
        std::cout << "Error: could not open CSV file" << std::endl;
        return data;
    }
    data = read_csv(file, data);
    if(data.empty())
    {
        std::cout << "Error: empty data\n";
    }

    return data;
}
