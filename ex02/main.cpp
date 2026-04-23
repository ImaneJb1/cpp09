#include "PmergeMe.hpp"

int main(int argc, char *argv[])
{
    if(argc < 2 || !argv[1][0])
        return 0;
    std::vector<int> arr;
    if(!parser(argc, argv, arr))
    {
        std::cout << "Invalid input\n";        
        return 1;
    }
    for(size_t i = 0; i < arr.size(); i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;
    return 0;
}
