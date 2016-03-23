//critical_example2.c
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>

#include "se207_sems.h"

int main(int argc, char argv[]){
  //Use our source file as the "key"
  int count = 0;
  //the line below is the array that stores the convertation between Mavbeth and Lady Macbeth
  const char *lines[] = {"LADY MACBETH Donalbain.","MACBETH This is a sorry sight.","LADY MACBETH A foolish thought, to say a sorry sight.","MACBETH There's one did laugh in's sleep, and one cried 'Murder!' That they did wake each other: I stood and heard them: But they did say their prayers, and address'd them Again to sleep.","LADY MACBETH There are two lodged together.","MACBETH One cried 'God bless us!' and 'Amen' the other; As they had seen me with these hangman's hands. Listening their fear, I could not say 'Amen,' When they did say 'God bless us!'","LADY MACBETH Consider it not so deeply.","MACBETH But wherefore could not I pronounce 'Amen'? I had most need of blessing, and 'Amen' Stuck in my throat.","LADY MACBETH These deeds must not be thought After these ways; so, it will ake us mad.","MACBETH Methought I heard a voice cry 'Sleep no more! Macbeth does murder sleep', the innocent sleep, Sleep that knits up the ravell'd sleeve of care, The death of each day's life, sore labour's bath, Balm of hurt minds, great nature's second course, Chief nourisher in life's feast,--", "LADY MACBETH What do you mean?"};
    
  int id=se207_semget("critical_example2.c",1);

  FILE * ladyFile; //makes a file pointer for the ladyFile
  FILE * macFile; //makes a file pointer for the macFile

  ladyFile = fopen ("ladyFile.txt","w"); //opens the ladyFile.txt file
  macFile = fopen ("macFile.txt","w"); //opens the macFile.txt file

  int pid=fork();  //forks the process
  if(pid){//if it is process 1 do this 
    //P1
    while(1){//loops
      se207_wait(id);
      printf("%s",lines[count]);//prints the current item in the array
      fprintf(ladyFile, "%s\n",lines[count]);//prints to the lady macbeth file
      count++;//icnrements the array count
      rsleep();//sleeps
      se207_signal(id);
    }
  }else{//if it is process 2 do this
    //P2
    while(1){//loops
      se207_wait(id);
      printf("%s",lines[count]);//prints the current item in the array
      fprintf(macFile, "%s\n",lines[count]); //prints to the macbeth file
      count++;//increments the array count
      rsleep();//sleeps
      se207_signal(id);
    }
    
  }
  fclose(ladyFile); //closes the lady macbeth file
  fclose(macFile); //closes the macbeth file
}

