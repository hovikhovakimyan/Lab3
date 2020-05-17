#include<stdio.h>
#include<time.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include <sys/times.h>

int main(){
    int status;
    struct tms *tms;
    printf("START: %ld\n", time(NULL));
    int p;
    p=fork();
    if(p>0){
        for(int i=0;i<250000000;i++){
        
        }
        wait(&status);
        times(tms);
        printf("PPID: %d, PID: %d, CPID: %d, RETVAL: %d\n", getppid(), getpid(), p, WIFEXITED(status));
        printf("USER: %ld, SYS: %ld\n",tms->tms_utime, tms->tms_stime);
        printf("CUSER: %ld, CSYS: %ld\n",tms->tms_cutime, tms->tms_cstime);
        printf("Exit: %ld",time(NULL));
    }
    if(p==0){
    for(int i=0;i<250000000;i++){

    }
    printf("PPID: %d, PID: %d\n", getppid(), getpid());
    }
    return 1;
}
