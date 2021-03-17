/*
 * Author: Nick House
 * Program: oss.c
 * Project: Process Scheduling
 */

#include <semaphore.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <limits.h>
#include <errno.h>
#include <math.h>
#include <stdbool.h>
#include <signal.h>
#include <time.h>
#include <sys/queue.h>
#include "oss.h"
#include "shared.h"


int main(int argc, char * argv[]){

	printf("Test Program: %s\n", argv[0]); 

	

	//Create Buffer of Ready Processes
	


	/*	How to use Circular Queues
	 *
	 * 	//HEADNAME = Struct to be defined
	 *  //TYPE = Type of the elements to be linked 
	 *	CIRCLE_HEAD(HEADNAME, TYPE) head; 	//Declare Circle Head
	 *
	 *	struct HEADNAM *headp; 			//Pointer to the Head of circular queue
	 *
	 *	CIRCLEQ_EMPTY(); 				//Checks if circle queue is empty
	 *	CIRCLEQ_FOREACH(); 				//Traverses forward and assigns var
	 *	CIRCLEQ_FOREACH_REVERSE(); 		//Traverses Backward and assigns var
	 *	CIRCLEQ_INIT();					//Initializes circular Queue by head
	 *	CIRCLEQ_INSERT_HEAD(); 			//Inserts new element at head
	 *	CIRLCEQ_INSERT_TAIL(); 			//Inserts new element at end
	 *	CIRCELQ_INSERT_AFTER(); 		//Inserts new element before list elm
	 *	CIRCLEQ_INSERT_BEFORE(); 		//Inserts new element after list elm
	 *	CIRLCEQ_LAST();					//Returns Last item on queue
	 *	CIRCLEQ_NEXT(); 				//Returns next item on list
	 *	CIRCLEQ_PREV(); 				//Returns previous item on list
	 *	CIRLCEQ_LOOP_NEXT(); 			//Returns next item, elm
	 *	CIRLCEQ_LOOP_PREV(); 			//Returns previous item, elm
	 *	CIRCLEQ__REMOVE(); 				//Removes the element elm queue
	 */
	
	//Initialize Items for CircleQ
	struct entry *readyQueue;                        //Ready Processes Queue
	struct entry *blockedQueue;                      //Blocked Processes Queue
	struct circlehead head;                         //Queue Head
	CIRCLEQ_INIT(&head);                            //Initialize the queue

	//Initialize Simulated CPU Resource
	struct CPU cpu;                                 //CPU Resource 
	
	readyQueue = malloc(sizeof(struct entry));      //Insert at head
	CIRCLEQ_INSERT_HEAD(&head, readyQueue, entries); 

	readyQueue = malloc(sizeof(struct entry));      //Insert at tail
	CIRLCEQ_INSERT_TAIL(&head, readyQueue, entries); 

	



	
		

	return 0; 

}
