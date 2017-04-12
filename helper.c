#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <time.h>


void rand_move(int* S);
long long rand_num(int lim); 



int main(void) {
	int S[100]; 

	rand_move(S); 
}


void rand_move(int* S) {

	int i = rand_num(100); 
	int j = rand_num(100); 

	while (j == i) {
		j = rand_num(100); 
	}

	// swap one element 
	S[i] = -S[i]; 

	// with probability 1/2, swap the other element 
	if (i < 50) {
		S[j] = -S[j]; 
	}

}


// generates random number in [1, lim] 
long long rand_num(int lim) {
	// generate random double, seeded with time for true randomness
	double rand_1 = (double) rand();
	// calculate the max value rand can return
	double max_rand = (double) RAND_MAX;
	// divide the two to make everything between 0 and 1
	float factor = (float) (rand_1/max_rand);

	long long rand = lim * factor + 1; 
	return rand; 

}