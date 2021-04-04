/* 
 * Author: Nick House
 * Project: Process Scheduling
 * File Name: shared.h
 */
 
#ifndef SHARED_H
#define SHARED_H

#include "headers.h"

//For usability: ready = 0, blocked = 1, running = 2, terminated = 3
enum state{ready, blocked, terminated}; 

//Process Control Block 
struct PCB{
                             
  //Simulated Time Values
  int cpu_Time;              //Time spent on CPU 
  int system_Time;           //Time spent in System
  int wait_Time;             //Time spent waiting
  int block_Time;            //Time spent Blocked
  int sprint_Time;           //Recent Run time in CPU
  int proc_id_Sim;           //Simulated PID         
  pid_t proc_id;             //Process Id
  int msgID;                 //Message Id

}pcb; 


struct msgBuf{

  long mtype; 
  char mtext[200];

};

struct msgBuf bufS;         //Send Msg from OSS -> User
struct msgBuf bufR;         //Send Msg from User -> OSS
struct msgBuf buf3;         //Message signal User initialized

int shmidMsg;               //Msg id for OSS->User
int shmidMsg2;            //Msg id for User->OSS
int shmidMsg3;              //Msg id for User initialize
int shmidSysTime;           //Shared Memory Id

//System Time
struct system_Time{

	int seconds;
	int nanoSeconds;
	struct PCB pcbTable[18]; 

};
 
#endif
