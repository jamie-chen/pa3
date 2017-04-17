/* 
CS124 - PROGRAMMING ASSIGNMENT 3
Authors: 30977521, 60977917

Description: Main controller program
...
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <time.h>

#define STD_COMMAND_SIZE 16
#define STD_FILENAME_SIZE 8
#define NUM_INSTANCES 100
#define STD_NUM_BUFFER_SIZE 16





int main () {

	// make 100 files of 100 integers
	char* sol_command = malloc(sizeof(char)*STD_COMMAND_SIZE);
	sprintf(sol_command, "./sol %d", NUM_INSTANCES);
	system(sol_command);


	// run Karmarkar-Karp, Hill Climbing, Repeated Random, and Simulated Annealing algorithms a hundred times
	for (int i=0; i<NUM_INSTANCES; i++) {

		char* kk_command = malloc(sizeof(char)*STD_COMMAND_SIZE);
		sprintf(kk_command, "./kk %d", i+1);

		// run the Karmarkar-Karp algorithm
		system(kk_command);


		// read in kk_residue
		char* inputfile = malloc(sizeof(char)*STD_FILENAME_SIZE);
		sprintf(inputfile, "kk_residue.txt");
		char* temp_number = malloc(sizeof(char)*STD_NUM_BUFFER_SIZE);

		FILE* fp;
		fp = fopen(inputfile, "r");

		fgets(temp_number, sizeof(long long), fp);

		int kk_residue = atoll(temp_number);


		// now run the 3 algorithms
		char* hc_command = malloc(sizeof(char)*STD_FILENAME_SIZE);
		char* rr_command = malloc(sizeof(char)*STD_FILENAME_SIZE);
		char* sa_command = malloc(sizeof(char)*STD_FILENAME_SIZE);


		sprintf(hc_command, "./hc %d %d", i, kk_residue);
		sprintf(rr_command, "./hc %d %d", i, kk_residue);
		sprintf(sa_command, "./hc %d %d", i, kk_residue);

		system(hc_command);
		printf("finished round %d\n", i);
		system(rr_command);
		system(sa_command);
		printf("finished round %d\n", i);
	}
}






