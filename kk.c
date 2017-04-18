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
#include "main.h"

#define STD_FILENAME_SIZE 16
#define STD_ARRAY_SIZE 100


void MergeSort(long long arr[], int l, int r); 
void merge(long long arr[], int l, int m, int r); 
void print_array(long long* arr, int size);
long long kk (long long* A); 



int main (int argc, char *argv[]) {

	// read from input file in command line 
    char inputfile[0x100]; 
    int f = atoi(argv[1]); 
    sprintf(inputfile, "100_random_instances/%d.txt", f);

    // read the integers line by line
    long long* A = malloc(sizeof(long long)*STD_ARRAY_SIZE);
    char* str = malloc(sizeof(char) * 12);
    int counter = 0;


    FILE* fp;
    fp = fopen(inputfile, "r");

    // read into array 
    for (int i =0; i < STD_ARRAY_SIZE; i++) {
        // printf("HELLO"); 
        // exit(0);
        fgets(str, 11, fp);
        A[i] = atoll(str);
    }

    // print for testing purposes 
    //print_array(A, STD_ARRAY_SIZE);

    // run KK algorithm 
	long long residue = kk(A);

	printf("The residue after Karmarkar-Karp algorithm is: %lld\n", residue);



	// now make a temporary kk_residue file
	char* outputfile = malloc(sizeof(char)*STD_FILENAME_SIZE);
	sprintf(outputfile, "kk_residue.txt");

	// print residue to file "kk_residue" to check later 
	FILE* wfp;
	wfp = fopen(outputfile, "w");

	char* final = malloc(sizeof(char) * 12); 
	sprintf(final, "%lld", residue); 
	fputs(final, wfp);
	
	fclose(fp); 
	fclose(wfp);

	free(outputfile);
    free(str); 
    free(final);
	free(A);

}


// helper funciton for Karmarkar-Karp algorithm 
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


// helper function for mergesort 
void merge(long long arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
 
    /* create temp arrays */
    int L[n1], R[n2];
 
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
 
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }

}
 
// l is for left index and r is right index of the
// sub-array of arr to be sorted
void MergeSort(long long arr[], int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;
 
        // Sort first and second halves
        MergeSort(arr, l, m);
        MergeSort(arr, m+1, r);
 
        merge(arr, l, m, r);
    }
}

// print array helper function (for testing purposes)
void print_array(long long* arr, int size) {
	printf("ARRAY: [");
	for (int i =0; i < size; i++ ) {
		printf("%lld, ", arr[i]); 
	}
	printf("]\n"); 
}




