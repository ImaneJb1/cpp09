#pragma once

#include "iostream"
#include "map"
#include "fstream"
#include "climits"
std::map<std::string, double>   &parse_csv(std::map<std::string, double> &data);
int parse_input(char *filename, std::map<std::string, double> &data);
std::map<std::string, double>     &read_csv(std::ifstream &file, std::map<std::string, double> &data);
void    convert_print(std::map<std::string, double> &data, std::string input, std::string value);