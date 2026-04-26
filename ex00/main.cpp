#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>

int  parse_value(std::string value, double &val)
{
    char *rest;
    val = strtod(value.c_str(), &rest);
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

// void    read_file(std::ifstream &file)
// {
//     std::string line;
//     while(std::getline(file, line))
//     {
//         size_t pos = line.find('|', 0);
//         if(pos == std::string::npos)
//         {
//             std::cout << "Error: bad input => " << line << std::endl;
//         }
//         std::string date = line.substr(0, pos);
//         std::string value = line.substr(pos + 1);
//         if(!parse_value(value))
//             continue;
//     }
// }

int parse_input(const char *filename)
{
    std::ifstream file(filename);
    if(!file.is_open())
        throw std::runtime_error("Could not open Input file");
    return 1;
}


int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Error: usage ./btc input.txt" << std::endl;
        return 1;
    }
    (void)argv;
    try
    {
        BitcoinExchange btc("data.csv");
        
        std::ifstream file(argv[1]);
        if(!file.is_open())
        {
            std::cout << "Could not open Input file\n";
            return 1;
        }
        std::string line;

        while (std::getline(file, line))
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
                double value_d = 0;
                if(!parse_value(value, value_d))
                    continue;
                std::cout << btc.getRate(date) * value_d << std::endl;
            }
            
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}

