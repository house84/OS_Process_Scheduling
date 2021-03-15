/* 
 * Author: Nick House
 * Project: Process Scheduling
 * File Name: shared.h
 */
 
#ifndef SHARED_H
#define SHARED_H

#define messageSize

//Process Controll Block 
struct pcb{
                             
  //Simulated Time Values
  int cpu_Time;              //Time spent on CPU 
  int system_Time;           //Time spent in System
  int wait_Time;             //Time spent waiting
  int block_Time;            //Time spent Blocked
  int unblocked_Time;        //Time spent UnBlocked
  int proc_id_Sem;           //Simulated PID         
  pid_t proc_id;             //Process Id 

}; 


//Messaging for Sending
struct message_Buffer_1{

  long msg_type; 
  char msg_text[100];

}message1;


//Messaging for Receiving
struct message_Buffer_2{

  long msg_type; 
  char msg_text[100]; 

}message2;


//Shared System Time
struct system_Time{

  int seconds;               //Seconds for System time
  int nanoSeconds;           //NanoSeconds for system time


#endif
