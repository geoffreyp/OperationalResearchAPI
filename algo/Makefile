all : source/main.o source/functions.o
	gcc source/main.o source/functions.o -o bin/HillClimberFirstImprovement

main.o : source/main.c source/functions.c
	gcc -c source/main.c -o source/main.o

functions.o : source/functions.c
	gcc -c source/functions.c -o source/functions.o
