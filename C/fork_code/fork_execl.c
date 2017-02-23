//fork and execl code to overcome problem of getting stuck in child process by using wait()
#include <unistd.h>
int main()
{
        int pid= fork() ;
        if(pid!=0) 
        {
                wait();
                printf ( " I am the parent my PID is %d, myPPID is %d, \n ",getpid(),getppid());
                printf( "Mychild process has finished. \n ");
        }
        else 
        {
                printf ( " I am the child , my PID is %d , my PPID is %d \n",getpid(),getppid());
                sleep(2);
                execl ( "/bin/ls",".",(char*)0);
                printf( "Can you read this ?\n " ) ;
        }
        return 0;
}
