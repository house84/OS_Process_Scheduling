/* 
 * Author: Nick House
 * Project: Process Scheduling
 * File Name: shared.h
 */
 
#ifndef SHARED_H
#define SHARED_H

//Process Control Block 
struct PCB{
                             
  //Simulated Time Values
  int cpu_Time;              //Time spent on CPU 
  int system_Time;           //Time spent in System
  int wait_Time;             //Time spent waiting
  int block_Time;            //Time spent Blocked
  int unblocked_Time;        //Time spent UnBlocked
  int proc_id_Sem;           //Simulated PID         
 // pid_t proc_id;             //Process Id 

}; 

//Messaging for Sending
struct message_Buffer{

  long msg_type; 
  char msg_text[100];

};
 

#endif
