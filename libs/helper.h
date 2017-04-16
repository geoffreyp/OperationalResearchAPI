//
// Created by geoffrey on 15/04/17.
//

#ifndef OPERATIONALRESEARCHAPI_HELPER_H
#define OPERATIONALRESEARCHAPI_HELPER_H
#include <random>
#include <string>
#include <iostream>
#include <algorithm>

std::string generateId();
std::string getNeighbourSolution(const std::string& solution);
const std::vector<std::string> explode(const std::string& s, const char& c);

#endif //OPERATIONALRESEARCHAPI_HELPER_H
