/*
 * Author: Nick House
 * Project: Process Scheduling
 * File Name: user.h
 */
 
#ifndef USER_H
#define USER_H

#include "headers.h"

static void initSysTime();        //Set Shared Mem
static void freeSHM();            //Free Shered Mem
static void initPCB();            //Set up Initial PCB Values
static void sendMessage();        //Send Message
static int getRandTime();         //Return Time spent in CPU
static int getMessageType();      //Return if Ready, blocked or Terminate

int shmidSysTime;                 //Shm System Time
int shmidMsg;                     //Message From OSS
int shmidMsgSend;                 //Message TO Oss
int shmidMsg3;                    //User Initialized
bool run;                         //Continue Process

struct system_Time *sysTimePtr;   //Pointer to System Time

//struct msgBuf buf; 

struct PCB pcb; 
struct PCB *pcbPtr; 


#endif
