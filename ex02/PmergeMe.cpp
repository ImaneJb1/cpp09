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
    
    for(size_t i = 0; i + 1 < arr.size(); i += 2)
    {
        int a = arr[i];
        int b = arr[i + 1];
        if(b > a)
            std::swap(a, b);
        pairs.push_back(std::make_pair(a,b));
    }
    return pairs;
}

void    PmergeMe::SplitPairs(std::vector<std::pair<int, int>> pairs, std::vector<int>& main_chain, 
                                std::vector<int>& pending)
{
    for(size_t i =0 ; i < pairs.size(); i++)
    {
        main_chain.push_back(pairs[i].first);
        pending.push_back(pairs[i].second);
    }
}

/////////

 std::vector<int> PmergeMe::buildInsertionOrder(int size)
{
    std::vector<int> jacob;
    jacob.push_back(1);
    jacob.push_back(3);

    while(jacob.back() < size)
    {
        int n = jacob.size();
        jacob.push_back(jacob[n-1] + 2 * jacob[n-2]);
    }
    std::vector<int> order;
    std::vector<bool> used(size, false);
    for(size_t i = 0; i < jacob.size(); i++)
    {
        int limit = std::min(jacob[i], size);
        for(int j = limit -1; j >= 0; j--)
        {
            if(used[j] == false)
            {
                order.push_back(j);
                used[j] = true;
            }
        }
    }
    return order;
}

int PmergeMe::searchBinaryPosition(std::vector<int> &main_chain, int value)
{
    int left = 0;
    int right = main_chain.size();
    while(left < right)
    {
        int mid = (left + right)/2;
        if(main_chain[mid] < value)
            left = mid + 1;
        else
            right = mid;
    }
    return left;
}

void PmergeMe::mergeInstertVector(std::vector<int>& arr)
{
    //base case
    if(arr.size() <= 1)
        return;
    std::vector<std::pair<int, int>> pairs = makePairs(arr);

    std::vector<int> main_chain;
    std::vector<int> pending;

    SplitPairs(pairs, main_chain, pending);

    mergeInstertVector(main_chain);

    std::vector<int> order = buildInsertionOrder(pending.size());

    for(size_t i = 0; i < order.size(); i++)
    {
        int value = pending[order[i]];
        int pos = searchBinaryPosition(main_chain, value);
        main_chain.insert(main_chain.begin() + pos, value);
    }

    if(arr.size() % 2 != 0)
    {
        int last = arr.back();
        int pos = searchBinaryPosition(main_chain, last);
        main_chain.insert(main_chain.begin() + pos, last);
    }

    arr = main_chain;
}

