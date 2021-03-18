/*
 * Author: Nick House
 * Project: Process Scheduling
 * Coures: CS-4760 Operating Systems, Spring 2021
 * File Name: oss.c
 */

#include "library.h"
#include "oss.h"
#include "shared.h"
#include "sysTime.h"

int main(int argc, char * argv[]){
	
	//Set Bool
	sigFlag = false; 
	spawnFlag = false; 
	
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

				default:	//Defalut Failure Exit
							fprintf(stderr, "Invalid Argument, see usage [-h]\n"); 
							exit(EXIT_FAILURE); 
				}

	}


	//Check Timer > 0
	if(myTimer < 1){

	  	fprintf(stderr, "Time -s must be greater than zero\n"); 
	 	exit(EXIT_FAILURE); 
	}
	
	//Set timer
	setTimer(myTimer); 

	//Create Shared Memory
	createSharedMemory(); 
	
	//Set System Time
	setSysTime(); 
	
	//=========== Add Program Logic =============
	
	int i; 
	for(i = 0; i < 2; ++i){

		//Increment System Time by NanoSeconds
		incrementSysTime(100000000); 

		//Show Timer
		//showSysTime();
		
		//Spawn Child Process
		spawn(i); 

		//Test Slowdown
		sleep(1);

	}

	//Testing Timer
	for(i = 0; i < 5; ++i){

		incrementSysTime(100000000); 
	//	sleep(1);
	}

	//Allow Processes to finish
	while(wait(NULL) > 0){}

	//Free Shared Memory
	freeSharedMemory(); 

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
	while(spawnFlag == true){}
	
	//Free Memory Resources
	//freeSharedMemory();
	
	//Free Message Memory
	//freeSharedMessage(); 
	
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


//Display Usage
static void help(char *program){

  	printf("\n//=== %s Usage Page ===//\n", program);  
	printf("\n%s [-h][-s t][-l f]\n", program); 
	printf("%s -h      This Usage Page\n", program); 
	printf("%s -s t    Time in seconds before program terminates\n", program); 
	printf("%s -l f    Specifies the name for generated logfile\n\n", program); 

}


//Set Timer
static void setTimer(int t){

  	signal(SIGALRM, signalHandler); 
	
	timer.it_value.tv_sec = t; 
	timer.it_value.tv_usec = 0; 
	timer.it_interval.tv_sec = 0; 
	timer.it_interval.tv_usec = 0; 

	if(setitimer(ITIMER_REAL, &timer, NULL) == -1){

		perror("oss: ERROR: Failed to set timer setitimer() ");
		exit(EXIT_FAILURE);
	}
}


//Create System Time Shared Memory
static void createSharedMemory(){  

	keySysTime = ftok("Makefile", 'a'); 
	
	shmidSysTime = shmget(keySysTime, sizeof(struct system_Time), IPC_CREAT|S_IRUSR|S_IWUSR); 
	
	if(shmidSysTime == -1){

	  perror("oss: ERROR: Failed to Generate sys_Time id shmget() "); 
	  exit(EXIT_FAILURE); 
	
	}

	sysTimePtr = (struct system_Time *) shmat(shmidSysTime, NULL, 0); 

}


//Free Shared Memory
static void freeSharedMemory(){

	//Detach System Pointer
	if(shmdt(sysTimePtr) == -1){
		
		perror("oss: ERROR: Failed to detach shmidSysTime, shmdt() "); 
		exit(EXIT_FAILURE); 
	}

	//Destroy System Time Memory
	if(shmctl(shmidSysTime, IPC_RMID, NULL) == -1){
		
		perror("oss: ERROR: Failed to Desttory sysTimePtr, shmctl() "); 
		exit(EXIT_FAILURE); 
	}
}


//Set System Time
static void setSysTime(){

	sysTimePtr->seconds = 0; 
	sysTimePtr->nanoSeconds = 0;
}

//Increment System Time
static void incrementSysTime(int x){

	sysTimePtr->nanoSeconds = sysTimePtr->nanoSeconds + x; 

	if(sysTimePtr->nanoSeconds == 1000000000 ){

		sysTimePtr->nanoSeconds = 0;  
		
		sysTimePtr->seconds += 1; 
	}	
}

//Show System Time
static void showSysTime(){
	
	float nano = sysTimePtr->nanoSeconds;

	printf("System Time (seconds)-> %03d:%09d\n",sysTimePtr->seconds, sysTimePtr->nanoSeconds); 

}


//Spawn Child Process
static void spawn(int idx){

	//Check if prograom is terminating
	if(sigFlag == true) { return; }

	pid_t process_id; 

	if((process_id = fork()) < 0){

		perror("oss: ERROR: Failed to fork process fork() ");
		exit(EXIT_FAILURE); 
	}

	if(process_id == 0){

		//Temp Block Handler from Terminating
		spawnFlag = true; 
		
		//Add Process to Process Array
		pidArray[idx]  = process_id; 
	
		//Release Block 
		spawnFlag = false; 

		//Index arg
		char buffer_idx[10];
		sprintf(buffer_idx, "%d", idx); 

		//shmidSysTime arg
		char buffer_sysTime[50]; 
		sprintf(buffer_sysTime, "%d", shmidSysTime); 

		//Call user file with child process
		if(execl("./user", "user", buffer_idx, buffer_sysTime, (char*) NULL)){

			perror("oss: ERROR: Failed to execl() child process "); 
			exit(EXIT_FAILURE); 
		}

	exit(EXIT_SUCCESS); 

	}
}



