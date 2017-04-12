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

#define STD_ARRAY_SIZE 16
#define NUM_INSTANCES 100





int main () {

	// make 100 files of 100 integers
	system("./sol");


	// run Karmarkar-Karp, Hill Climbing, Repeated Random, and Simulated Annealing algorithms a hundred times
	for (int i=0; i<NUM_INSTANCES; i++) {

		char* command = malloc(sizeof(char)*STD_ARRAY_SIZE);
		sprintf(command, "./kk %d.txt", i);




		// read in kk_residue
		char* inputfile = malloc(sizeof(char)*STD_FILENAME_SIZE);
		int temp_number = 0;

		FILE* fp;
		fp = fopen(inputfile, "r");

		fgets(temp_number, sizeof(long long), fp);

		int kk_residue = temp_number;




		// now run the 3 algorithms
		char* hc_command = malloc(sizeof(char)*STD_FILENAME_SIZE);
		char* rr_command = malloc(sizeof(char)*STD_FILENAME_SIZE);
		char* sa_command = malloc(sizeof(char)*STD_FILENAME_SIZE);


		sprintf(hc_command, "./hc %d %d", i, kk_residue);
		sprintf(rr_command, "./hc %d %d", i, kk_residue);
		sprintf(sa_command, "./hc %d %d", i, kk_residue);

		system(hc_command);
		system(rr_command);
		system(sa_command);
	}
}






