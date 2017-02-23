/* se207_sems.h */
/* Simple functions to ease the use of semaphores */
/* James Shuttleworth, 2012 */
/*--------------------------------------------------------------------------------*/
/* This program is free software: you can redistribute it and/or modify */
/* it under the terms of the GNU General Public License as published by */
/* the Free Software Foundation, either version 3 of the License, or */
/* (at your option) any later version. */

/* This program is distributed in the hope that it will be useful, */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the */
/* GNU General Public License for more details. */

/* You should have received a copy of the GNU General Public License */
/* along with this program.  If not, see <http://www.gnu.org/licenses/>. */

#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>

void rsleep(){
  //Random sleep function.  Comes in handy demoing stuff.
  int stime=2+(rand()/(float)(RAND_MAX))*4;
  printf("Sleeping for %d secs\n",stime);
  sleep(stime);
}


int se207_semget(char* path, int val){
  //Very simple semaphore "getting", 
  //always uses 1 as the project ID
  //takes path to file and initial value of semaphore

  int id; /* Number by which the semaphore 
	     is known within a program */
    

  union semun {
    int val;
    struct semid_ds *buf;
    ushort * array;
  } argument;
  
  argument.val = val;

  /* Create the semaphore with external key from 
     ftok if it doesn't already 
     exist. Give permissions to the world. */

  id = semget(ftok(path,1), 1, 0666 | IPC_CREAT);
  
  /* Always check system returns. */
  
  if(id < 0)
    {
      fprintf(stderr, "Unable to obtain semaphore.\n");
      exit(0);
    }
    
  /* Set the value of the number 0 semaphore in semaphore array # id
     to the value "val". */
  
  if( semctl(id, 0, SETVAL, argument) < 0)
      fprintf( stderr, "Cannot set semaphore value.\n");
  else
    fprintf(stderr, "Semaphore %d initialized with path '%s'.\n", 
	      ftok(path,1),path);
  return id;
}

void se207_semop(int id,int val){
  
  
  struct sembuf operations[1];
  int retval; /* Return value from semop() */
  
  //simple wait on semaphore
  operations[0].sem_num = 0;
  /* Which operation? Subtract 1 from semaphore value to wait, add to
     signal */
  operations[0].sem_op = val;
  operations[0].sem_flg = 0;
  
  retval = semop(id, operations, 1);

}
 

void se207_wait(id){
  se207_semop(id,-1);
}

void se207_signal(id){
  se207_semop(id,1);
}


