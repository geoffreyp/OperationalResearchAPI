#include "functions.h"


int main(int argc, char *argv[]) {
    /*
     * Init
     */
    int size=0, nbEvalMax=0;
    int initp = initParameters(argc, argv, &size, &nbEvalMax);
    if(initp != 0) {
        printf("Oh, Something bad happened !");
        return -1;
    }

    int solution[size];

    loadInitialSolution(solution, size);

    int fitness = askFitness(solution, size);
    printf("Fitness value for solution initial = %d", fitness);

    for (int i = 0; i < nbEvalMax; ++i) {
        int tmp[size];
        chooseBetterSolution(solution,size,fitness,nbEvalMax, tmp);
    }

    return 0;
}
