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

int shmidSysTime;                 //Shm System Time
int shmidMsg; 

struct system_Time *sysTimePtr;   //Pointer to System Time

struct msgBuf buf; 

struct PCB pcb; 
struct PCB *pcbPtr; 


#endif
