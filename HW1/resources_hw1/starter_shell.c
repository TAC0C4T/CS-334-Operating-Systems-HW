/*
 * This is a sample structure for writing HW1. This starter file contains 
 * coding holes to be filled by students and grading rubric as comments.
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <wait.h>
#include <stdlib.h>	/* for exit() system call */

#define MAX_LINE 81	/* The maximum length command */

int readStringInput(char str[], int n);	/* read a line of string */

int main(void)
{
	/* Declare necessary variables below if any more required
	 *
	 * ------------------------ 5 point ------------------------------------------
	 * */
	char userCommand[MAX_LINE];	/* user input string */
	char *args[MAX_LINE/2 + 1];	/* command-line arguments */
	int running = 1;		/* flag to determine when to exit program */
	int concurrent = 0;		/* flag for concurrent run */
	pid_t pid;

	int numArgs = 0;


	while(running) {
		/* print the command prompt */
		if (concurrent == 0) {		// only if the parent is not running concurrently	
			printf("cs334B> ");
			fflush(stdout);
		}
		concurrent = 0;

		/* Your code for safely reading user input through readStringInput() function
		 * call comes below
		 *
		 * ------------------------------ 5 points ---------------------------------
		 *  */



		if (strcmp(userCommand, "exit") == 0) { // terminate shell if command 'exit'
			running = 0;
		}
		else {	// execute user command

			/* Your code comes below to parse the user command and also ignore if the
			 * user command is invalid i.e., a null string  or just "&" has been typed 
			 * as Linux command.
			 *
			 * ------------------------------ 15 points ------------------------------ 
			 */
			
		         	


			/**
		 	* After reading user command, the steps are:
		 	* (1) fork a child process using fork()
		 	* (2) the child process will invoke execvp()
		 	* (3) if command included &, parent will not invoke wait()
		 	*/

			/*
			 * Your code for Step (1) comes below
			 * -------------------------------- 5 points ------------------------------
			 */
			pid = fork();
			if (userCommand[numArgs-1] == "&") {
				concurrent = 1;
			} 
	


			if (pid < 0) {	/* error occured */
				printf("Fork failed!\n");
				return 1;
			}	
			else if (pid == 0) {	/* child process */
			       /* Your code for Step (2) comes below. Also, include a necessary check if 
				* the child process would run in the background or not.
				*
				* ------------------------- 15 points -----------------------------
				*/	
				execvp(userCommand[0], args);
				exit


			}
			else { /* parent process */
				/* Your code for Step (3) comes below. Include necessary checks to
				 * so that the parent process run properly with or without the
				 * wait() system call concerning concurrent or simultaneous 
				 * execution.
				 *
				 * ------------------------- 25 points -----------------------------
				 *
				 */



			}	

		}

		/* if you don't disable the following statement, the starter_code will run in an
		 * infinite loop. Disable it as you start building the code.
		 */
		running = 0;
	} // end of while

	return 0;
} // end of main


/* safely reads user-defined command (i.e., string value) from the keyboard one 
 * character at at time and then stores it into str[] of size n. The final content
 * in str[] is also null terminated.
 *
 * this is alternative to using scanf(), gets(), or fgets() function. 
 * 
 * -------------------------- Score: 15 points--------------------------------
 * */
int readStringInput(char str[], int n)
{
	// Your code comes here 


	return 0;	// number of characters stored
} // end of read_line
