#include "PmergeMe.hpp"

void printVec(const std::vector<int>& v)
{
    for (size_t i = 0; i < v.size(); i++)
        std::cout << v[i] << " ";
    std::cout << std::endl;
}

int main(int argc, char **argv)
{
    std::vector<int> arr;

    if (!PmergeMe::parser(argc, argv, arr))
    {
        std::cout << "Error: invalid input\n";
        return 1;
    }

    std::cout << "Before: ";
    printVec(arr);

    PmergeMe::mergeInstertVector(arr);

    std::cout << "After:  ";
    printVec(arr);

    return 0;
}