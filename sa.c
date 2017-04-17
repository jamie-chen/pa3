/* 
CS124 - PROGRAMMING ASSIGNMENT 3
Authors: 30977521, 60977917

Description: Simulated Annealing algorithm...
...
*/



#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <time.h>

#define STD_FILENAME_SIZE 16
#define STD_ARRAY_SIZE 100
#define MAX_RANDOM_NUMBER 100
#define MAX_ITER 25000
#define STD_NUM_BUFFER_SIZE 16






// Calculates the residue for a given solution to a given array
int residue_calculator (int* A, int* S) {
	int residue = 0;
	for (int i=0; i<STD_ARRAY_SIZE; i++) {
		residue += (A[i] * S[i]);
	}
	return residue;
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

// generates random number in [0, 1] 
float rand_num_double () {
	// generate random double, seeded with time for true randomness
	double rand_1 = (double) rand();
	// calculate the max value rand can return
	double max_rand = (double) RAND_MAX;
	// divide the two to make everything between 0 and 1
	double factor = (rand_1/max_rand);

	return factor;
}







// Generates a randoms solution, comprised of -1's and 1's
void generate_random_solution (int* S) {
	for (int i=0; i<STD_ARRAY_SIZE; i++) {

		long long random_number = rand_num(100);
		if (random_number < 50) {
			S[i] = -1;
		}
		else {
			S[i] = 1;
		}
	}
}

// move the solution array to a neighbor, by performing one random move
void rand_move (int* S) {

	int i = rand_num(100);
	int j = rand_num(100);
	int k = rand_num(100);

	// make sure i and j are not equal to one another
	while (i == j) {
		j = rand_num(100);
	}

	// swap one element
	S[i] = -S[i];

	// with probability 1/2, swap the element
	if (k < 50) {
		S[j] = -S[j];
	}
}

double cooling_schedule (int iter) {
	double answer = pow(10, 10) * pow(0.8, (((double)iter)/300));
	return answer;
}


int sa_standard (int* A) {

	// make a random solution first
	int* S = malloc(sizeof(int)*STD_ARRAY_SIZE);
	generate_random_solution(S);

	// create S_double_prime which is just a copy of S
	int* S_double_prime = malloc(sizeof(int)*STD_ARRAY_SIZE);
	for (int i=0; i<STD_ARRAY_SIZE; i++) {
		S_double_prime[i] = S[i];
	}

	// ?????
	for (int i=0; i<MAX_ITER; i++) {
		// S_prime: random neighbor of S 
		int* S_prime = malloc(sizeof(int)*STD_ARRAY_SIZE);
		for (int j=0; j<STD_ARRAY_SIZE; j++) {
			S_prime[j] = S[j];
		}
		rand_move(S_prime);

		// set S_prime to S if its residue is smaller
		int S_residue = residue_calculator(A, S);
		int S_prime_residue = residue_calculator(A, S_prime);

		if (S_prime_residue < S_residue) {
			S = S_prime;
		}

		// if not, then ???
		else {
			double j = rand_num_double();
	 		double bound = exp(-((S_prime_residue - S_residue) / (cooling_schedule(i))));

			if (j < bound) {
				S = S_prime;
			}
		}


		// if the updated S's residue is lower than S double prime's then update S 
		// double prime as such
		int updated_S_residue = residue_calculator(A, S);
		int S_double_prime_residue = residue_calculator(A, S_double_prime);

		if (updated_S_residue < S_double_prime_residue) {
			S_double_prime = S;
		}

	}

	int final_S_double_prime_residue = residue_calculator(A, S_double_prime);
	return final_S_double_prime_residue;
}





int sa_prepartition (int* A) {

}







int main (int argc, char *argv[]) {

	// parse the command line arguments
	char* inputfile = malloc(sizeof(char)*STD_FILENAME_SIZE);
	inputfile = argv[1];
	int kk_residue = atoi(argv[2]);


	// read the integers line by line
	int* A = malloc(sizeof(long long)*STD_ARRAY_SIZE);
	char* temp_number = malloc(sizeof(char)*STD_NUM_BUFFER_SIZE);
	int counter = 0;

	FILE* fp;
	fp = fopen(inputfile, "r");

	while (fgets(temp_number, sizeof(long long), fp)) {
		A[counter] = atoll(temp_number);
		counter++;
	}


	int sa_standard_residue = sa_standard(A);
	int sa_prepartition_residue = sa_prepartition(A);


	printf("The residue after Simulated Annealing in standard representation is: %d\n", sa_standard_residue);
	printf("The residue after Simulated Annealing in prepartition representation is: %d\n", sa_prepartition_residue);

}






