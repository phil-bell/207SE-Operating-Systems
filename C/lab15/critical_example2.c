//critical_example2.c
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>

#include "se207_sems.h"

int main(int argc, char argv[]){
  //Use our source file as the "key"
  int macbethCount = 0;
  int ladyCount = 0;
  int id=se207_semget("critical_example2.c",1);

  int pid=fork();  
  if(pid){
    //P1
    while(1){
      se207_wait(id);
      printf("In critical section P1 ... \n");
      rsleep();
      printf("Ending critical section P1 ... \n");
      
      se207_signal(id);
    }
  }else{
    //P2
    while(1){
      se207_wait(id);
      printf("In critical section P2 ... \n");
      rsleep();
      printf("Ending critical section P2 ... \n");
      se207_signal(id);
    }
    
  }
  
}

