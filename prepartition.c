
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <time.h>
#include "main.h"

#define STD_ARRAY_SIZE 100

void rand_move(long long* S);
long long rand_num(int lim); 
void prepartition(long long* S, long long* A_p);
void print_array(long long* arr, int size);

int main(int argc, char *argv[]) {

	srand((unsigned) time(NULL));
	// read from input file in command line 
    char inputfile[0x100]; 
    int f = atoi(argv[1]); 
    sprintf(inputfile, "100_random_instances/%d.txt", f);

    // read the integers line by line
    long long* A = malloc(sizeof(long long)*STD_ARRAY_SIZE);
    char* str = malloc(sizeof(char) * 12);
    int counter = 0;

    FILE* fp;
    fp = fopen(inputfile, "r");
 
    // read into array 
    for (int i =0; i < STD_ARRAY_SIZE; i++) {
        // printf("HELLO"); 
        // exit(0);
        fgets(str, 12, fp);
        A[i] = atoll(str);
    }

    print_array(A, STD_ARRAY_SIZE); 

	rand_move(A);

	print_array(A, STD_ARRAY_SIZE);

	// long long* prepart = malloc(sizeof(long long)*STD_ARRAY_SIZE); 
	// prepartition(A, prepart); 

	// print_array(prepart, STD_ARRAY_SIZE); 
}


void rand_move(long long* S) {

	long long i = rand_num(100); 
	long long j = rand_num(100); 
	long long k = rand_num(100);

	printf("i: %lld, j: %lld\n", i, j);

	while (j == i) {
		j = rand_num(100); 
	}

	// swap one element 
	S[i] = -S[i]; 

	// with probability 1/2, swap the other element 
	if (k < 50) {
		S[j] = -S[j]; 
	}

}


void prepartition(long long* S, long long *A_p) {

	long long P[STD_ARRAY_SIZE]; 

	// initialize all A_p to 0, P to random ints between 1, 100 
	for (int i = 0; i < STD_ARRAY_SIZE; i++) {
		P[i] = rand_num(STD_ARRAY_SIZE); 
		A_p[i] = 0; 
	}
	print_array(P, STD_ARRAY_SIZE);

	// prepartition
	for (int j = 0; j < STD_ARRAY_SIZE; j++) {
		A_p[(P[j])] = A_p[(P[j])] + S[j]; 
	}


 }

 void pp_randmove(long long * S) {
 	long long i = rand_num(100); 
	long long j = rand_num(100); 

	while (j == S[i]) {
		j = rand_num(100); 
	}

	S[i] = j; 

 }

// generates random number in [1, lim] 
long long rand_num (int lim) {

	// generate random double, seeded with time for true randomness
	double rand_1 = (double) rand();
	// calculate the max value rand can return
	double max_rand = (double) RAND_MAX;
	// divide the two to make everything between 0 and 1
	float factor = (float) (rand_1/max_rand);

	long long rand = lim * factor + 1; 
	return rand; 
}

void print_array(long long* arr, int size) {
	printf("ARRAY: [");
	for (int i =0; i < size; i++ ) {
		printf("%lld, ", arr[i]); 
	}
	printf("]\n"); 
}
