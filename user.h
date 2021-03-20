/*
 * Author: Nick House
 * Project: Process Scheduling
 * File Name: user.h
 */
 
#ifndef USER_H
#define USER_H

#include "library.h"

static void initSysTime();        //Set Shared Mem
static void freeSHM();            //Free Shered Mem

int shmidSysTime;                 //Shm System Time
int shmidMsg; 
struct system_Time *sysTimePtr;   //Pointer to System Time
struct msgBuf buf; 
struct PCB *pcb; 

#endif
