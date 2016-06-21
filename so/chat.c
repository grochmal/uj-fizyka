#include <stdio.h>
#include <unistd.h>
main()
{
        int  pipefd[2];
        int pid;
        char child_buff[100] = "This is a buffer :: I am doing IPC";
        char parent_buff[100];
        if( pipe(pipefd) < 0)
        {
                printf("Error in creating pipe!\n");
                return;
        }
        if( (pid = fork()) < 0)
        {
                printf("Error in fork\n");
                return;
        }
        if(pid == 0)
        {
                if( write(pipefd[1], child_buff, 50) < 0)
                {
                        printf("write error!\n");
                        return;
                }
        }
        else
        {
                read(pipefd[0], parent_buff, 50);
                printf("%s\n", parent_buff);
        }
}
