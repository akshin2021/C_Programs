#include <stdio.h>

void main()
{
    int fd[2],fd2[2];
    struct dob{
        int dd;
        int mm;
        int yyyy;
        
    };
    struct dob now;
    now.dd=11;
    now.mm=9;
    now.yyyy=2023;
    
    pipe(fd);
    pipe(fd2);
    struct dob dobs;
    int pid;
    pid=fork();
    
    if(pid<0){
        printf("Error ");
    }
    else if (pid==0){
        close(fd[1]);
        read(fd[0],&dobs,sizeof(dobs));
        close(fd[0]);
        
        int age=now.yyyy-dobs.yyyy;
        close(fd2[0]);
        write(fd2[1],&age,sizeof(age));
        close(fd2[1]);
        
    }
    else {
        close(fd[0]);
        printf("Enter the dob in dd mm yyyy format -");
        scanf("%d%d%d",&dobs.dd,&dobs.mm,&dobs.yyyy);
        write(fd[1],&dobs,sizeof(dobs));
        close(fd[1]);
        int age;
        close(fd2[1]);
        read(fd2[0],&age,sizeof(age));
        printf("The age of person is %d",age);
    }
    
}
