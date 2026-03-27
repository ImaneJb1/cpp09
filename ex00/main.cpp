#include "BitcoinExchange.hpp"

int main(int argc, char const *argv[])
{
    if(argc < 2)
        return 1;
    (void)argv;
    parse_csv();
    return 0;
}
