//fork code that uses multiple loops to creates parents and children
#include <unistd.h>
int main()
{
        int a=0;
        int loops = 2;
        int pid;
        printf("%d\n", a);
        for (a= 1; a <= loops; a++)
        {
                pid=fork();
                if(pid == 0)
                {
                        printf("%d ", a);
                        printf("child \n");
                }
                if(pid != 0)
                {
                        printf("%d ",a);
                        printf("parent\n");
                }
        }
}
