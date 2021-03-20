/*
 * Author: Nick House
 * Project: Process Scheduling
 * File Name: oss.h
 */
 
#ifndef OSS_H
#define OSS_H

#include "library.h"

//For usability: ready = 0, blocked = 1, running = 2
enum state{ready, blocked, running}; 


//Function Prototypes
static void help(); 
static void spawn();
static void setTimer();  
static void setSysTime();
static void showSysTime(); 
static void signalHandler(); 
static void freeSharedMemory(); 
static void incrementSysTime(); 
static void createSharedMemory();

key_t keySysTime;                       //Shm Key
size_t memSize;                         //memSize for getshm()

key_t keyMsg;                           //Shm Key for Message Q

struct itimerval timer;                 //Set Timer

int shmidMsg; 
int shmidSysTime; 

struct msgBuf buf; 
struct system_Time *sysTimePtr; 
struct PCB *pcb; 

pid_t pidArray[100];                    //Variable for Process PID's
bool sigFlag;                           //Variable to pause termination
bool spawnFlag;                         //Varialbe to signal forking process

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
