#include "PmergeMe.hpp"

bool PmergeMe::HasDuplicate(std::vector<int> &arr, int value)
{
    for(size_t i = 0; i < arr.size(); i++)
    {
        if(arr[i] == value)
            return true;
    }
    return false;
}

int PmergeMe::parse_one_str(std::string str, std::vector<int> &arr)
{
    std::string value;
    for(int i = 0; str[i]; i++)
    {
        char *rest;
        value += str[i];
        if(str[i] == ' '|| (str[i] != ' ' && (str[i+1] != 0 && str[i+1] != ' ')))
            continue;            
        double num = strtod(value.c_str(), &rest);
        if(*rest || num < 0 || num > INT_MAX)
            return 0;
        if(num != std::floor(num))
            return 0;
        if(HasDuplicate(arr, num))
            return 0;
        arr.push_back(num);
        value = "";   
    }
    return 1;
}

int PmergeMe::parse_input(char **argv, std::vector<int> &arr)
{

    for(int i = 1; argv[i]; i++)
    {
        char *rest;
        double num = strtod(argv[i], &rest);
        if(*rest || num < 0 || num > INT_MAX)
            return 0;
        if(num != std::floor(num))
            return 0;
        if(HasDuplicate(arr, num))
            return 0;
        arr.push_back(num);
    }
    return 1;
}

int PmergeMe::parser(int argc, char **argv, std::vector<int> &arr)
{
    if(argc == 2)
    {
        if(!parse_one_str(argv[1], arr))
            return 0;  
    }
    else if(!parse_input(argv, arr))
        return 0;
    return 1;
}


///////////////////////////////////////

std::vector<std::pair<int,int>> PmergeMe::makePairs(std::vector<int>& arr)
{
    std::vector<std::pair<int, int>> pairs;
    
    for(int i = 0; i + 1 < arr.size(); i += 2)
    {
        int a = arr[i];
        int b = arr[i + 1];
        if(b > a)
            std::swap(a, b);
        std::make_pair(a, b);
        pairs.push_back(std::make_pair(a,b));
    }
    return pairs;
}

void    PmergeMe::SplitPairs(std::vector<std::pair<int, int>> pairs, std::vector<int>& main_chain, 
                                std::vector<int>& pending)
{
    for(int i =0 ; i < pairs.size(); i++)
    {
        main_chain.push_back(pairs[i].first);
        pending.push_back(pairs[i].second);
    }
}

