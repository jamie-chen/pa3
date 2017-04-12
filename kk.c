/* 
CS124 - PROGRAMMING ASSIGNMENT 3
Authors: 30977521, 60977917

Description: Karmarkar-Karp algorithm...
...
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <time.h>

#define STD_FILENAME_SIZE 16
#define STD_ARRAY_SIZE 100




int* kk (int* A_sorted) {

	// implementation of kk here...

}



int* mergesort (int* A, ... mergesort stuff here ...) {

	// implementation of mergesort here...

}



int main (int argc, char *argv[]) {

	// parse the command line arguments
	char* inputfile = malloc(sizeof(char)*STD_FILENAME_SIZE);
	inputfile = argv[1];


	// read the integers line by line
	long long* A = malloc(sizeof(long long)*STD_ARRAY_SIZE);
	long long temp_number = 0;
	int counter = 0;

	FILE* fp;
	fp = fopen(inputfile, "r");

	while (fgets(temp_number, sizeof(long long), fp)) {
		A[counter] = temp_number;
		counter++;
	}

	long long* A_sorted = mergesort(A, ... other arguments here ...);

	long long residue = kk(A_sorted);

	printf("The residue after Karmarkar-Karp algorithm is: %d\n", residue);




	// now make a temporary kk_residue file
	char* outputfile = malloc(sizeof(char)*STD_FILENAME_SIZE);
	sprintf(outputfile, "kk_residue");

	FILE* wfp;
	wfp = fopen(outputfile, "w");

	fputs(residue, sizeof(long long), wfp);
}



