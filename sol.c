#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

long long rand_num(void); 

int main(void) {
	srand((unsigned) time(NULL));

	for (int j = 0; j < 100; j++) {

		char filename[0x100]; 
		snprintf(filename, sizeof(filename), "%d.txt", j+1);
		FILE *fp = fopen(filename,"w+");

		
		// long long sum = 0; 


		for (int i = 0; i < 100; i++) {
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

	long long rand = 1000000000000 * factor + 1; 
	return rand; 

}