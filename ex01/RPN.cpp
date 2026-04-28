#include "RPN.hpp"

RPN::RPN(){}

RPN::~RPN(){}

RPN::RPN(const RPN &other){(void) other;}

RPN &RPN::operator=(const RPN &other)
{
    (void) other;
    return *this;
}

bool    RPN::op_and_push(int a, int b, std::string &token)
{
    if(token == "+") _stack.push(a + b);
    else if(token == "*") _stack.push(a * b);
    else if(token == "-") _stack.push(a - b);
    else if(token == "/" && b != 0) _stack.push(a / b);
    else return false;
    return true;
}

void    RPN::calculate(char *operation)
{
    std::istringstream iss(operation);
    std::string token;
    while (!_stack.empty())
        _stack.pop();
    while(iss >> token)
    {
        if(isdigit(token[0])){
            for(size_t i = 0; i < token.size(); i++)
            {
                if(!isdigit(token[i]))
                    throw std::runtime_error("Error"); 
            }
            int num = atoi(token.c_str());
            _stack.push(num);
        }
        else if(_stack.size() >= 2)
        {
            int b = _stack.top(); _stack.pop();
            int a = _stack.top(); _stack.pop();
            if(!op_and_push(a, b, token))
                throw std::runtime_error("Error");
        }
        else
            throw std::runtime_error("Error");

    }
}

int RPN::get_result()
{
    if (_stack.size() != 1)
        throw std::runtime_error("Error");

    return _stack.top();
}