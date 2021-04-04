/*
 * Author: Nick House
 * Project: Process Scheduling
 * Coures: CS-4760 Operating Systems, Spring 2021
 * File Name: oss.c
 */

#include "oss.h"

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
	totalProc = 0;  
	srand(time(NULL)); 
//	bv_t bitVector; 
	
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

	//Set 3 Second Timer
	stopProdTimer = false; 
	//setTimer2(3); 
	setTimer2(100); 

	//Create Shared Memory
	createSharedMemory(); 
	
	//Set System Time
	setSysTime(); 

	//Open logfile
	openLogfile(); 

	//Initialize Queue
	GQue = initQueue(); 

	//Initialize CPU Node
	//struct p_Node *CPU_Node = (struct p_Node*)malloc(sizeof(struct p_Node)); 
	CPU_Node = (struct p_Node*)malloc(sizeof(struct p_Node)); 

	//=========== Add Program Logic =============
	

	int i; 
	int index; 
	concProc = 0; 
	
	//For Real 
	//whlie(totalProc < 100 && stopProdTimer == false){ 
	
	//Testing While
//	while( totalProc < 10 && stopProdTimer == false ){ 
	while(true){

		//Increment System Time by NanoSeconds
		incrementSysTime(100000000); 
		
		//Spawn Child Process //Set to 20 for testing
		if( concProc < 12 && totalProc < 100 && stopProdTimer == false){

			index = getBitVectorPos(); 
			if(index != -1) { 
				
				spawn(index); 
				++totalProc; 
				++concProc;
			
				fprintf(stderr, "::::::::::::::::::: Spawned index: %d, Total Proc: %d, ConcProc: %d\n", index, totalProc, concProc); 
				
				//Allow User to initialize
				if(msgrcv(shmidMsg3, &buf3, sizeof(buf3.mtext), index+1, 0) == -1){

					perror("OSS: ERROR: Failed to RCV Message from user msgrcv() ");
					exit(EXIT_FAILURE); 
				}

				//Add to RunQ
				enqueue(index);
			}
		}
		
		
		//Check for freed Proc From Blocked Que
		//checkBlockedQue(); 
		//
		//
		//Try Running Process in CPU
		
		//Check runQueue
		allocateCPU();
			
		
	//	sysTimePtr->pcbTable[index] = pcb;  

		//check for Finished Processes
		int status; 
	//	pid_t user_id = 0; 
		
		pid_t user_id = waitpid(-1, &status, WNOHANG); 

		if(user_id > 0 ){
 			
			//fprintf(stderr,"waitPid user_id: %d\n", user_id); 
			--concProc;
		}

	//	if(concProc > 1){
	//		wait(NULL);
	//		--concProc;
	//	}

		//Break Loop clean up memory
		if((totalProc == 100 || stopProdTimer == true) && concProc == 0){
		
			break; 
		}

		if( totalProc %18  == 0 ){

		//Slowdown for testing
			//sleep(rand()%3);
			sleep(1); 
		}
	}


	//==========================================
	

	//Allow Processes to finish
	while(wait(NULL) > 0){} 
	
	//Testing Output
	printf("Test Program: %s Timer: %d FileName: %s\n", argv[0], myTimer, logfile); 
	
	//Clean up Resources
	signalHandler(3126);

	return 0; 

}


//Signal Handler
void signalHandler(int sig){

  	//set sigFlag to block the creation of an further child processes
 	sigFlag == true; 

  	//openLogfile(); 
  
  	time(&t); 
  
  	//Check for Signal Type
  	if( sig == SIGINT ) {

		fprintf(stderr, "\nProgram Terminated by User\n"); 
		fprintf(logfilePtr, "\nTime: %sProgram Terminated by User\n", ctime(&t)); 
	
  	}else if( sig == 3126 ){

	  	fprintf(stderr, "\nAll Processes have finished\n"); 
	  	fprintf(logfilePtr, "\nTime: %sAll Processes have finished\n", ctime(&t));
	
	}else{

	  	fprintf(stderr, "\nProgram Terminated due to Timer\n"); 
		//fprintf(logfilePtr, "\nTime: %sProgram Termintated due to Timer\n", ctime(&t)); 

	}


	//fprintf(shmptr->logfilePtr,"\n//****************** END FILE ENTRY ********************//\n\n"); 
	
	//Display Stats
	displayStats(); 
	
	//Close Logfile Ptr
	closeLogfile(); 
	
	//Allow Potential Creating Processes to add PID to Array
	while(spawnFlag == true){}
	
	//Free Memory Resources
	freeSharedMemory();
	
	//Exit Normally
	if( sig == 3126 ) { exit(EXIT_SUCCESS); }


	//Terminate Child Processes
	int i; 
	for( i = 0; i < totalProc; ++i){
	    
	    if(kill(pidArray[i], SIGKILL ) == -1 && errno != ESRCH ){
	    		
	        perror("oss: ERROR: Failed to Kill Processes "); 
	        exit(EXIT_FAILURE); 
	
	    }
	}
	
	//Destroy Potential Zombies
	while( wait(NULL) != -1 || errno == EINTR ); 

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


//Start Stop Produce Timer
static void setTimer2(int t){

	signal(SIGALRM, stopTimeHandler); 

	timer.it_value.tv_sec = t; 
	timer.it_value.tv_usec = 0; 
	timer.it_interval.tv_sec = 0; 
	timer.it_interval.tv_usec = 0; 

	if(setitimer(ITIMER_REAL, &timer, NULL) == -1){

		perror("oss: ERROR: Failed to set timer setitimer() ");
		exit(EXIT_FAILURE);
	}
}


//Handler for Stopping Process Creation
static void stopTimeHandler(){

	fprintf(stderr, "3 Second Timer \n"); 
	stopProdTimer = true;
}


//Create Shared Memory
static void createSharedMemory(){  

	//=== System Time Shared Memory
	if((keySysTime = ftok("Makefile", 'a')) == -1){
		
		perror("oss: ERROR: Failed to generate keySysTime ftok() ");
		exit(EXIT_FAILURE); 
	}
	
	if((shmidSysTime = shmget(keySysTime, sizeof(struct system_Time), IPC_CREAT|S_IRUSR|S_IWUSR)) == -1){
		
		perror("oss: ERROR: Failed to get shmidSysTime, shmget() ");
		exit(EXIT_FAILURE); 
	}
	

	sysTimePtr = (struct system_Time *) shmat(shmidSysTime, NULL, 0); 


	//=== Messaging to Send to User
	if((keyMsg = ftok("oss.c", 'a')) == -1){
		
		perror("oss: ERROR: Failed to generate keyMsg, ftok() ");
		exit(EXIT_FAILURE);
	}
	
	if((shmidMsg = msgget(keyMsg, IPC_CREAT|S_IRUSR|S_IWUSR)) == -1){

		perror("oss: ERROR: Failed to generate shmidMsg, msgget() "); 
		exit(EXIT_FAILURE); 
	}
	
	//=== Message to Receive From User
	if((keyMsg2 = ftok("user.c", 'a')) == -1){

		perror("oss: ERROR: Failed to generate keyMsg2, ftok() ");
		exit(EXIT_FAILURE); 
	}

	if((shmidMsgRcv = msgget(keyMsg2, IPC_CREAT|S_IRUSR|S_IWUSR)) == -1){

		perror("oss: ERROR: Failed to generate shmidMsgRcv, msgget() ");
		exit(EXIT_FAILURE); 
	}

	//=== Message to Receive Initialized from User
	if((keyMsg3 = ftok("user.h", 'a')) == -1){

		perror("oss: ERROR: Failed to generate keyMsg3, ftok() "); 
		exit(EXIT_FAILURE); 
	}

	if((shmidMsg3 = msgget(keyMsg3, IPC_CREAT|S_IRUSR|S_IWUSR)) == -1){

		perror("oss: ERROR: Failed to generate shmidMsg3, msgget() ");
		exit(EXIT_FAILURE); 
	}

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

	
	//Destroy Message Q
	if(msgctl(shmidMsg, IPC_RMID, NULL) == -1){

		perror("oss: ERROR: Failed to Destroy shmidMsg, msgctl() "); 
		exit(EXIT_FAILURE); 
	}

	if(msgctl(shmidMsgRcv, IPC_RMID, NULL) == -1){

		perror("oss: ERROR: Failed to Destroy shmidMsgRcv, msgctl() ");
		exit(EXIT_FAILURE); 
	}

	if(msgctl(shmidMsg3, IPC_RMID, NULL) == -1){

		perror("oss: ERROR: Failed to Destroy shmidMsg3, msgctl() "); 
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

	if(sysTimePtr->nanoSeconds >= 1000000000 ){

	//	sysTimePtr->nanoSeconds = sysTimePtr->nanoSeconds - 100000000;  
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

		//shmidMsg arg
		char buffer_msgId[50];
		sprintf(buffer_msgId, "%d", shmidMsg);


	//	bool run = true; 
		//shmidMsgRcv arg
		char buffer_msgId2[50];
		sprintf(buffer_msgId2, "%d", shmidMsgRcv); 
		
		//shmidMsg3 arg
		char buffer_msgId3[50];
		sprintf(buffer_msgId3, "%d", shmidMsg3); 

		//Call user file with child process
		if(execl("./user", "user", buffer_idx, buffer_sysTime, buffer_msgId,buffer_msgId2, buffer_msgId3, (char*) NULL)){

			perror("oss: ERROR: Failed to execl() child process "); 
			exit(EXIT_FAILURE); 
		}

	exit(EXIT_SUCCESS); 

	}
}


//Find Index of empty Bit Arr
static int getBitVectorPos(){

	unsigned int i = 1; 
	int idx = 0; 

	//Search bitVector R->L until 0 is found
	while(( i & bitVector) && (idx < procMax)){

		i <<= 1; 
		++idx; 
	}

	if( idx < procMax ){

		//Set Bit Func
		setBitVectorVal(idx); 

		return idx; 
	}

	else{

		return -1; 
	}

}


//Set Bit Vector From Index 
void setBitVectorVal(int idx){
	
	bitVector |= ( 1 << idx ); 
}


//Unset Bit Vector from index
void unsetBitVectorVal(int idx){ 

	bitVector &= ~( 1 << idx ); 
}


//Open New Logfile
static void openLogfile(){
	
	logfilePtr = fopen(logfile, "w"); 

	if( logfilePtr == NULL ){

		perror("oss: ERROR: Failed to Open logfile "); 
		exit(EXIT_FAILURE); 
	}

	time(&t); 

	fprintf(logfilePtr, "\n//========================= Log Opened ========================//\n"); 
	fprintf(logfilePtr, "Time: %s", ctime(&t));
	fprintf(logfilePtr, "//=============================================================//\n"); 

}


//Close Logfile
static void closeLogfile(){

	
	fprintf(logfilePtr, "\n//========================= Log Closed ========================//\n"); 
	fprintf(logfilePtr, "Time: %s", ctime(&t)); 
	fprintf(logfilePtr, "//=============================================================//\n\n"); 
	fclose(logfilePtr); 


}


//Display Stats/Print Stats
static void displayStats(){

	//Print to logs and Display
	fprintf(stderr, "displayStats()\n"); 

}


//Initialize Queue
//struct Queue * initQueue(int pid){
struct Queue * initQueue(){

	struct Queue *que = (struct Queue*)malloc(sizeof(struct Queue));

	//fprintf(stderr, "IN INITQUEUE\n"); 


	//Initialize Null Front and Rear Nodes
	que->head = NULL; 
	que->tail = NULL; 

	que->maxSize = procMax; 
	que->currSize = 0;  

	return que; 

}


//Enqueue Process to Queue
static void enqueue(int idx){

	//Testing
	fprintf(stderr, "ENQUEU index: %d\n", idx); 

	struct p_Node *newNode = (struct p_Node*)malloc(sizeof(struct p_Node));  
	

	newNode->fakePID = idx; 
	newNode->next = NULL; 

	//Test Print
	fprintf(stderr, "OSS: Time: %s PID: %d |||| Added to Queue[%d]\n", getSysTime(), newNode->fakePID, GQue->currSize); 

	++GQue->currSize; 

	//Check if Empty
	if( GQue->head == NULL && GQue->tail == NULL ){

		GQue->head = newNode; 
		GQue->tail = newNode; 

		return; 
	}

	//Else add Node to End of Que
	GQue->tail->next = newNode; 
	GQue->tail = newNode; 
  
}


//Dequeue Process from Queue
struct p_Node * dequeue(){

	//Testing
	//fprintf(stderr, "Dequeue\n"); 	

	//Check if Que is empty
	if( GQue->head == NULL ){ return NULL; }

	struct p_Node *newNode = GQue->head; 

	--GQue->currSize; 

	//Make next node the head
	GQue->head = GQue->head->next; 

	//Check if Que is Now Empty
	if( GQue->head == NULL ){ GQue->tail = NULL; }

	//Test Print
	fprintf(stderr, "OSS: Time: %s PID: %d |||| Removed from Queue\n", getSysTime(), newNode->fakePID); 

	return newNode; 

}


//Print The Queue for Testing
static void printQ(){

	//Test
	fprintf(stderr, "Print Q\n"); 
	
	struct p_Node *newNode = GQue->head; 

	fprintf(stderr, "QUEUE Sizez: %d -> ", GQue->currSize);

	while(newNode != NULL){

		fprintf(stderr, "%d ", newNode->fakePID); 
		newNode = newNode->next; 
	}

	fprintf(stderr,"\n"); 

}


//Check Blocked Que for Ready Proc
static void checkBlockedQue(){


}


//Display Stytem Time
const char * getSysTime(){
	
	
	char *sTime; 
	asprintf(&sTime, "%04d:%09d", sysTimePtr->seconds, sysTimePtr->nanoSeconds); 
	
	return sTime; 
}


//Put Ready Process into CPU
static void allocateCPU(){
	
	//Check for runnable Processes
	if(GQue->currSize == 0){ return; }
	
	//Dequeue Process
	CPU_Node = dequeue(); 
	
	//Check Node
	if(CPU_Node == NULL){

		fprintf(stderr,"Que Head Empty\n"); 
		return; 
	}

	//Testing
	fprintf(stderr, "In Allocate CPU, mID: %d\n", CPU_Node->fakePID+1); 

	int mID = CPU_Node->fakePID+1; 

//	bufS.mtype = msgID; //CPU_Node->fakePID+1;
	bufS.mtype = mID; 
	strcpy(bufS.mtext, "Run"); 

//	if((msgsnd(shmidMsg, &bufS, sizeof(bufS.mtext)+1, IPC_NOWAIT)) == -1){
//	if((msgsnd(shmidMsg, &bufS, sizeof(bufS.mtext)+1, 0)) == -1){
	if((msgsnd(shmidMsg, &bufS, sizeof(bufS.mtext), 0)) == -1 ){
		
	//	bool err = true; 

	//	if( errno != EINTR){

	//		if(	msgsnd(shmidMsg, &bufS, sizeof(bufS.mtext)+1, 0) > -1){
				
	//			err = false; 
	//		}	
	//	}
		
//		if(err == true){

			fprintf(stderr, "OSS: FAILED::: mID: %d\n", mID);  
			perror("oss: ERROR: Failed to Send Msg to User msgsnd() "); 
			exit(EXIT_FAILURE); 
//		}
	}

	//Print Update from CPU 
	fprintf(stderr, "OSS: Time: %s PID: %d |||| Sent to CPU\n", getSysTime(), CPU_Node->fakePID); 


	//Need to wait for message back that 
	msgrcv(shmidMsgRcv, &bufR, sizeof(bufR.mtext), mID, 0);

	
	//Display Message
	fprintf(stderr,"mID: %d => Message: %s\n", mID, bufR.mtext); 

	if( strcmp(bufR.mtext, "terminated") == 0){

		fprintf(stderr," TERMINATED\n");
		unsetBitVectorVal(CPU_Node->fakePID); 
		return; 
	}
	
	//Add Process Back to Queue
	enqueue(CPU_Node->fakePID); 
}

//struct p_Node *CPU_Node = (struct p_Node*)malloc(sizeof(struct p_Node)); 
