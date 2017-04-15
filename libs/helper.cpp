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

//std::cout<<res;
    return res;
};