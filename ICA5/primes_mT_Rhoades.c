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

int localCounts[NUM_THREADS];

/* structure declaration */
struct range {
	int start;	// first value in the range
	int end;	// last value in the range
	int id;
};
typedef struct range Range;
struct timeval stime, etime;

/* function declaration for thread entry point */
void *findPrimes(void *param);
int isPrime(int num);


/*
 * main function -- entry point for the parent process
 *
 */
int main(int argc, char *argv[])
{
	/* declare and initialize necessary variables */
	int n = 0;
	Range ranges[NUM_THREADS];
	pthread_t tid1, tid2, tid3, tid4;		// the thread identifier 
	pthread_t tid[NUM_THREADS];
	pthread_attr_t attr;	// set of thread attribute
	struct timeval startTime, endTime;
	

	/* process command-line input with sanitation checks */
	if (argc != 2) {
		fprintf(stderr, "usage: ./a.out <integer value>\n");
		return -1;
	}

	if (atoi(argv[1]) < 1000) {
		fprintf(stderr, "%d must be > 999\n",atoi(argv[1]));
		return -1;
	}

	n = atoi(argv[1]);

	/* log the start time of program execution */
	gettimeofday(&startTime, NULL);
	
	
	/* calculate the range for each subset of the initial data set of size n */
	int totalNums = n - 1;
	int range = totalNums / NUM_THREADS;
	int remainder = totalNums % NUM_THREADS;
	int current = 0;

	for (int i = 0; i < NUM_THREADS; i++) {
		int size = range + (i < remainder?1:0);
		ranges[i].start = current;
		ranges[i].end = current + size - 1;
		ranges[i].id = i;
		current = ranges[i].end + 1;
	}
	

	/* get ready for the final output */
	
	for (int i = 0; i < NUM_THREADS; i++) {
		localCounts[i] = 0;
	}
	



	/* create a thread for calculating prime numbers with in four different sub ranges.
	 * -- use a loop to create a sub range of data set for each thread
	 * -- within the loop, create equal number of threads and pass the sub ranges to the 
	 *    thread entry point
	 */
	// DUMMIED UP -- WRITE YOUR CODE HERE //
	for (int i = 0; i < NUM_THREADS; i++) {
		if (pthread_create(&tid[i], NULL, findPrimes, &ranges[i]) != 0) {
			perror("pthread_create");
			return 0;
		}
	}
	

	/* wait for the child threads to exit, i.e., fork-join strategy */
	// DUMMIED UP -- WRITE YOUR CODE HERE //

	for (int i = 0; i < NUM_THREADS; i++) {
		if(pthread_join(tid[i], NULL) != 0) {
			perror("pthread_join");
			return 0;
		}
	}
	

	/* log the end time of program execution */
	// DUMMIED UP -- WRITE YOUR CODE HERE //
	gettimeofday(&endTime, NULL);
	

	/* print the total elapsed time for the multi-threaded program execution */
	// DUMMIED UP -- WRITE YOUR CODE HRER //
	double total = (endTime.tv_sec - startTime.tv_sec) + (endTime.tv_usec - startTime.tv_usec) / 1000000.0;

	printf("Execution time for multi-threaded program: %f seconds\n", total);

	int totalCount = 0;
	for (int i = 0; i < NUM_THREADS; i++) {
		totalCount += localCounts[i];
	}

	printf("Total primes between 0 and %d: %d\n", n, totalCount);

	return 0;
} // end of main


/* 
 * Each thread will begin execution from  this function 
 * Consider creating a pointer variable of Range type to
 * keep track of the local range of each thread
 * */
void *findPrimes(void *param)
{
    Range *r = (Range *)param;

    for (int i = r->start; i <= r->end; i++) {
        if (isPrime(i)) {
            localCounts[r->id]++; 
        }
    }
    return NULL;
}


int isPrime(int num) {
    if (num < 2) return 0;
    for (int i = 2; i * i <= num; i++) {  
        if (num % i == 0) return 0;
    }
    return 1;
}