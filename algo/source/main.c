#include "functions.h"


int main(int argc, char *argv[]) {
    /*
     * Init
     */
    int size=0, nbEval=0;
    int initp = initParameters(argc, argv, &size, &nbEval);
    if(initp != 0) {
        printf("Oh, Something bad happened !");
        return -1;
    }

    int solution[size];

    loadInitialSolution(solution, size);

    int fitness = askFitness(solution, size);
    printf("Fitness value for solution initial = %d", fitness);

    return 0;
}
