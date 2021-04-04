/*
 * Author: Nick House
 * Program: user.c
 * Project: Process Scheduling
 */ 

#include "user.h"

int main(int argc, char * argv[]){

//	srand(time(NULL)); 
	srand(time(NULL) ^ (getpid()<<16)); 

	//Set Shmids
	shmidSysTime = atoi(argv[2]);
	shmidMsg = atoi(argv[3]);
	shmidMsg2 = atoi(argv[4]); 
	shmidMsg3 = atoi(argv[5]); 

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
	
	buf3.mtype = mID;
	strcpy(buf3.mtext, ""); 

	msgsnd(shmidMsg3, &buf3, sizeof(buf3.mtext), 0); 

	while(run == true){

		fprintf(stderr, "user: mID: %d Wating for OSS\n", mID); 
		//Recienve Message to Run from CPU
		msgrcv(shmidMsg, &bufS, sizeof(bufS.mtext), mID, 0); 
	
		
		//Send Message Back to OSS
		sendMessage(shmidMsg2, mID); 
	}

	//Free Memory
	freeSHM(); 
	
	exit(EXIT_SUCCESS); 

}


//Decide to block run or Terminate
static int getMessageType(int idx){

	return ((rand()+idx) % 3) ; 

}

//Decide how long to spend in quantum 10ms
static int getRandTime(){

	return (rand()% 8800001) + 200000; 

}

//Message_t ready = 0 , blocked = 1, terminated = 3
static void sendMessage(int msgid, int idx){

	bufS.mtype = idx; 

	//Get Type of message
	int messageT = getMessageType(idx); 

	if(messageT != ready){
		
		int rand = getRandTime(); 
		sysTimePtr->pcbTable[idx].sprint_Time = rand; 
		sysTimePtr->pcbTable[idx].cpu_Time += rand/1000000000; 
	}
	else{

		sysTimePtr->pcbTable[idx].sprint_Time = 10000000; 

		sysTimePtr->pcbTable[idx].cpu_Time += .01; 
	}
	
	if(messageT == ready){

		strcpy(bufS.mtext, "ready");
	}
	else if( messageT == blocked ){

		strcpy(bufS.mtext, "blocked"); 
		blockedWait(idx); 
	}
	else {

		strcpy(bufS.mtext, "terminated");
		run = false; 
	}

	//Message Sent 
	fprintf(stderr, "user: Sending msg to OSS mID: %d\n", idx); 

	if((msgsnd(msgid, &bufS, sizeof(bufS.mtext), 0)) == -1){

		perror("user: ERROR: Failed to msgsnd() ");
		exit(EXIT_FAILURE); 
	}
}


//Wait while user blocked while User Blocked
static void blockedWait(int idx){

	float nanoWait = rand()%100000001; 
	float secWait = rand()%6; 
	float bWait = secWait + nanoWait/1000000000;
	timeLocal = getTime(); 
	
	float unblocked = timeLocal + bWait; 
	sysTimePtr->pcbTable[idx].wake_Up = unblocked; 

	fprintf(stderr, "user: Time: %f  Unblocked: %f\n", timeLocal, unblocked);  

}


//Get time 
static float getTime(){
	
	float decimal = sysTimePtr->nanoSeconds;
	decimal = decimal/1000000000;
	float second = sysTimePtr->seconds; 
	
	float localT = second+decimal; 

//	fprintf(stderr, "++++++ User: Seconds = %f  Decimal = %f  LocalT: %f\n", second, decimal, localT); 
	
	return localT; 


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

	sysTimePtr->pcbTable[idx].time_Started = getTime();
	sysTimePtr->pcbTable[idx].proc_id = getpid(); 
	sysTimePtr->pcbTable[idx].proc_id_Sim = idx; 
	sysTimePtr->pcbTable[idx].cpu_Time = 0; 
	sysTimePtr->pcbTable[idx].system_Time = 0; 
	sysTimePtr->pcbTable[idx].waited_Time = 0; 
	sysTimePtr->pcbTable[idx].blocked_Time = 0; 
	sysTimePtr->pcbTable[idx].sprint_Time = 0; 
	sysTimePtr->pcbTable[idx].msgID = idx+1;

}


