/* 
 * Author: Nick House
 * Project: Process Scheduling
 * File Name: shared.h
 */
 
#ifndef SHARED_H
#define SHARED_H

#include "headers.h"

//For usability: ready = 0, blocked = 1, running = 2, terminated = 3
enum state{ready, blocked, running, terminated}; 

//Process Control Block 
struct PCB{
                             
  //Simulated Time Values
  int cpu_Time;              //Time spent on CPU 
  int system_Time;           //Time spent in System
  int wait_Time;             //Time spent waiting
  int block_Time;            //Time spent Blocked
  int unblocked_Time;        //Time spent UnBlocked
  int proc_id_Sim;           //Simulated PID         
  pid_t proc_id;             //Process Id
  int msgID;                 //Message Id

}pcb; 

//struct PCB *pcbArr[18];      //Array for Running PCBs

//struct PCB *pcbPTR;          //PCB Ptr

//Messaging for Sending
struct msgBuf{

  long mtype; 
  char mtext[200];

};


//System Time
struct system_Time{

	int seconds;
	int nanoSeconds;
	struct PCB pcbTable[18]; 

};
 
#endif
