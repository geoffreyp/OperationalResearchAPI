#include "helper.h"

std::string generateId(){
    std::string res = "";
    std::random_device rd;

    for (int i = 0; i < 20; ++i) {
        std::mt19937 rng(rd());
        std::uniform_int_distribution<int> uni(48,90);
        auto random_integer = uni(rng);
        res = res + (char) random_integer;
    }

    return res;
};

std::string getNeighbourSolution(const std::string& solution){
    std::vector< std::string> v{explode(solution, '-')};
    std::random_shuffle (v.begin(), v.end());

    std::string neighbour = "";
    for(auto n:v){
        neighbour = neighbour + n + "-";
    }
    neighbour.pop_back();
    return  neighbour;
}

const std::vector<std::string> explode(const std::string& s, const char& c)
{
    std::string buff{""};
    std::vector<std::string> v;

    for(auto n:s)
    {
        if(n != c) buff+=n; else
        if(n == c && buff != "") { v.push_back(buff); buff = ""; }
    }
    if(buff != "") v.push_back(buff);

    return v;
}