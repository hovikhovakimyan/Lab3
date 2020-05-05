#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/errno.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int killsigs = 0;
int totalsigs = 0;
char* signalsarr[27]= {"HUP", "INT", "QUIT", "ILL", "TRAP", "ABRT", "IOT", "BUS", "FPE", "USR1", "SEGV", "USR2", "PIPE", "ALRM", "TERM", "STKFLT", "CHLD", "CONT", "TSTP", "TTIN", "TTOU", "URG", "XCPU", "XFSZ", "VTALRM", "PROF", "WINCH"};

void sighandler(int signalnum)
{
    printf("%s caught at %ld\n", signalsarr[signalnum - 1], time(NULL));
    totalsigs++;

    if (signalnum == SIGTERM)
    {
        killsigs++;
    }
    else
    {
        killsigs = 0;
    }
}

int main(int argc, char **argv)
{
    fprintf(stderr, "PID = %d\n", getpid());
    for (int i = 1; i < argc; i++)
    {
        for (int j = 0; j < 27; j++)
        {
            if (strcmp(argv[i], signalsarr[j]) == 0)
            {
                signal(j + 1, sighandler);
            }
        }
    }
    while (killsigs < 3)
    {
        pause();
    }
    fprintf(stderr, "Total signals count = %d\n", totalsigs);
    return 0;
}
