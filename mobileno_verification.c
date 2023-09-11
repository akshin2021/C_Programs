#include <stdio.h>
#include <unistd.h>
#include <string.h>

void main()
{
    int fd[2],fd2[2],valid;
    char mob[13];
    pipe(fd);
    pipe(fd2);
    
    int pid=fork();
    
    if (pid<0)
    {
        printf("Error");
    }
    else if (pid==0)
    {
        //child
        close(fd[1]);
        read(fd[0],&mob,sizeof(mob));
        int valid=1;
        if(strlen(mob)==13)
        {
            if (mob[0]=='+' && mob[1]=='9' && mob[2]=='1')
            {
                for (int i=3;i<strlen(mob);i++)
                {
                    if(mob[i]>='0' && mob[i]<='9')
                    {
                        valid=1;
                    }
                    else
                    {
                        valid=0;
                        break;
                    }  
                }
                
            }
            else{
                    valid=0; 
                    }  
        }
        else
        {
            valid=0;
        }
    
    close(fd[0]);
    close(fd2[0]);
    write(fd2[1],&valid,sizeof(valid));
    close(fd2[1]);
    }
    else
    {
        close(fd[0]);
        printf("Enter the mobile number -");
        scanf("%s",mob);
        write(fd[1],&mob,sizeof(mob));
        close(fd[1]);
        close(fd2[1]);
        read(fd2[0],&valid,sizeof(valid));
        if (valid==1)
        {
        printf("Mobile number is valid ");
        }
        else
        {
            printf("Mobile number is not valid");
        }
    }
}
