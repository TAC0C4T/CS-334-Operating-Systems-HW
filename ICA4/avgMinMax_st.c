#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int arraySize;
double average = 0;
int maximum = 0;
int minimum = 0;

struct timeval stime, etime;

void avgValue(void *numList);	/* thread for calculating average value */
void minValue(void *numList); 	/* thread for calculating minimum value */
void maxValue(void *numList);	/* thread for calculating maximum value */

int main(int argc, char *argv[])
{
	gettimeofday(&stime, NULL);



	/* perform input sanity check */
	 
	if(argc <= 2) {
		fprintf(stderr, "Usage: ./a.out <integer value>*\n");
		return -1;
	}




	/* initialize and populate a dynamically-allocated array to store user-defined data from the command-line */

	arraySize = argc - 1;
	int *arr = (int *)malloc(sizeof(int) * arraySize);
	for(int i = 0; i < arraySize; i++) {
		arr[i] = atoi(argv[i+1]);
	}

	

	
	/* print the user-defined data from the dynamic array */

	for (int i = 0; i < arraySize; i++) {
		printf("%d ", arr[i]);
	}
	


	printf("\n");
	
    avgValue(arr);
    minValue(arr);
    maxValue(arr);

	

	
	/* de-allocate the dynamic array */
	free(arr);



	/* print the final output */
	printf("\nThe average value is %d\n", (int)average);
	printf("The minimum value is %d\n", minimum);
	printf("The maximum value is %d\n", maximum);
	gettimeofday(&etime, NULL);

	printf("Time: %dms\n", etime.tv_usec - stime.tv_usec);

	return 0;
} // end of main 


/* AVG_THREAD will begin control in this function */
void avgValue(void *numArr)
{
	//numArr = (int*) numArr;
	int total = 0;
	for (int i = 0; i < arraySize; i++) {
		total += ((int*)numArr)[i];
	}	
	average = total / arraySize;
} // end of avgValue


/* MIN_THREAD will beging contril in this function */
void minValue(void *numArr)
{
	int min = ((int*)numArr)[0];
	for (int i = 0; i < arraySize; i++) {
		if (((int*)numArr)[i] < min) {
			min = ((int*)numArr)[i];
		}
	}	
	minimum = min;

} // end of minValue


/* MAX_THREAD will begin control here */
void maxValue(void *numArr)
{
	int max = ((int*)numArr)[0];
	for (int i = 0; i < arraySize; i++) {
		if (((int*)numArr)[i] > max) {
			max = ((int*)numArr)[i];
		}
	}	
	maximum = max;

} // end of maxValue                                                                                                            
