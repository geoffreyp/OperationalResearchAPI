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

    double fitness = askFitness(solution, size);
    printf("Fitness value for solution initial = %f\n", fitness);

    for (int i = 0; i < nbEvalMax; ++i) {
        int potentialBetterSolution[size];
        double  potentialBetterFitness = chooseBetterSolution(solution,size,fitness,nbEvalMax, potentialBetterSolution);

        if(potentialBetterFitness < fitness){
            fitness = potentialBetterFitness;
            copyTab(potentialBetterSolution, solution, size);
            printf("\n== DEBUG == new best fitness : %f\n",fitness);
        }
    }

    printf("{\"message\":\"finish\",\"best_fitness\":%f,\"best_solution\":[",fitness);

    for (int i = 0; i < size; ++i) {
        printf("%d", *(solution + i));
        if (i < size - 1) {
            printf(",");
        }
    }
    printf("]}\n");
    return 0;
}
