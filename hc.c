/* 
CS124 - PROGRAMMING ASSIGNMENT 3
Authors: 30977521, 60977917

Description: Hill Climbing algorithm...
...
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <time.h>
#include "kk.h"

#define STD_FILENAME_SIZE 16
#define STD_ARRAY_SIZE 100
#define MAX_RANDOM_NUMBER 100
#define MAX_ITER 25000
#define STD_NUM_BUFFER_SIZE 16
#define STD_COMMAND_SIZE 16



// Calculates the residue for a given solution to a given array
long long residue_calculator (long long* A, long long* S) {
	long long residue = 0;
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



// Generates a randoms solution, comprised of -1's and 1's
void generate_random_solution (long long* S) {
	for (int i=0; i<STD_ARRAY_SIZE; i++) {

		long long random_number = rand_num(STD_ARRAY_SIZE);
		if (random_number < 50) {
			S[i] = -1;
		}
		else {
			S[i] = 1;
		}
	}
}

// move the solution array to a neighbor, by performing one random move
void rand_move (long long* S) {

	long long i = rand_num(STD_ARRAY_SIZE-1);
	long long j = rand_num(STD_ARRAY_SIZE-1);
	long long k = rand_num(STD_ARRAY_SIZE-1);

	// make sure i and j are not equal to one another
	while (i == j) {
		j = rand_num(STD_ARRAY_SIZE-1);
	}

	// swap one element
	S[i] = -S[i];

	// with probability 1/2, swap the element
	if (k < 50) {
		S[j] = -S[j];
	}
}


long long hc_standard (long long* A) {

	// make a random solution first
	long long* S = malloc(sizeof(long long)*STD_ARRAY_SIZE);
	generate_random_solution(S);

	// then iterate MAX_ITER times while doing a random move then update if residue is smaller
	for (int i=0; i<MAX_ITER; i++) {
		long long* S_prime = malloc(sizeof(long long)*STD_ARRAY_SIZE);
		for (int j=0; j<STD_ARRAY_SIZE; j++) {
			S_prime[j] = S[j];
		}

		rand_move(S_prime);

		// set S_prime to S if its residue is smaller
		long long S_residue = llabs(residue_calculator(A, S));
		long long S_prime_residue = llabs(residue_calculator(A, S_prime));

		if (S_prime_residue < S_residue) {
			for (int j=0; j<STD_ARRAY_SIZE; j++) {
				S[j] = S_prime[j];
			}
		}

		free(S_prime);
	}

	long long final_S_residue = llabs(residue_calculator(A, S));

	free(S);

	return final_S_residue;
}






void generate_random_solution_pp (long long* A, long long* P, long long* A_prime) {
	for (int i=0; i<STD_ARRAY_SIZE; i++) {
		P[i] = rand_num((STD_ARRAY_SIZE-1));
		A_prime[i] = 0;
	}

	for (int i=0; i<STD_ARRAY_SIZE; i++) {
		A_prime[(P[i])] = A_prime[(P[i])] + A[i];
	}
}


void rand_move_pp (long long* P) {
	long long i = rand_num(STD_ARRAY_SIZE-1);
	long long j = rand_num(STD_ARRAY_SIZE-1);

	while (P[i] == j) {
		j = rand_num(STD_ARRAY_SIZE-1);
	}

	P[i] = j;
}

void generate_A_prime (long long* A, long long* P, long long* A_prime) {
	for (int i=0; i<STD_ARRAY_SIZE; i++) {
		A_prime[(P[i])] = A_prime[(P[i])] + A[i];
	}
}

long long run_kk (long long* A) {

	// write a temporary file of the array
	char* temp_number = malloc(sizeof(char)*STD_NUM_BUFFER_SIZE);
	char outputfile[0x100]; 
	sprintf(outputfile, "100_random_instances/0.txt");
	FILE* wfp;
	wfp = fopen(outputfile, "w");
	for (int i=0; i<STD_ARRAY_SIZE; i++) {
		sprintf(temp_number, "%lld\n", A[i]);
		fputs(temp_number, wfp);
	}
	free(temp_number);
	fclose(wfp);

	// run the KK algorithm on the 0.txt file and return
	long long kk_residue = kk_main(0);
	return kk_residue;
}


long long hc_prepartition (long long* A) {
	long long* P = malloc(sizeof(long long)*STD_ARRAY_SIZE);
	long long* A_prime = malloc(sizeof(long long)*STD_ARRAY_SIZE);

	generate_random_solution_pp(A, P, A_prime);

	// then iterate MAX_ITER times while doing a random pp move and update if residue is smaller
	for (int i=0; i<MAX_ITER; i++) {
		
		long long* P_prime = malloc(sizeof(long long)*STD_ARRAY_SIZE);
		long long* A_double_prime = malloc(sizeof(long long)*STD_ARRAY_SIZE);

		for (int j=0; j<STD_ARRAY_SIZE; j++) {
			P_prime[j] = P[j];
		}

		rand_move_pp(P_prime);
		generate_A_prime(A, P_prime, A_double_prime);


		long long P_residue = llabs(run_kk(A_prime));
		long long P_prime_residue = llabs(run_kk(A_double_prime));

		if (P_prime_residue < P_residue) {
			for (int j=0; j<STD_ARRAY_SIZE; j++) {
				P[j] = P_prime[j];
				A_prime[j] = A_double_prime[j];
			}
		}

		free(P_prime);

		free(A_double_prime);
	}

	long long final_P_residue = llabs(run_kk(A_prime));
	free(A_prime);
	free(P);

	return final_P_residue;
}






int main (int argc, char *argv[]) {
	// randomizing seed
	srand((unsigned) time(NULL));

	// parse the command line arguments
	char inputfile[0x100]; 
	sprintf(inputfile, "100_random_instances/%d.txt", atoi(argv[1]));
	int kk_residue = atoi(argv[2]);


	// read the integers line by line
	long long* A = malloc(sizeof(long long)*STD_ARRAY_SIZE);
	char* temp_number = malloc(sizeof(char)*STD_NUM_BUFFER_SIZE);
	int counter = 0;

	FILE* fp;
	fp = fopen(inputfile, "r");

	// while (fgets(temp_number, STD_NUM_BUFFER_SIZE, fp)) {
	// 	A[counter] = atoll(temp_number);
	// 	counter++;
	// }
	
    for (int i =0; i < STD_ARRAY_SIZE; i++) {
        // printf("HELLO"); 
        // exit(0);
        fgets(temp_number, STD_NUM_BUFFER_SIZE, fp);
        A[i] = atoll(temp_number);
    }
	

	long long hc_standard_residue = hc_standard(A);
	long long hc_prepartition_residue = hc_prepartition(A);

	printf("The residue after Hill Climbing in standard representation is: %lld\n", hc_standard_residue);
	printf("The residue after Hill Climbing in prepartition representation is: %lld\n", hc_prepartition_residue);

	//free(temp_number);
	//free(A);
	fclose(fp);
}







