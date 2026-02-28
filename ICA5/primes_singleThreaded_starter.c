/*
 * This is a single-threaded implementation for counting prime numbers
 * between 0 and n, where n > 0
 *
 * This implementation creates a single child thread using fork-join
 * strategy; therefore, the child preforms necessary computation while 
 * the parent process waits for its child's termination. 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <time.h>


/* global variable declaration*/
int count = 0;

/* declaration of thread entry point*/
void *findPrimes(void *param);
int isPrime(int num);


/* 
 * main function
 * 
 * */
int main(int argc, char *argv[])
{
	/* local variable declaration */
	struct timeval stime, etime;
	pthread_t tid1;
	pthread_attr_t attr;
	int val;



	/* process command-line input with sanitation check */
	if (argc != 2) {
		fprintf(stderr, "usage: ./a.out <integer value>\n");
		return -1;
	}

	if (atoi(argv[1]) < 1) {
		fprintf(stderr, "%d must be > 0\n",atoi(argv[1]));
		return -1;
	}

	val = atoi(argv[1]);
	

	/* log the start time of program execution */
	gettimeofday(&stime, NULL);


	/* create a single thread for prime-number detection */
	pthread_attr_init(&attr);
	pthread_create(&tid1, &attr, findPrimes, &val);


	/* wait for the thread to exit */
	pthread_join(tid1, NULL);
	
	/* log the end time for program execution*/	
	gettimeofday(&etime, NULL);


	/* print the total number of primes (i.e., count) and total  execution time from start and end times */
	printf("Total primes: %d\n", count);
	printf("Time: %dms\n", etime.tv_usec - stime.tv_usec);
	
	
	
	return 0;
} // end of main


/* 
 * definition of thread entry point for finding prime number
 * 
 * */
void *findPrimes(void *param)
{
 int num = *(int *)param;
 for (int i = 2; i < num; i++) {
	if (isPrime(i) == 1) {
		count++;
	}
 }
 return NULL;
} // end of isPrime

int isPrime(int num) {
	int prime = 1;
	for (int i = 2; i < num; i++) {
		if (num % i == 0) {
			prime = 0;
		}
	}
	return prime;
}
