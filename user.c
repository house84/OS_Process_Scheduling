/*
 * Author: Nick House
 * Program: user.c
 * Project: Process Scheduling
 */ 

#include "user.h"

int main(int argc, char * argv[]){

	srand(time(NULL)); 

	//Set Shmids
	shmidSysTime = atoi(argv[2]);
	shmidMsg = atoi(argv[3]);
	shmidMsgSend = atoi(argv[4]); 

	//Set index
	int idx = atoi(argv[1]); 
	int mID = idx+1;
	run = true; 

	fprintf(stderr,"IN USER IDX: %d mID: %d\n", idx, mID); 

	//Initiate SHM
	initSysTime();

	//Initialize PCB Values
	initPCB(idx); 
	
	sysTimePtr->pcbTable[idx].proc_id_Sim = idx; 
	
	sysTimePtr->pcbTable[idx].cpu_Time = sysTimePtr->nanoSeconds; 

	fprintf(stderr, "Test Program: %s\n", argv[0]); 
	fprintf(stderr, "Index: %d\n", atoi(argv[1])); 
	fprintf(stderr, "SHMID: %d\n", atoi(argv[2]));
	fprintf(stderr, "SHMID MSG: %d\n", atoi(argv[3]));
	fprintf(stderr, "PCB CPU Time: %d\n", sysTimePtr->pcbTable[idx].cpu_Time); 

	int i; 
	while(run == true){

		//Recienve Message to Run from CPU
		msgrcv(shmidMsg, &bufS, sizeof(bufS.mtext), mID, 0); 
	
		//Send Message Back to OSS
		sendMessage(shmidMsgSend, mID); 
	}

	//Free Memory
	freeSHM(); 
	
	exit(EXIT_SUCCESS); 

}


//Decide to block run or Terminate
static int getMessageType(){

	return (rand() % 3) ; 

}

//Decide how long to spend in quantum 10ms
static int getRandTime(){

	return (rand()%10) + 1; 

}

//Message_t ready = 0 , blocked = 1, terminated = 3
static void sendMessage(int msgid, int idx){

	bufS.mtype = idx; 

	//Get Type of message
	int messageT = getMessageType(); 
	 
	if(messageT != ready){
		
		int rand = getRandTime(); 
		sysTimePtr->pcbTable[idx].sprint_Time = rand; 

		sysTimePtr->pcbTable[idx].cpu_Time += rand; 
	}
	else{

		sysTimePtr->pcbTable[idx].sprint_Time = 10; 

		sysTimePtr->pcbTable[idx].proc_id += 10; 
	}
	
	if(messageT == ready){

		strcpy(bufS.mtext, "ready");
	}
	else if( messageT == blocked ){

		strcpy(bufS.mtext, "blocked"); 
	}
	else {

		strcpy(bufS.mtext, "terminated");
		run = false; 
	}


	if((msgsnd(msgid, &bufS, strlen(bufS.mtext)+1, IPC_NOWAIT)) == -1){

		perror("user: ERROR: Failed to msgsnd() ");
		exit(EXIT_FAILURE); 
	}
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

	sysTimePtr->pcbTable[idx].proc_id = getpid(); 
	sysTimePtr->pcbTable[idx].proc_id_Sim = idx; 
	sysTimePtr->pcbTable[idx].cpu_Time = 0; 
	sysTimePtr->pcbTable[idx].system_Time = 0; 
	sysTimePtr->pcbTable[idx].wait_Time = 0; 
	sysTimePtr->pcbTable[idx].block_Time = 0; 
	sysTimePtr->pcbTable[idx].sprint_Time = 0; 
	sysTimePtr->pcbTable[idx].msgID = idx+1;

}


