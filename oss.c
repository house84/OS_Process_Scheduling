/*
 * Author: Nick House
 * Project: Process Scheduling
 * Coures: CS-4760 Operating Systems, Spring 2021
 * File Name: oss.c
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


	//===========Begin Project Coding============//
	
	//Initialize Signal Handling
	signal(SIGINT, signalHandler); 


	//Set Initial Parameters
	memset(logfile, '\0', sizeof(logfile)); 
	strcpy(logfile, "logfile"); 
	myTimer = 100; 

	//Parse input Args
	int c = 0; 
	
	while(( c = getopt(argc, argv, "hs:l:")) != -1){

	  switch(c){
				case 'h':	help(argv[0]); 
							exit(EXIT_SUCCESS); 

				case 's': 	//Set Time
							myTimer = atoi(optarg); 
							break; 

				case 'l':	//Set logfile Name
							memset(logfile, '\0', sizeof(logfile));
							strcpy(logfile, optarg); 
							break; 

				case ':':	//Print Missing Arg Message
							fprintf(stderr, "Arguments Required, see usage [-h]\n"); 
							exit(EXIT_FAILURE); 
							break; 

				defalut:	//Defalut Failure Exit
							fprintf(stderr, "Invalid Argument, see usage [-h]\n"); 
							exit(EXIT_FAILURE); 
				}

	}


	//Testing Output
	printf("Test Program: %s Timer: %d FileName: %s\n", argv[0], myTimer, logfile); 
	

	return 0; 

}


//Signal Handler
void signalHandler(int sig){

  	//set sigFlag to block the creation of an further child processes
 	sigFlag == true; 

  	//openLogfile(); 
  
  	//time(&t); 
  
  	//Check for Signal Type
  	if( sig == SIGINT ) {

		fprintf(stderr, "\nProgram Terminated by User\n"); 
		//fprintf(shmptr->logfilePtr, "\nTime: %sProgram Terminated by User\n", ctime(&t)); 
	
  	}else if( sig == 3126 ){

	  	fprintf(stderr, "\nAll Processes have finished\n"); 
	  	//fprintf(shmptr->logfilePtr, "\nTime: %sAll Processes have finished\n", ctime(&t));
	
	}else{

	  	fprintf(stderr, "\nProgram Terminated due to Timer\n"); 
		//fprintf(shmptr->logfilePtr, "\nTime: %sProgram Termintated due to Timer\n", ctime(&t)); 

	}


	//fprintf(shmptr->logfilePtr,"\n//****************** END FILE ENTRY ********************//\n\n"); 
	
	//closeLogfile(); 
	
	//Allow Potential Creating Processes to add PID to Array
	//while(flag == true){}
	
	//Free Memory Resources
	//freeMemory();
	
	if( sig == 3126 ) { exit(EXIT_SUCCESS); }

	//Terminate Child Processes
	//int i; 
	//for( i = 0; i < totalProc; ++i({
	//    
	//    if(kill(pidArray[i], SIGKILL ) == -1 && errno != ERSCH ){
	//    		
	//        perror("oss: ERROR: Failed to Kill Processes "); 
	//        exit(EXIT_FAILURE); 
	//
	//    }
	
	//Destroy Potential Zombies
	//while( wait(NULL) != -1 || errno == EINTR ); 

	exit(EXIT_SUCCESS); 
}

void help(char *program){

  	printf("\n//=== %s Usage Page ===//\n", program);  
	printf("\n%s [-h][-s t][-l f]\n", program); 
	printf("%s -h      This Usage Page\n", program); 
	printf("%s -s t    Time in seconds before program terminates\n", program); 
	printf("%s -l f    Specifies the name for generated logfile\n\n", program); 

}
