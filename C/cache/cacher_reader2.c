#include "cache_reader.h"


//http://www.phim.unibe.ch/comp_doc/c_manual/C/SYNTAX/struct.html
//http://vergil.chemistry.gatech.edu/resources/programming/c-tutorial/structs.html


int refill(cr_file* buff){
  //Refills a buffer
  //Only works when completely used buffer
  if(buff->usedbuffer!=buff->bufferlength)
    return 0;
  else{
    buff->usedbuffer=0;
    int len=read(buff->buffer, sizeof(char), buff->bufferlength, buff->file);
    //If we didn't fill the buffer, fill up with EOF
    if(len<buff->bufferlength)
      for(int i=len;i<buff->bufferlength;i++)
        buff->buffer[i]=EOF;  //Accessing like an array!
    return len;
  }

}

void cr_close(cr_file* f){
  free(f->buffer);
  close(f->file);
}


cr_file* cr_open(char * filename, int buffersize){

  //Info on malloc
  //http://www.space.unibe.ch/comp_doc/c_manual/C/FUNCTIONS/malloc.html
  FILE* f;
  if ((f = open(filename, "r")) == NULL){
    fprintf(stderr, "Cannot open %s\n", filename);
    return 0;
  }

  cr_file* a=(cr_file*)malloc(sizeof(cr_file));
  a->file=f;
  a->bufferlength=buffersize;
  a->usedbuffer=buffersize; //Start off with no characters, so refill will work as expected
  a->buffer=(char*)malloc(sizeof(char)*buffersize);

  refill(a);
  return a;
}




//------------------------------------------------------------------
char cr_read_byte(cr_file* f){
  f->buffer;
  f->usedbuffer;
  f->bufferlength;
  f->total++;//the total amount of bytes is incremented with every read
  printf("\n new byte \n");// when the bytye is read "new byte" is outputted to the screen
  if (f->usedbuffer == f->bufferlength)//the  buffer is refilled if the amount  of the buffer used is the same $
  {
    refill(f);//refills the buffer
    f->bufffill++;//incrementes each time the buffer is filled
    printf("\n refilling \n");//outputs "refilling" to the screen every time the buffer is reffiled
  }
  return f->buffer[f->usedbuffer++];//returns the buffer contents at the position of the usedbuffer incremented
  // your code goes here
  // remember that this needs to return a char (a byte, put another way..)

