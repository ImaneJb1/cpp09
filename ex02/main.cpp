#include "PmergeMe.hpp"

int main(int argc, char *argv[])
{
    if(argc < 2 || !argv[1][0])
        return 0;
    if(!parse_input(argv))
        std::cout << "Invalid input\n";
    return 0;
}
