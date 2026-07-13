#include "BitcoinExchange.hpp"
#include <cmath>



int  parse_value(std::string value, double &val)
{
    char *rest;
    val = strtod(value.c_str(), &rest);
    if(*rest || std::isnan(val))
    {
        std::cerr << "Error: Invalid value\n";
        return 0;
    }
    if(val < 0)
    {
        std::cerr << "Error: not a positive number\n";
        return 0;
    }
    if(val > 1000 )
    {
        std::cerr << "Error: too large number\n";
        return 0;
    }
    return 1;
}


void trim(std::string& str)
{
    if(str.empty())
        return;
    size_t start = 0;
    while (start < str.size() && std::isspace(static_cast<unsigned char>(str[start])))
        start++;

    size_t end = str.size();
    while (end > start && std::isspace(static_cast<unsigned char>(str[end - 1])))
        end--;
    str = str.substr(start, end - start);
}

int parse_input(const char *filename)
{
    std::ifstream file(filename);
    if(!file.is_open())
        throw std::runtime_error("Could not open Input file");
    return 1;
}

int parse_header(std::string header)
{
    size_t pos = header.find('|', 0);
    if(pos == std::string::npos)
        return 0;
    std::string date = header.substr(0 , pos);
    std::string value = header.substr(pos+1);
    trim(date); trim(value);
    if((date != "date") || (value != "value"))
        return 0;
    return 1;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Error: Please enter an input file" << std::endl;
        return 1;
    }
    (void)argv;
    try
    {
        BitcoinExchange btc("data.csv");
        
        std::ifstream file(argv[1]);
        if(!file.is_open())
        {
            std::cerr << "Error: Could not open Input file\n";
            return 1;
        }
        std::string line;

        while (std::getline(file, line))
        {      
            if(!parse_header(line))
            {
                std::cerr << "Missing a valid header = `date | value`\n";
                break;
            }
            std::string line;
            while(std::getline(file, line))
            {
                trim(line);
                if(!line.empty())
                {
                    size_t pos = line.find('|', 0);
                    if(pos == std::string::npos)
                    {
                        std::cerr << "Error: bad input => " << line << std::endl;
                        continue;
                    }
                    std::string date = line.substr(0, pos);
                    std::string value = line.substr(pos + 1);
                    trim(date); trim(value);
                    if(!value.empty()){
                        double value_d = 0;
                        if(!parse_value(value, value_d))
                            continue;
                        double rate = btc.getRate(date);
                        if(rate >= 0)
                        {
                            std::cout << date << " => "<< value_d << " = "
                            << std::fixed << std::setprecision(2) << rate * value_d << std::endl;
                        }
                    }
                    else {
                        std::cerr << "Error: Expected a value\n";
                    }
                }
            }
            
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}

