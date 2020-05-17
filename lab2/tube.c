#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
int main(int argc, char **argv)
{
    int commaindex;
    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], ",") == 0)
        {
            commaindex = i;
            break;
        }
    }
    pid_t child1;
    pid_t child2;
    int state1;
    int state2;
    int pipefd[2];
    char *instruct1[commaindex];
    char *instruct2[argc - commaindex];
    int i = 1;
    int j = 0;
    while (i < commaindex)
    {
        instruct1[i - 1] = argv[i];
        i++;
    }
    i++;
    while (i < argc)
    {
        instruct2[j] = argv[i];
        i++;
        j++;
    }
    pipe(pipefd);
    child1 = fork();
    waitpid(child1, &state1, WUNTRACED);
    if (child1 > 0)
    {
        child2 = fork();
        if (child2 == 0)
        {
            close(pipefd[1]);
            dup2(pipefd[0], 0);
            execve(instruct2[0], instruct2, NULL);
            perror("execve");
        }
        else if (child2 > 0)
        {
            fprintf(stderr, "%s: $$ = %d\n", instruct1[0], child1);
            fprintf(stderr, "%s: $$ = %d\n", instruct2[0], child2);
            waitpid(child2, &state2, WUNTRACED);
        }
    }
    if (child1 == 0)
    {
        close(pipefd[0]);
        dup2(pipefd[1], 1);
        execve(instruct1[0], instruct1, NULL);
        perror("execve");
    }
    if (child1 > 0)
    {
        fprintf(stderr, "%s: $? = %d\n", instruct1[0], WEXITSTATUS(state1));
        fprintf(stderr, "%s: $? = %d\n", instruct2[0], WEXITSTATUS(state2));
        close(pipefd[0]);
        close(pipefd[1]);
    }
    return 0;
}
