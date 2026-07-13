#include "PmergeMe.hpp"
#include <algorithm>
#include <exception>

int main(int argc, char **argv)
{
    try 
    {
        PmergeMe Ford(argc, argv);
    

    } catch (const std::exception &e ) 
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}