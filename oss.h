/*
 * Author: Nick House
 * Project: Process Scheduling
 * File Name: oss.h
 */
 
#ifndef SHARED_H
#define SHARED_H

key_t key;                          //Shm Key
size_t memSize;                      //memSize for getshm()
int shmid;                          //Variable for Shm Id value
pid_t *pidArray;                    //Variable for Process PID's


#endif
