//fork and execl code to overcome problem of getting stuck in child process by using wait()
#include <unistd.h>
#include <stdio.h>
int main()
{
        char answer[1];//defines the variable fo the users answer
        printf("Please select one of the following values:\n");//this line and the three below ask the user what they want to do. This is the menu
        printf("a: ls\n");
        printf("b: who\n");
        printf("c: ping\n");
        scanf("%s",answer);
        if (strcmp(answer,"a") == 0)//if the users answer is "a" then it does teh following
        {
                int pid = fork();//forks the processes
                if(pid!=0) //if it is tbe parent process
                {
                        wait();//waits 
                        printf ( "I am the parent my PID is %d, myPPID is %d, \n ",getpid(),getppid());//prints out the parent PID
                        printf( "Mychild process has finished. \n ");//prints that the child process has finished
                }
                else //if it is the child process
                {
                        printf ( "I am the child , my PID is %d , my PPID is %d \n",getpid(),getppid());//prints the child proicess PID
                        sleep(2);//sleeps for 2 seconds
                        execl ( "/bin/ls",".",(char*)0);//runs the ls in the current directory using execl
                }
        }
        else if(strcmp(answer,"b") == 0)//if the the users answer is "b" it does the following 
        {
                int pid = fork();//forks the porcesses 
                if(pid!=0) //if it is the parent process
                {
                        wait();//waits 
                        printf ( "I am the parent my PID is %d, myPPID is %d, \n ",getpid(),getppid());//outputs the PID and PPID of the parent process
                        printf( "Mychild process has finished. \n ");//outputs that the child process has finished
                }
                else /if it is the child process
                {
                        printf ( "I am the child , my PID is %d , my PPID is %d \n",getpid(),getppid());//outputs the PID and PPID of the child process
                        sleep(2);//sleeps for 2 seconds 
                        execl ( "/bin/who","who","-u",(char*)0);//uses execl to run the who command to show who is currently logged in
                }
        }
        else if (strcmp(answer,"c") == 0)//if the user input is "c"
        {
                int pid = fork();//forks the process
                if(pid!=0) //if it is the parent process
                {
                        wait();
                        printf ( "I am the parent my PID is %d, myPPID is %d, \n ",getpid(),getppid());//outputs the PID and PPID of the parent process
                        execl ("/bin/ping","ping","www.google.com","-c 1",(char*)0);//uses the execl to run a ping to google as the parent process. Only pings once.
                        printf( "Mychild process has finished. \n ");//outputs that the child process has finished
                }
                else //if it is the child process
                {
                        printf ( "I am the child , my PID is %d , my PPID is %d \n",getpid(),getppid());//outputs the PID and PPID of the child process
                        sleep(2);//sleeps for 2 seconds
                        execl ( "/bin/ping","ping","www.yahoo.com", "-c 1",(char*)0);//uses the execl process to run a ping yahoo as a child process. Only pings once.
                }          
        }
        else// if the user enters an invalid command it does the following
        {
                printf("Not a valid command\n");//outs that the user has entered an invalid command
        }                
        return 0;
}