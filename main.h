#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <time.h>


//prepartition 
void rand_move(long long* S);
long long rand_num(long long lim); 
void prepartition(long long* S, long long* A_p);
void print_array(long long* arr, int size);
void pp_randmove(long long * S);
void prepartition(long long* S, long long *A_p);

//sa.c 
long long residue_calculator (long long* A, long long* S);
double rand_num_double ();
void generate_random_solution (long long* S);
double cooling_schedule (int iter);
long long sa_standard (long long* A);


//kk.c
void MergeSort(long long arr[], int l, int r); 
void merge(long long arr[], int l, int m, int r); 
long long kk (long long* A); 

//hc.c
long long hc_standard (long long* A);

// PREPARTITION 
long long rand_num(long long lim) {
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

 long long kk (long long* A) {
	int elt_remaining = STD_ARRAY_SIZE; 
	int res = 0; 

	// keep track of max indices in the sorted array 
	int max = STD_ARRAY_SIZE - 1; 
	int max_2 = STD_ARRAY_SIZE - 2;
	

	while (elt_remaining > 0) {

		MergeSort(A, 0, max); 
		int temp = A[max] - A[max_2];
		A[max] = temp; 
		A[max_2] = 0; 
		elt_remaining--; 
	}

	// find residue (non zero element)
	for (int i =0; i < STD_ARRAY_SIZE; i++) {
		if (A[i] != 0) {
			res = A[i]; 
		}
	}

	return res; 
}

