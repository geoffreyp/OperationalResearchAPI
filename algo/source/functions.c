//
// Created by geoffrey on 26/03/17.
//
#include "functions.h"

int initParameters(int argc, char * argv[], int * sizeOfSolution, int * numberOfEvaluation){
    /*
     * Test arguments
     */
    if(argc < 5){
        return -1;
    }
    for (int i = 1; i < argc; i+=2) {
        if(strcmp(argv[i], "--size") == 0)
            *sizeOfSolution = atoi(argv[i+1]);
        if(strcmp(argv[i], "--nbeval") == 0)
            *numberOfEvaluation = atoi(argv[i+1]);
    }
    if(*sizeOfSolution == 0){
        printf("Error : size can't equals zero\n");
        return -1;
    }
    if(*numberOfEvaluation == 0){
        printf("Error : numberOfEvaluation can't equals zero\n");
        return -1;
    }

    printf("Parameters : ");
    printf("size=%d / nbEval=%d\n", *sizeOfSolution, *numberOfEvaluation);
    return 0;
}

void loadInitialSolution(int *solution, int size) {

   printf("{\"message\":\"claim_initial_solution\"}\n");

    int i = 0;
    char buf[BUFFER_SIZE];
    read(0,buf,sizeof(buf));
    char *token = strtok(buf, "-");

    while (token != NULL)
    {
        solution[i] = atoi(token);
        if(i<size){
            i++;
        } else{
            return;
        }
        token = strtok(NULL, "-");
    }
}

int askFitness(const int *solution, int size) {
    printf("{\"message\":\"claim_fitness\",\"solution\":[");
    for (int i = 0; i < size; ++i) {
        printf("%d", *(solution + i));
        if (i < size - 1) {
            printf(",");
        }
    }
    printf("]}\n");
    char buf[BUFFER_SIZE];
    read(0,buf,sizeof(buf));

    return atoi(buf);
}

void chooseBetterSolution(const int * solution, int size, int fitness, int nbEval, int * betterSolution){
    copyTab(solution, betterSolution, size);
    swapTwoItems(betterSolution,size);
    //int betterFitness = askFitness(betterSolution,size);
}

void copyTab(const int * original, int * copy, int size){
    for (int i = 0; i < size; ++i) {
        copy[i] = original[i];
    }
}

void swapTwoItems(int * solution, int size){

}