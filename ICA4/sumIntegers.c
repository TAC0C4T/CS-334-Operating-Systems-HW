#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int sum;	// global variable will be shared by threads
void *sumIntegers(void *param);	// threads starts from this function

int main(int agrc, char* argv[]) {
	/* beginning of the main method */
	pthread_t tid;		// the thread identifier	
	pthread_attr_t attr;	// set the thread attributes

	/* sanity checks for the command line input */
	if(agrc != 2) {
		fprintf(stderr, "Usage: ./a.out <integer value>\n");
		return -1;
	}

	if(atoi(argv[1]) < 0) {
		fprintf(stderr, "%d must be >0\n", atoi(argv[1]));
		return -1;
	}

	printf("Creating thread ....\n");

	/* creates a thread */

	// get the default thread attributes
	pthread_attr_init(&attr);

	// create the thread
	pthread_create(&tid, &attr, sumIntegers, argv[1]);

	// wait for the thread to exit -- Fork-and-Join strategy
	pthread_join(tid, NULL);


	/* print the final value using the parent thread */
	printf("Returned thread id: %08X\t\n", (unsigned int)tid);
	printf("The final sum is : %d\n", sum);

	/* end of program */
	return 0;
} // end of main


/* Thread entry point defition */
void *sumIntegers(void* param)
{
	int input = atoi(param); // not atoi(*param) -- derefencing is not needed since
				 // atio() expects "const char *", not a char
	sum = 0;
	for(int i = 0; i <= input; i++) {
		sum += i;
		printf("Running sum: %d\n", sum);
	} // end of for

	/* exit thread */
	pthread_exit(0);
} // end of sumIntegers


