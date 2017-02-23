/* Examination of creating two processes using fork: A Child process and a Parent process */
int main()
{
        int pid=fork();
        if(pid==0)
        {
                printf("Child\n");
        }
        else
        {
                printf("Parent\n");
        }
        return 0;
}

