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

	//Point pcb 
	pcbPtr = &pcb;

	//Initialize PCB Values
	initPCB(pcbPtr, idx); 

	//Add PCB to shared  pcbArr()
	sysTimePtr->pcbArr[idx] = pcbPtr; 

	fprintf(stderr,"IDX: %d SHMID: %d\n", idx, sysTimePtr->pcbArr[idx]->proc_id_Sim); 

	//Test Setting Values to PCB
	pcbPtr->cpu_Time = sysTimePtr->nanoSeconds; 

	printf("Test Program: %s\n", argv[0]); 
	printf("Index: %d\n", atoi(argv[1])); 
	printf("SHMID: %d\n", atoi(argv[2]));
	printf("SHMID MSG: %d\n", atoi(argv[3]));
	printf("PCB CPU Time: %d\n", pcbPtr->cpu_Time); 

	sleep(idx+1); 

	fprintf(stderr,"Time: %03d:%09d\n", sysTimePtr->seconds, sysTimePtr->nanoSeconds); 

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
static void initPCB(struct PCB *pcb, int idx){

	pcb->proc_id = getpid(); 
	pcb->proc_id_Sim = idx; 
	pcb->cpu_Time = 0; 
	pcb->system_Time = 0; 
	pcb->wait_Time = 0; 
	pcb->block_Time = 0; 
	pcb->unblocked_Time = 0; 
}


