//Modified from 
//http://docs.linux.cz/programming/c/unix_examples/semab.html

#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>

#define KEY 87654 //Unique semaphore key




int main(){

  int id; /* Number by which the semaphore is known within a program */
  
  /* The next thing is an argument to the semctl() function. Semctl() 
     does various things to the semaphore depending on which arguments
     are passed. We will use it to make sure that the value of the 
     semaphore is initially 0. */
  
  union semun {
    int val;
    struct semid_ds *buf;
    ushort * array;
  } argument;
  
  argument.val = 1;
  
  /* Create the semaphore with external key KEY if it doesn't already 
     exists. Give permissions to the world. */
  
  id = semget(KEY, 1, 0666 | IPC_CREAT);
  
  /* Always check system returns. */
  
  if(id < 0)
    {
      fprintf(stderr, "Unable to obtain semaphore.\n");
      exit(0);
    }
  
  /* What we actually get is an array of semaphores. The second 
     argument to semget() was the array dimension - in our case
     1. */
  
  /* Set the value of the number 0 semaphore in semaphore array
     # id to the value 0. */
  
  if( semctl(id, 0, SETVAL, argument) < 0)
    {
      fprintf( stderr, "Cannot set semaphore value.\n");
    }
  else
    {
      fprintf(stderr, "Semaphore %d initialized.\n", KEY);
    }
  
  int pid=fork();
  
  if(pid){
    struct sembuf operations[1];
    int retval; /* Return value from semop() */

    /* Get the index for the semaphore with external name KEY. */
    id = semget(KEY, 1, 0666);

    if(id < 0){
      /* Semaphore does not exist. */
      
      fprintf(stderr, "Program sema cannot find semaphore, exiting.\n");
      exit(0);
    }
    operations[0].sem_num = 0;
    /* Which operation? Subtract 1 from semaphore value : */
    operations[0].sem_op = -1;
    /* Set the flag so we will wait : */   
    operations[0].sem_flg = 0;
    

    
    while(1){
      //Process 1

      //wait
      operations[0].sem_op = -1;
      retval = semop(id, operations, 1);


      //critical section
      printf("In critical section P1 ... \n");
      fflush(stdout);
      int stime=2+(rand()/(float)(RAND_MAX))*4;
      printf("Sleeping for %d secs\n",stime);
      sleep(stime);


      printf("Ending critical section P1 ... \n");
      fflush(stdout);

      operations[0].sem_op = 1;
      //signal
      retval = semop(id, operations, 1);

    }
  }else{
    //Process 2
    struct sembuf operations[1];
    int retval; /* Return value from semop() */
    /* Get the index for the semaphore with external name KEY. */
    id = semget(KEY, 1, 0666);
    if(id < 0){
      /* Semaphore does not exist. */
      
      fprintf(stderr, "Program sema cannot find semaphore, exiting.\n");
      exit(0);
    }
    operations[0].sem_num = 0;
    /* Which operation? Subtract 1 from semaphore value : */
    operations[0].sem_op = -1;
    /* Set the flag so we will wait : */   
    operations[0].sem_flg = 0;
    
    while(1){

      
      
      //wait
      operations[0].sem_op = -1;
      retval = semop(id, operations, 1);
      
      //critical section
      printf("In critical section P2 ... \n");
      fflush(stdout);
      int stime=2+(rand()/(float)(RAND_MAX))*4;
      printf("Sleeping for %d secs\n",stime);
      sleep(stime);

      printf("Ending critical section P2 ... \n");
      fflush(stdout);

      //signal
      operations[0].sem_op = 1;
      retval = semop(id, operations, 1);

    }
    
  }
  
}

