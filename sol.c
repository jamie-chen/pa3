#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define STD_ARRAY_SIZE 100
#define STD_FILENAME_SIZE 64
#define LIM 100

long long rand_num(void); 

int main(int argc, char** argv) {
	srand((unsigned) time(NULL));
	int n = atoi(argv[1]); 

	for (int j = 0; j < n; j++) {

		// number of 100-int files to print

		char filename[0x100]; 
		sprintf(filename, "100_random_instances/%d.txt", j+1);
		FILE *fp = fopen(filename,"w+");
		
		// long long sum = 0; 


		for (int i = 0; i < STD_ARRAY_SIZE; i++) {
			long long rand = rand_num(); 
			fprintf(fp, "%lld\n", rand); 
			// sum+=rand; 
		}


		// long long avg = sum / 100;
		// printf("average: %lld\n", avg);

		fclose(fp);
	}
	return 0;
}

long long rand_num(void) {
	// generate random double, seeded with time for true randomness
	double rand_1 = (double) rand();
	// calculate the max value rand can return
	double max_rand = (double) RAND_MAX;
	// divide the two to make everything between 0 and 1
	float factor = (float) (rand_1/max_rand);

	long long rand = LIM * factor + 1; 
	return rand; 

}