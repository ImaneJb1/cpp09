#pragma once

#include "stdio.h"
#include "iostream"
#include "map"
#include "fstream"
#include "climits"
#include "sstream"
#include "stack"

class RPN
{
    private:
        std::stack<int> _stack;
    private:
        bool    op_and_push(int a, int b, std::string &token);
        RPN(const RPN &other);
        RPN &operator=(const RPN &other);
    public:
        RPN();
        ~RPN();
        void    calculate(char *operation);
        int     get_result();  

};