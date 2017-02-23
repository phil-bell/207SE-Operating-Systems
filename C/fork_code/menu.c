#include <unistd.h>
#include <stdio.h>
#include <sys/tpye/h>
#include <stdlib.h>

int main()
{
    int a;
    int pid = fork()
    printf("Please select one of the option below:\n");
    printf("1: ls the current directory\n");
    printf("2: who you currently logged in as\n");
    printf("3: ping Google\n");
    scanf("%d",&a);
    printf("You have selected: %d \n",a);
    if (a == 1)
    {
        if (pid != 0)
        {
            wait();
            printf("Parant PID: %d \n",getpid());
        }
        else
        {
            printf("Child PID: %d \n",getpid());
            execl("/bin/ls",".",(char*)0);
        }
    }
    else if (a == 2)
    {
        if (pid != 0)
        {
            wait();
            printf("Parant PID: %d \n",getpid());
        }
        else
        {
            printf("Child PID: %d \n",getpid());
            execl("/bin/who",".",(char*)0);
        }
    }
    else if (a == 3)
    {
        if (pid != 0)
        {
            wait();
            printf("Parant PID: %d \n",getpid());
        }
        else
        {
            printf("Child PID: %d \n",getpid());
            execl("/bin/ping","www.google.com",(char*)0);
        }
    }
}
