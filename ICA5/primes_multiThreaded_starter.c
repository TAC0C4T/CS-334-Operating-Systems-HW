/**
 * This is a multi-threaded implementation for counting the
 * number of primes between 0 and n, where n > 0.
 *
 * This implementation creates more than one child threads 
 * using fork-join strategy; therefore, the parent process waits
 * until all child threads are done.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>

/* macro defintion */
#define NUM_THREADS 4

/* structure declaration */
struct range {
	int start;	// first value in the range
	int end;	// last value in the range
};
typedef struct range Range;
struct timeval stime, etime;

/* function declaration for thread entry point */
void *findPrimes(void *param);


/*
 * main function -- entry point for the parent process
 *
 */
int main(int argc, char *argv[])
{
	/* declare and initialize necessary variables */
	pthread_t tid1, tid2, tid3, tid4;		// the thread identifier 
	pthread_t tid[NUM_THREADS];
	pthread_attr_t attr;	// set of thread attribute
	

	/* process command-line input with sanitation checks */
	if (argc != 2) {
		fprintf(stderr, "usage: ./a.out <integer value>\n");
		return -1;
	}

	if (atoi(argv[1]) < 100) {
		fprintf(stderr, "%d must be > 999\n",atoi(argv[1]));
		return -1;
	}

	/* log the start time of program execution */
	gettimeofday(&stime, NULL);
	
	
	/* calculate the range for each subset of the initial data set of size n */
	// DUMMIED UP -- WRITE YOUR CODE HERE //
	

	/* get ready for the final output */
	// DUMMIED UP -- WRITE YOUR CODE HERE //


	/* create a thread for calculating prime numbers with in four different sub ranges.
	 * -- use a loop to create a sub range of data set for each thread
	 * -- within the loop, create equal number of threads and pass the sub ranges to the 
	 *    thread entry point
	 */
	// DUMMIED UP -- WRITE YOUR CODE HERE //
	

	/* wait for the child threads to exit, i.e., fork-join strategy */
	// DUMMIED UP -- WRITE YOUR CODE HERE //
	

	/* log the end time of program execution */
	// DUMMIED UP -- WRITE YOUR CODE HERE //
	

	/* print the total elapsed time for the multi-threaded program execution */
	// DUMMIED UP -- WRITE YOUR CODE HRER //
	

	return 0;
} // end of main


/* 
 * Each thread will begin execution from  this function 
 * Consider creating a pointer variable of Range type to
 * keep track of the local range of each thread
 * */
void *findPrimes(void *param)
{
	/* local variable declarations for number of primes, local range, etc.*/
	// DUMMIED UP -- WRITE YOUR CODE HERE //
	
		
	/* output the staring and ending range of number of the thread and total number of primes */
	// DUMMIED UP -- WRITE YOUR CODE HERE //
	
	/* exit thread here */
	// DUMMIED UP -- WRITE YOUR CODE HERE //
	
	 
} // end of findPrimes
