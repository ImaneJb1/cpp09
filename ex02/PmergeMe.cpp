#include "PmergeMe.hpp"
#include <ctime>
#include <stdexcept>

int g_comparison = 0;
PmergeMe::PmergeMe(int argc, char **argv)
{
    if(argc == 2)
    {
        if(!parse_one_str(argv[1]))
            throw std::runtime_error("Error: invalid input");  
    }
    else if(!parse_input(argv))
        throw std::runtime_error("Error: invalid input");
    std::cout << "Before: ";
    printVec();
    runAlgo();


}

PmergeMe::PmergeMe()
{}
PmergeMe::PmergeMe(const PmergeMe &other)
{
    (void)other;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other){
    (void)other;
    return *this;
}

PmergeMe::~PmergeMe(){}

template <typename Container>
bool PmergeMe::HasDuplicate(Container &arr, int value)
{
    if(arr.empty())
        return false;;
    for(size_t i = 0; i < arr.size(); i++)
    {
        if(arr[i].value == value)
            return true;
    }
    return false;
}

int PmergeMe::parse_one_str(std::string str)
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
        if(HasDuplicate(m_vector, num))
            return 0;
        s_node node;
        node.value = num;
        node.id = i - 1;
        m_vector.push_back(node);
        m_deque.push_back(node);
        value = "";   
    }
    return 1;
}

int PmergeMe::parse_input(char **argv)
{
    for(int i = 1; argv[i]; i++)
    {
        char *rest;
        double num = strtod(argv[i], &rest);
        if(*rest || num < 0 || num > INT_MAX)
            return 0;
        if(num != std::floor(num))
            return 0;
        if(HasDuplicate(m_vector, num))
            return 0;
        s_node node;
        node.value = num;
        node.id = i - 1;
        m_vector.push_back(node);
        m_deque.push_back(node);
    }
    return 1;
}




///////////////////////////////////////
template <typename Container>
std::vector<std::pair<s_node,s_node> > PmergeMe::makePairs(Container& container)
{
    std::vector<std::pair<s_node, s_node> > pairs;
    
    for(size_t i = 0; i + 1 < container.size(); i += 2)
    {
        s_node first;
        s_node second;
        first = container[i];
        second = container[i + 1];
        g_comparison += 1;
        if(second.value > first.value) // ==============================> comparison
            std::swap(first, second);
        pairs.push_back(std::make_pair(first,second));
    }
    return pairs;
}
template <typename Container>
void    PmergeMe::SplitPairs(std::vector<std::pair<s_node, s_node> > pairs, Container& main_chain, 
                                std::vector<s_pending_node>& pending)
{
    for(size_t i =0 ; i < pairs.size(); i++)
    {
        main_chain.push_back(pairs[i].first);
        s_pending_node pending_node;
        pending_node.node = pairs[i].second;
        pending_node.bigPairId = pairs[i].first.id;
        pending.push_back(pending_node);
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

template<typename Container>
int PmergeMe::searchBinaryPosition(Container &main_chain, s_pending_node &value, size_t bigId, int odd) const
{
    int left = 0;
    int right = bigId;
    if(!odd)
    {
        for(size_t i = 0; i < main_chain.size(); i++)
        {
            if(main_chain[i].id == bigId)
            {
                right = i;
                break;
            }
        }
    }
    int mid = 0;
    while(left < right)
    {
        mid = (left + right)/2;
        g_comparison += 1;
        if(main_chain[mid].value < value.node.value)
            left = mid + 1;
        else
            right = mid;
    }
    return left;
}

void    PmergeMe::runAlgo()
{
    clock_t vec_start = clock();
    FordJhonson(m_vector);
    std::cout << "After:  ";
    printVec();
    clock_t vec_end = clock();
    double vec_time = static_cast<double>(vec_end - vec_start) * 1000000.0 / CLOCKS_PER_SEC;
    
    g_comparison = 0;
    
    clock_t deq_start = clock();
    FordJhonson(m_deque);
    clock_t deq_end = clock();
    double deq_time = static_cast<double>(deq_end - deq_start) * 1000000.0 / CLOCKS_PER_SEC;
    
    std::cout << std::fixed << std::setprecision(5);
    std::cout << "Time to process a range of "
            << getSize()
            << " elements with std::vector : "
            << vec_time << " us\n";

    std::cout << "Time to process a range of "
            << getSize()
            << " elements with std::deque : "
            << deq_time << " us\n";
    // std::cout << "the program made " << g_comparison << " comparisons\n";
}

template <typename Container>
void printarr(const Container& v)
{
    for (size_t i = 0; i < v.size(); i++)
    {
        std::cout << v[i].node.value << " ";

    }
    std::cout << "\n";
    for (size_t i = 0; i < v.size(); i++)
    {
        std::cout << v[i].node.id << " ";

    }
    std::cout << "\n";
    for (size_t i = 0; i < v.size(); i++)
    {
        std::cout << v[i].bigPairId << " ";

    }
    std::cout << std::endl;
}

template <typename Container>
void PmergeMe::FordJhonson(Container& container)
{
    //base case
    if(container.size() <= 1)
        return;
    std::vector<std::pair<s_node, s_node> > pairs = makePairs(container);

    Container main_chain;
    std::vector<s_pending_node> pending;

    SplitPairs(pairs, main_chain, pending);

    FordJhonson(main_chain);

    std::vector<int> order = buildInsertionOrder(pending.size());
    
    for(size_t i = 0; i < order.size(); i++)
    {
        int pos = searchBinaryPosition(main_chain, pending[order[i]], pending[order[i]].bigPairId, 0);
        main_chain.insert(main_chain.begin() + pos, pending[order[i]].node);
    }
    if(container.size() % 2 != 0)
    {
        s_pending_node last;
        last.node = container.back();
        int pos = searchBinaryPosition(main_chain, last, main_chain.size(), 1);
        main_chain.insert(main_chain.begin() + pos, last.node);
    }

    container = main_chain;
}

size_t PmergeMe::getSize() const
{
    return m_vector.size();
}

void PmergeMe::printVec() const
{
    for (size_t i = 0; i < m_vector.size(); i++)
        std::cout << m_vector[i].value << " ";
    std::cout << std::endl;
}