/* 
CS124 - PROGRAMMING ASSIGNMENT 3
Authors: 30977521, 60977917

Description: Repeated Random algorithm...
...
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <time.h>

#define STD_FILENAME_SIZE 16
#define STD_ARRAY_SIZE 100
#define MAX_ITER 25000




// DO STUFF HERE, one for standard representation and one for prepartition representation





int main (int argc, char *argv[]) {

	// parse the command line arguments
	char* inputfile = malloc(sizeof(char)*STD_FILENAME_SIZE);
	inputfile = argv[1];
	int kk_residue = atoi(argv[2]);


	// read the integers line by line
	int* A = malloc(sizeof(long long)*STD_ARRAY_SIZE);
	long long temp_number = 0;
	int counter = 0;

	FILE* fp;
	fp = fopen(inputfile, "r");

	while (fgets(temp_number, sizeof(long long), fp)) {
		A[counter] = temp_number;
		counter++;
	}

	// DO STUFF HERE

	printf("The residue after Hill Climbing in standard representation is: %d\n", ???);
	printf("The residue after Hill Climbing in prepartition representation is: %d\n", ???);

}








