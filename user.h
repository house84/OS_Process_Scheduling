/*
 * Author: Nick House
 * Project: Process Scheduling
 * File Name: user.h
 */
 
#ifndef USER_H
#define USER_H

#include "headers.h"

bool run;                         //Continue Process
float timeLocal;                  //System Time for Blocked
static void initSysTime();        //Set Shared Mem
static float getTime();           //Get time for blocked
static void freeSHM();            //Free Shered Mem
static void initPCB();            //Set up Initial PCB Values
static void sendMessage();        //Send Message
static void blockedWait();        //Wait while Blocked
static int getRandTime();         //Return Time spent in CPU
static int getMessageType();      //Return if Ready, blocked or Terminate
struct system_Time *sysTimePtr;   //Pointer to System Time
struct PCB pcb; 
struct PCB *pcbPtr; 

#endif
