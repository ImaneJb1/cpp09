#include "PmergeMe.hpp"

int main(int argc, char *argv[])
{
    if(argc < 2 || !argv[1][0])
        return 0;
    std::vector<int> arr;
    if(!PmergeMe::parser(argc, argv, arr))
    {
        std::cout << "Error\n";        
        return 1;
    }
    // for(size_t i = 0; i < arr.size(); i++)
        // std::cout << arr[i] << " ";
    // std::cout << std::endl;
    // std::vector<int> vc = PmergeMe::buildInsertionOrder(5);
    
    std::vector<int> vc;
    vc.push_back(2);
    vc.push_back(5);
    vc.push_back(9);
    vc.push_back(11);
    vc.push_back(23);
    vc.push_back(34);
    int pos = PmergeMe::searchBinaryPosition(vc, 67);
    std::cout << pos << "\n";

    
    // for(size_t i= 0; i < vc.size(); i++)
    // std::cout << "\n";
    return 0;
}
