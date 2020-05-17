#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include<sys/wait.h>
int main(int argc, char** argv){
    int child;
    int status;
    child=fork();
    if(child>0){
        wait(&status);
        fprintf(stderr,"Child ID: %d\nReturnVal: %d\n",child,WIFEXITED(status));
    }
    if(child==0){
        execve(argv[1],argv+1,NULL);
        perror("execve");
    }
}