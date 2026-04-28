#include "RPN.hpp"

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        std::cout << "Error\n";
        return 1;
    }
    if(argv[1][0] == 0) 
    {
        std::cout << "Error\n";
        return 1;
    }
    RPN rpn;
    std::stack<int> stack;
    try
    {
        rpn.calculate(argv[1]);
        std::cout << rpn.get_result() << std::endl;
    }
    catch(std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}