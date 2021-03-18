/*
 * Author: Nick House
 * Project: Process Scheduling
 * File Name: oss.h
 */
 
#ifndef SHARED_H
#define SHARED_H

//For usability: ready = 0, blocked = 1, running = 2
enum state{ready, blocked, running}; 


//Function Prototypes
static void help(); 
static void spawn();
static void setTimer(); 
static void signalHandler(); 
static void freeSharedMemory(); 
static void createSharedMemory();
static void setTimer(); 

key_t keySysTime;                       //Shm Key
size_t memSize;                         //memSize for getshm()
int shmidSysTime;                       //Variable for Shm Id value
struct system_Time *sysTimePtr;         //Pointer for System Time
struct itimerval timer;                 //Set Timer

pid_t *pidArray;                        //Variable for Process PID's
bool sigFlag;                           //Variable to pause termination

int logLines;                           //Holds Number of lines in logfile
int myTimer;                            //Timer Value
int totalProc; 					        //Number of total procedures
char logfile[100];                      //Logfile Name
FILE *logfilePtr;                       //Logfile Pointer
time_t t;                               //Hold Time



struct Queue{

	struct Node *front; 
	struct Node *Rear; 
	int	currSize;
	int maxSize; 
	int pid; 

};


struct Node{

  int fakePID;                      //Index for PCB
  struct Node *next; 

}; 



#endif
