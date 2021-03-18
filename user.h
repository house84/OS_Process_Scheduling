/*
 * Author: Nick House
 * Project: Process Scheduling
 * File Name: user.h
 */
 
#ifndef SHARED_H
#define SHARED_H

static void initSysTime();        //Set Shared Mem
static void freeSHM();            //Free Shered Mem

int shmidSysTime;                 //Shm System Time
struct system_Time *sysTimePtr;   //Pointer to System Time


#endif
