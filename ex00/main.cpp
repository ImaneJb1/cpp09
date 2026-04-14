#include "BitcoinExchange.hpp"

int main(int argc, char *argv[])
{
    if(argc < 2)
        return 1;
    (void)argv;
    std::map<std::string, double> data;
    data = parse_csv(data);
    if(data.empty())
    {
        return 0;
    }
    if(!parse_input(argv[1], data))
        return 1;
    return 0;
}
