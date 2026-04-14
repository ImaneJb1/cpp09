#include "PmergeMe.hpp"

int parse_one_str(std::string str, std::vector<int> &arr)
{
    for(int i = 0; str[i]; i++)
    {
        char *rest;
        
        double num = strtod(str[i], &rest);
        if(*rest || num < 0 || num > INT_MAX)
            return 0;
        if(num != std::floor(num))
            return 0;
        arr.push_back(num);
        
    }
}

int parse_input(char **argv, std::vector<int> &arr)
{

    for(int i = 1; argv[i]; i++)
    {
        char *rest;
        double num = strtod(argv[i], &rest);
        if(*rest || num < 0 || num > INT_MAX)
            return 0;
        if(num != std::floor(num))
            return 0;
        arr.push_back(num);
    }
    return 1;
}

