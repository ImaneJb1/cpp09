#pragma once

#include <cstddef>
#include <stdlib.h>
#include <iostream>
#include "cmath"
#include "climits"
#include "vector"
#include <ctime>
#include <iomanip>
#include <deque>
#include <vector>



struct s_node
{
    int value;
    size_t id;
};

struct s_pending_node
{
    s_node node;
    size_t bigPairId;
};


class PmergeMe
{
    private:
        std::vector<s_node> m_vector;
        std::deque<s_node> m_deque;
    public:
        PmergeMe(int argc, char **argv);
    private:
        template<typename Container>
        static bool HasDuplicate(Container &arr, int value);
        int parse_one_str(std::string str);
        int parse_input(char **argv);

        template<typename Container>
        static std::vector<std::pair<s_node,s_node> > makePairs(Container& arr);
        template<typename Container>
        static void    SplitPairs(std::vector<std::pair<s_node, s_node> > pairs, Container& main_chain, 
                                std::vector<s_pending_node>& pending);
    public:
        std::vector<int> buildInsertionOrder(int size);
        size_t getSize() const;
        template<typename Container>
        int searchBinaryPosition(Container &main_chain, s_pending_node &value,  size_t bigId, int odd) const;
        void printVec() const;
        
        template<typename Container>
        void FordJhonson(Container& container);
        void    runAlgo();
        ~PmergeMe();

    private:
        PmergeMe();
        PmergeMe(const PmergeMe &other);
        PmergeMe &operator=(const PmergeMe &other);
};
