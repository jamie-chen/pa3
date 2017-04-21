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

	printf("\n\n\n");
	printf("Creating 100 random instances...\n");
	system(sol_command);
	printf("... Finished creating 100 random instances\n");
	printf("\n\n\n\n\n");
	free(sol_command);


	printf("START ALGORITHMS\n");
	printf("\n\n\n\n\n");

	// run Karmarkar-Karp, Hill Climbing, Repeated Random, and Simulated Annealing algorithms a hundred times
	for (int i=0; i<NUM_INSTANCES; i++) {

		char kk_command[0x100]; 
		sprintf(kk_command, "./kk %d", i+1);

		printf("-----------------------------\n");
		printf("----------TRIAL %d-----------\n", i+1);


		// run the Karmarkar-Karp algorithm
		printf("Running KK Algorithm...\n");
		clock_t kk_start, kk_end;
		kk_start = clock();
		system(kk_command);
		kk_end = clock();
		printf("Running KK took %f\n", (((double) (kk_end - kk_start)) / CLOCKS_PER_SEC));
		printf("... Finished KK Algorithm\n\n");


		// read in kk_residue
		char inputfile[0x100]; 
		sprintf(inputfile, "kk_residue.txt");
		char* temp_number = malloc(sizeof(char)*STD_NUM_BUFFER_SIZE);

		FILE* fp;
		fp = fopen(inputfile, "r");

		fgets(temp_number, sizeof(long long), fp);
		fclose(fp);

		int kk_residue = atoll(temp_number);
		free(temp_number);

		// now run the 3 algorithms
		char hc_command[0x100]; 
		char rr_command[0x100]; 
		char sa_command[0x100]; 

		sprintf(rr_command, "./rr %d %d", i, kk_residue);
		sprintf(hc_command, "./hc %d %d", i, kk_residue);
		sprintf(sa_command, "./sa %d %d", i, kk_residue);

		printf("Running RR Algorithm...\n");
		system(rr_command);
		printf("... Finished RR Algorithm\n\n");

		printf("Running HC Algorithm...\n");
		system(hc_command);
		printf("... Finished HC Algorithm\n\n");

		printf("Running SA Algorithm...\n");
		system(sa_command);
		printf("... Finished SA Algorithm\n");

		printf("-----------------------------\n");
		printf("\n\n\n");
	}

	printf("\n\n\n");
	printf("ALL FINISHED\n");
	printf("\n\n\n");
	return 0;
}






