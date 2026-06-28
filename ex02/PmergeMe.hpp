#pragma once

#include <stdlib.h>
#include <iostream>
#include "cmath"
#include "climits"
#include "vector"
#include <ctime>
#include <iomanip>
#include <deque>

template <typename Container>
class PmergeMe
{
    public:
        static int parser(int argc, char **argv, Container &arr);
    private:
        static bool HasDuplicate(Container &arr, int value);
        static int parse_one_str(std::string str, Container &arr);
        static int parse_input(char **argv, Container &arr);
        static std::vector<std::pair<int,int>> makePairs(Container& arr);
        static void    SplitPairs(std::vector<std::pair<int, int>> pairs, Container& main_chain, 
                                Container& pending);
    public:
        static Container buildInsertionOrder(int size);
        static int searchBinaryPosition(Container &main_chain, int value);
        static void mergeInstertVector(Container& arr);
        ~PmergeMe();

    private:
        PmergeMe();
        PmergeMe(const PmergeMe &other);
        PmergeMe &operator=(const PmergeMe &other);
};

#include "PmergeMe.tpp"