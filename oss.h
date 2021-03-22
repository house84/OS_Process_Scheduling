/*
 * Author: Nick House
 * Project: Process Scheduling
 * File Name: oss.h
 */
 
#ifndef OSS_H
#define OSS_H

#include "headers.h"

//For usability: ready = 0, blocked = 1, running = 2
//enum state{ready, blocked, running};

#define procMax 18

//Function Prototypes
static void help(); 
static void spawn();
void setBitVectorVal(); 
static void setTimer();  
void unsetBitVectorVal(); 
static void setSysTime();
static void showSysTime(); 
static void signalHandler();
static int  getBitVectorPos();
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
struct PCB pcb; 

typedef unsigned int bv_t;              //Bit Vector
bv_t bitVector;                         //BV Variable
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
