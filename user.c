/*
 * Author: Nick House
 * Program: user.c
 * Project: Process Scheduling
 */ 

#include "user.h"

int main(int argc, char * argv[]){

	//Set Shmids
	shmidSysTime = atoi(argv[2]);
	shmidMsg = atoi(argv[3]);

	//Set index
	int idx = atoi(argv[1]); 


	//Initiate SHM
	initSysTime();

	fprintf(stderr,"IN USER\n"); 
	//Initialize PCB Values
	initPCB(idx); 
	
	sysTimePtr->pcbArr[idx].proc_id_Sim = idx; 
	
	fprintf(stderr,"IDX: %d SHMID: %d\n", idx, idx); 

	//Test Setting Values to PCB
	//pcbPtr->cpu_Time = sysTimePtr->nanoSeconds; 
	sysTimePtr->pcbArr[idx].cpu_Time = sysTimePtr->nanoSeconds; 

	fprintf(stderr, "Test Program: %s\n", argv[0]); 
	fprintf(stderr, "Index: %d\n", atoi(argv[1])); 
	fprintf(stderr, "SHMID: %d\n", atoi(argv[2]));
	fprintf(stderr, "SHMID MSG: %d\n", atoi(argv[3]));
	fprintf(stderr, "PCB CPU Time: %d\n", sysTimePtr->pcbArr[idx].cpu_Time); 

//	sleep(idx+1); 

//	fprintf(stderr,"Time: %03d:%09d\n", sysTimePtr->seconds, sysTimePtr->nanoSeconds); 

	//Test Sending Message
	buf.mtype = idx+1;                        //mtype is "address"
	//buf.mtext = "This is Test from User";   //Message
	strcpy(buf.mtext, "This is test from User"); 

	//msgsnd(msgID, message, sizeof(), wait)
	if((msgsnd(shmidMsg, &buf, strlen(buf.mtext)+1, 0)) == -1){

		perror("user: ERROR: failed to msgsnd() "); 
		exit(EXIT_FAILURE); 
	}
	
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


//Initialize PCB Values
static void initPCB(int idx){

	sysTimePtr->pcbArr[idx].proc_id = getpid(); 
	sysTimePtr->pcbArr[idx].proc_id_Sim = idx; 
	sysTimePtr->pcbArr[idx].cpu_Time = 0; 
	sysTimePtr->pcbArr[idx].system_Time = 0; 
	sysTimePtr->pcbArr[idx].wait_Time = 0; 
	sysTimePtr->pcbArr[idx].block_Time = 0; 
	sysTimePtr->pcbArr[idx].unblocked_Time = 0; 
}


