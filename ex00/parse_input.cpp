#include "BitcoinExchange.hpp"

int    read_file(std::ifstream file)
{
    std::string line;
    while(std::getline(file, line))
    {
        int pos = line.find('|', 0);
        if(pos == std::string::npos)
        {
            std::cout << "Error: bad input => " << line << std::endl;
            return 0;
        }
        std::string date = line.substr(pos, 0);
        std::string value = line.substr(pos + 1);
        if(!parse_date(std::string date) || parse_value(std::string value)) // ba9i maderthom
            return 0;
    }
}

int parse_input(char *filename)
{
    std::ifstream file(filename);
    if(!file.is_open())
    {
        std::cout << "Error: could not open input file" << std::endl;
        return 0;
    } 

}

