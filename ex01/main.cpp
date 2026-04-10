#include "RPN.hpp"

bool    op_and_push(int a, int b, std::string &token, std::stack<int> &stack)
{
    if(token == "+") stack.push(a + b);
    else if(token == "*") stack.push(a * b);
    else if(token == "-") stack.push(a - b);
    else if(token == "/" && b != 0) stack.push(a / b);
    else return false;
    return true;
}

int    calculate(std::stack<int> &stack, char *operation)
{
    std::istringstream iss(operation);
    std::string token;
    while(iss >> token)
    {
        if(isdigit(token[0]))
        {
            // std::cout << token[0] << "\n";
            int num = atoi(token.c_str());
            stack.push(num);
        }
        else if(stack.size() >= 2)
        {
            int b = stack.top(); stack.pop();
            int a = stack.top(); stack.pop();
            if(!op_and_push(a, b, token, stack))
                return 0;
        }
        else
            return 0;
    }
    return 1;
}


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
    // std::istringstream iss(argv[1]);
    // std::string token;
    std::stack<int> stack;
    if(!calculate(stack, argv[1]))
    {
        std::cout << "Error\n";
        return 1;
    }
    if(!stack.empty() && stack.size() == 1)
        std::cout << stack.top() << std::endl;
    else
    {
        std::cout << "Error\n";
        return 1;
    }
    return 0;
}
