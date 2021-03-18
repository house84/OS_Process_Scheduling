/*
 * Author: Nick House
 * Program: user.c
 * Project: Process Scheduling
 */

#include "library.h"
#include "user.h"
#include "sysTime.h"

int main(int argc, char * argv[]){

	//Set SysTimeID
	shmidSysTime = atoi(argv[2]);

	initSysTime(); 

	printf("Test Program: %s\n", argv[0]); 
	printf("Index: %d\n", atoi(argv[1])); 
	printf("SHMID: %d\n", atoi(argv[2])); 

	sleep(1); 

	fprintf(stderr,"Time: %03d:%09d\n", sysTimePtr->seconds, sysTimePtr->nanoSeconds); 
	
	//Free Memory
	freeSHM(); 
	
	exit(EXIT_SUCCESS); 

}

//Initialize Shared Memory for System Time
static void initSysTime(){

	sysTimePtr = (struct system_Time *) shmat(shmidSysTime, NULL, 0); 

}


//Free Shared Memory PTR
static void freeSHM(){

	if(shmdt(sysTimePtr) == -1){

		perror("user: ERROR: Failed to free ptr shmdt() ");
		exit(EXIT_FAILURE); 
	}
}

