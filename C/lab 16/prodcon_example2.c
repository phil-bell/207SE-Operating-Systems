#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "se207_sems.h"

/* Remember to try reversing the timings...*/


int bufferlength=10; //Limited buffer length 
//what could we do about this?

int main(int argc, char argv[]){

  //Create shared memory segment
  int shm_id=shmget(ftok("prodcon_example2.c",2),bufferlength, 
		    0666|IPC_CREAT);

  //Use our source file as the "key"
  int id=se207_semget("prodcon_example2.c",0);

  char* data; //For our pointer to shared memory...

  int pid=fork();  
  if(pid){
    //P1 - CONSUMER
    shm_id=shmget(ftok("prodcon_example2.c",2),0,006);

    //Attach the shared buffer
    data = shmat(shm_id, (void *)0, 0);
    int consumed=0;
    while(consumed<bufferlength){
      if (consumed>=bufferlength-1){//if the buffer reaches 2 final positions in the buffer (which are reserved for the locations of the consumer and producer) it reset the position to 0 so it goes back to the begining of the buffer
        printf("Reached end buffer Consumer reseting to 0\n");//outputs that it reseting the consumer
        consumed=0;//resets the consumer
      }
      data[bufferlength-1]=consumed;//stores the current location of the consumer in the final position of the buffer
      if (data[bufferlength]-1 != data[bufferlength-2]){// if the consumer is not overruning into the producer
        se207_wait(id);
        printf("Consuming item number %d...\n",consumed);
        sleep(1);
        char item=data[consumed];
      
        printf("Consumed item number %d.  Item value was %d\n",
          consumed,item);
        consumed++;
      }
      else{//if the consumer is going to over run the producer the consumer will do nothing untill the producer has moved
        printf("Stopping Consumer over running Producer\n");//outputs that the Consumer is about to over run the Producer and that it is stopping it 
      }

    }

    //Detatch
    shmdt(data);
    printf("All done consuming.\n");

    wait(); //For child process so that we can

    //Delete the shared memory
    printf("Child ended, removing shm\n");
    shmctl(shm_id, IPC_RMID, NULL);    
  }else{
    //P2
    shm_id=shmget(ftok("prodcon_example2.c",2),0,006);                   
    //Attach the shared buffer
    data = shmat(shm_id, (void *)0, 0);

    int produced=0;
    while(produced<bufferlength){
      if (produced>=bufferlength-1){//if the buffer reaches 2 final positions in the buffer (which are reserved for the locations of the consumer and producer) it reset the position to 0 so it goes back to the begining of the buffer
        printf("Reached end of buffer Producer reseting to 0\n"); //outputs that it reseting the consumer
        produced=0;//resetes the producer
      }
      data[bufferlength-2]=produced;//sets the second from final postition in the buffer to the producer
      if (data[bufferlength]-1 != data[bufferlength-2]){//if the producer is not over runnning the consumer
        printf("Producing item number %d...\n",produced);
        sleep(2);
        data[produced]=produced*2; //Simple data, easy to check.
        printf("Produced item number %d.  Value is %d\n",
  	     produced,data[produced]);
        se207_signal(id);
        produced++;
      }
      else{//if the producer is over running the consumer it will do nothing until the consumer has moved
        printf("Stopping Producer over running Producer\n");
      }
    }
    //Detatch
    shmdt(data);
    printf("Producer finished.");
  }  
}