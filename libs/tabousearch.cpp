#include "tabousearch.h"


void addMoveInTabuList(){
    // TODO
}

bool moveIsAllowed(){
    // TODO
}

std::vector<std::string> getAllNeighbors(std::string solution){
    /**
     * Example : s = 1-2-3-4
     * N(s) with i=0 = {2-1-3-4; 3-1-2-4; 4-2-3-1}
     * N(s) with i=1 = {2-1-3-4; 1-3-2-4; 1-4-3-2}
     * N(s) with i=2 = {3-2-1-4; 1-3-2-4; 1-2-4-3}
     * N(s) with i=3 = {4-2-3-1; 1-4-3-2; 1-2-4-3}
     */
    std::cout << "in1" << std::endl;
    std::vector<std::string> vSolution{explode(solution, '-')};
    std::cout << "in2" << std::endl;
    std::vector<std::string> vAllNeighbors;
    std::cout << "in3" << std::endl;
    for (int i=0; i < vSolution.size(); i++) {
        for (int j=0; j < vSolution.size(); j++) {
            if (i != j){
                std::vector<std::string> vNeighbor = vSolution;
                std::string tmp = vNeighbor[i];
                vNeighbor[i] = vNeighbor[j];
                vNeighbor[j] = tmp;
                vAllNeighbors.push_back(vectorToString(vNeighbor));
            }
        }
    }

    return vAllNeighbors;
}