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
    // convert solution from string to vector
    std::vector< std::string> v{explode(solution, '-')};

    // swap 2 elements
    std::random_device rd;
    std::mt19937 rng(rd());    // random-number engine used Mersenne-Twister
    std::uniform_int_distribution<int> uni(0, (int) v.size() - 1);
    auto random_integer1 = uni(rng);
    auto random_integer2 = uni(rng);

    std::string str_tmp = v[random_integer1];
    v[random_integer1] = v[random_integer2];
    v[random_integer2] = str_tmp;



    return  vectorToString(v);
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

const std::string vectorToString(std::vector<std::string> v){
    // convert solution from vector to string
    std::ostringstream oss;
    std::copy(v.begin(), v.end()-1, std::ostream_iterator<std::string>(oss, "-"));
    oss << v.back();

    return  oss.str();
}