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

    
    clock_t start = clock(); // cpu ticks before


    // PmergeMe::mergeInstertVector(arr);
    
    std::vector<int> tmp = arr;
    for (int i = 0; i < 1000; i++)
    {
        PmergeMe::mergeInstertVector(tmp);
    }
    clock_t end = clock(); // cpu ticks after
    std::cout << "After:  ";
    printVec(tmp);
    double time = static_cast<double>(end - start) * 1000000.0  / CLOCKS_PER_SEC;
    time /= 1000.0;
  
    std::cout << "Time to process a range of ";
    std::cout << arr.size();
    std::cout << " elements with std::clock : ";
    std::cout << std::fixed << std::setprecision(10);
    std::cout << time;
    std::cout << " us\n";
    return 0;
}