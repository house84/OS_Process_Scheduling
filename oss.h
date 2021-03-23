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
static void help();                    //Help Page
static void spawn();                   //Spawn Child Process
static void setTimer();                //Set initial Timer
static void setSysTime();              //Set the System Time
static void showSysTime();             //Display System Time
static void openLogfile();             //Open Logfile
static void closeLogfile();            //Close Logfile
static void displayStats();            //Display Stats
static void signalHandler();           //Handle Signal timer/ctrl+c
static int  getBitVectorPos();         //Search bit vector for open idx
static void freeSharedMemory();        //Release Shared Memory Resources
static void incrementSysTime();        //Increment System time
static void createSharedMemory();      //Allocate Shared Memory

void setBitVectorVal();                //Set BitVector used from idx 
void unsetBitVectorVal();              //Clear Bitvector from idx

key_t keySysTime;                      //Shm Key
size_t memSize;                        //memSize for getshm()

key_t keyMsg;                          //Shm Key for Message Q

struct itimerval timer;                //Set Timer

int shmidMsg;                          //Shared Memory ID for Message
int shmidSysTime;                      //Shared Memory For System Time

struct msgBuf buf;                     //Message Buffer
struct system_Time *sysTimePtr;        //System Time Pointer
//struct PCB pcb;                        //PCB 
struct PCB *pcbArr[100];               //PCB Array for OSS

typedef unsigned int bv_t;             //Bit Vector
bv_t bitVector;                        //BV Variable
pid_t pidArray[100];                   //Variable for Process PID's
bool sigFlag;                          //Variable to pause termination
bool spawnFlag;                        //Varialbe to signal forking process

int myTimer;                           //Timer Value
int totalProc; 					       //Number of total procedures
char logfile[100];                     //Logfile Name
FILE *logfilePtr;                      //Logfile Pointer
int logLines;                          //Holds Number of lines in logfile
time_t t;                              //Hold Time



struct Queue{                          //Queue for Ready 

	struct Node *front; 
	struct Node *Rear; 
	int	currSize;
	int maxSize; 
	int pid; 

};


struct CPU{                            //Struct for CPU item

  int fakePID;                         //Index for next Process
  struct CPU *next; 

}; 



#endif
