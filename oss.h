/*
 * Author: Nick House
 * Project: Process Scheduling
 * File Name: oss.h
 */
 
#ifndef SHARED_H
#define SHARED_H

#include <sys/queue.h>
#include <stdbool.h> 

enum state{ready, blocked, running}; 


key_t key;                          //Shm Key
size_t memSize;                     //memSize for getshm()


int shmid;                          //Variable for Shm Id value
pid_t *pidArray;                    //Variable for Process PID's


struct entry{

  int pid;                          //Process PID
  int fakePID;                      //Assigned Fake PID
  int procState;                    //State of process (from enum state) ready, blocked, or running
  CIRCLEQ_ENTRY(entry) entries; 	//Queue

};


CIRCLEQ_HEAD(circlehead, entry); 


struct CPU{

  bool free;                        //Check if CPU is available(free) or not
  pid_t pid;                      	//PID of process in CPU

};

#endif
