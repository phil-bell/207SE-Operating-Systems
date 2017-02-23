//Simple fork with execl.  Problem that get stuck as execl writes over process that calls it
#include<unistd.h>
int main( ) 
{
        int pid=fork();
        if ( pid!=0) 
        {
                printf ("Hello \n") ;
        }
        else
        {
                sleep(2);
                execl("/bin/ls",".",( char*)0);
                printf("Can you read this ? \n" );
        }
        return 0;
}

