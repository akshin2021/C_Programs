#include <stdio.h>
#include <unistd.h>
void main()
{
    int fd[2],fd2[2],otp,u_otp;
    pipe(fd);
    pipe(fd2);
    
    int pid=fork();
    
    if (pid<0){
        printf("Error");
        
    }
    else if (pid==0){
        close(fd[1]);
        read(fd[0],&otp,sizeof(otp));
        printf("The otp is %d \n",otp);
        
        printf("Enter the otp");
        scanf("%d",&u_otp);
        close(fd[0]);
        
        close(fd2[0]);
        write(fd2[1],&u_otp,sizeof(u_otp));
        
    }
    else{
        close(fd[0]);
        //otp=673016;
        printf("Bank Generated OTP - ");
        scanf("%d",&otp);
        write(fd[1],&otp,sizeof(otp));
        
        close(fd[1]);
        
        close(fd2[1]);
        read(fd2[0],&u_otp,sizeof(u_otp));
        if (otp==u_otp){
            printf("Transaction Approved");
        }
        else{
            printf("Transaction failed");
        }
        
    }
}

