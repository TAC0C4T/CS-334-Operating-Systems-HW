/*
 * A multithreaded sorting application
 *
 * Concepts: implicit threading, global variables,
 * 	     structure, parallel tasks, fork-join 
 * 	     strategy, sorting algorithms, etc.
 *
 * CS334: Operating Systems homework assignment 3
 * TOTAL POINTS: 100
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* preprocessor constants */
#define SIZE 10
#define NUM_THREADS 3

/* declaration of thread entry points */
void *sorter(void *param);	// thread for basic sorting algorithm
void *merger(void *param);	// thread for merging sorted data subsets

/* global variables for sorting data */
int dataSet[SIZE] = {7,12,19,3,18,4,2,6,15,8};
int result[SIZE];

/**
 * This structure will be used to pass parameters to both sorter and merger threads.
 * In case of sorter thread, startIndex and endIndex represent the subrange of dataset.
 * In case of merger thread, the startIndex and endIndex represent the staring indexes of the 
 * first and the second subranges of the entire dataset
 */
struct subRange{ 	// a structure for passing the subrange of the dataset
	int startIndex;	
	int endIndex;
};
typedef struct subRange SubRange;


/**
 * main method 
 *
 * Note: entry point of the parent thread
 */
int main(int argc, char *argv[])
{
  /* local variable declarations */
  pthread_t tid[NUM_THREADS];
  pthread_attr_t attr;


 
  //======================>> 15 POINTS <<=====================
  /* create the first sorter thread (thread_0) with appropriate subrange */
  SubRange *sRange = (SubRange *)malloc(sizeof(SubRange));	// create a SubRange pointer variable to set the 
  								// subrange of dataset before passing to the thread
  // -----DUMMIED UP -- WRITE YOUR CODE HERE------ //
  pthread_create(&tid[0], &attr, sorter, sRange);
  


  
  //======================>> 15 POINTS <<=====================
  /* create the second sorter thread (thread_1) with appropriate subrange -- as above */
  // -----DUMMIED UP -- WRITE YOUR CODE HERE------ //



  //======================>> 10 POINTS <<=====================
  /* wait for the sorter threads to return to the parent thread -- fork-join strategy */
  for(int i = 0; i < NUM_THREADS-1; i++) {
  	// -----DUMMIED UP -- WRITE YOUR CODE HERE------- //
	

  } // end of for


  //======================>> 15 POINTS <<=====================
  /* Now created the merger thread with appropriate subrange 
   *
   * Note: Here, the 'SubRange' struct will contain the startIndex values of
   * thread_0 and thread_1 in the startIndex and endIndex, respectively.
   * */



  //======================>> 5 POINTS <<=====================
  /* wait for the merger thread to finish */
  // -----DUMMIED UP -- WRITE YOUR CODE HERE------ //



  /* output the sorted array */
  printf("\nSorted data set: ");
  for(int i = 0; i < SIZE; i++) {
  	printf("%d ", dataSet[i]);	// currently prints unsorted data set
  }
  printf("\n");

  return 0;
} // end of main


/*
 * definition of the entry point for sorter thread
 *
 * Note: implement any sorting algorithm of your choice
 */
void *sorter(void *param)
{
    SubRange *range = (SubRange *)param;

    //======================>> 20 POINTS <<=====================
    // -----DUMMIED UP -- WRITE YOUR CODE HERE------ //
    int n = range->endIndex - range->startIndex + 1;
    int *arr = (int *)malloc(n * sizeof(int));
    arr = &dataSet[range->startIndex];
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
    
    for (int i = 0; i < n; i++) {
        dataSet[range->startIndex + i] = arr[i];
    }
    free(arr);

    
    /* exit sorter thread */
    // -----DUMMIED UP -- WRITE YOUR CODE HERE------ //



} // end of sorter


/**
 * definition of the entry point for the  merger thread
 *
 * Note: Use merge sort for merging two lists (subranges)
 *       passed to 'thread_0' and 'thread_1'
 */
void *merger(void *param) 
{
    //======================>> 20 POINTS <<=====================
    /* Implement merge sort for merging the two sublist of the dataset */
    // -----DUMMIED UP -- WRITE YOUR CODE HERE------ //
    int *arrayFirst[SIZE/2];
    int *arraySecond[SIZE/2];

    for (int i = 0; i < SIZE/2; i++) {
        if (i < SIZE/2) {
            arrayFirst[i] = result[i];
        } else {
            arraySecond[i - SIZE/2] = result[i];
        }
    }

    int arrOne = 0;
    int arrTwo = 0;

    for (int i = 0; i < SIZE; i++) {
        if (arrayFirst[arrOne] < arraySecond[arrTwo]) {
            dataSet[i] = arrayFirst[arrOne];
            arrOne++;
        } else {
            dataSet[i] = arraySecond[arrTwo];
            arrTwo++;
        }
    }



    /* exit merger thread */
    // -----DUMMIED UP -- WRITE YOUR CODE HERE------ //


} // end of merger
