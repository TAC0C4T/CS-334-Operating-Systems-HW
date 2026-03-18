#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define NUM_THREADS 3

int points;
int in = 0;


struct timeval stime, etime;

void *finder_ihardlyknower(void *param);	/* thread for calculating average value */
// void *minValue(void *numList); 	/* thread for calculating minimum value */
// void *maxValue(void *numList);	/* thread for calculating maximum value */

/* initial (parent) process/thread */
int main(int argc, char *argv[])
{
	gettimeofday(&stime, NULL);

	pthread_t tid1, tid2, tid3;		// the thread identifier 
	pthread_t tid[NUM_THREADS];
	pthread_attr_t attr;	// set of thread attribute

    points = atoi(argv[1]);


	pthread_attr_init(&attr);

	pthread_create(&tid1, &attr, finder_ihardlyknower, &points);
	//pthread_create(&tid2, &attr, maxValue, arr);
	//pthread_create(&tid3, &attr, minValue, arr);
	

	
	/* wait for the threads to join with the parent thread */

	pthread_join(tid1, NULL);
	//pthread_join(tid2, NULL);
	//pthread_join(tid3, NULL);



	/* print the final output */
	printf("\nThe value is %f\n", 4 * (double)in / points);
	gettimeofday(&etime, NULL);

	//printf("Time: %dms\n", etime.tv_usec - stime.tv_usec);

	return 0;
} // end of main 


/* AVG_THREAD will begin control in this function */
void *finder_ihardlyknower(void *param)
{
    int dec = *(int*)param;

    for (int i = 0; i < dec; i++) {
        double x = (double)rand() / RAND_MAX * 2.0 - 1.0;
        double y = (double)rand() / RAND_MAX * 2.0 - 1.0;
        if (x*x + y*y <= 1.0) {
            in++;
        }

    }


	
	pthread_exit(0);
} // end of avgValue


                                                                                      
