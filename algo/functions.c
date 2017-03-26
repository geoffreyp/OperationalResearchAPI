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

void loadInitialSolution(int *tab, int size) {
    char ask[23] = "write_initial_solution";
    write(0,ask, sizeof(ask));

    int i = 0;
    char buf[BUFFER_SIZE];
    read(0,buf,sizeof(buf));
    char *token = strtok(buf, "-");

    while (token != NULL)
    {
        tab[i] = atoi(token);
        if(i<size){
            i++;
        } else{
            return;
        }
        token = strtok(NULL, "-");
    }
}

void sendSolution(int *tab, int size) {
    printf("{");
    for (int i = 0; i < size; ++i) {
        printf("%d", *(tab + i));
        if (i < size - 1) {
            printf(";");
        }
    }
    printf("}");
}
