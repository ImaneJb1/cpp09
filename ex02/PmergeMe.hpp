#pragma once

#include <stdlib.h>
#include "iostream"
#include "cmath"
#include "climits"
#include "vector"

class PmergeMe
{
    public:
        static int parser(int argc, char **argv, std::vector<int> &arr);
    private:
        static bool HasDuplicate(std::vector<int> &arr, int value);
        static int parse_one_str(std::string str, std::vector<int> &arr);
        static int parse_input(char **argv, std::vector<int> &arr);
        static std::vector<std::pair<int,int>> makePairs(std::vector<int>& arr);
        static void    SplitPairs(std::vector<std::pair<int, int>> pairs, std::vector<int>& main_chain, 
                                std::vector<int>& pending);
    public:
        static std::vector<int> buildInsertionOrder(int size);
        static int searchBinaryPosition(std::vector<int> &main_chain, int value);

};