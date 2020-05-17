#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

pid_t moleone, moletwo;
char dir[1500];
char moledir[1510];
void sighandler(int signalnum)
{
    snprintf(moledir, 1510, "%s/mole", dir);
    char *moleOneArgs[4] = {"mole", "mole1", dir, NULL};
    char *moleTwoArgs[4] = {"mole", "mole2", dir, NULL};
    int randomnum = (rand() % 2) + 1;
    if (signalnum == SIGTERM)
    {
        kill(moleone, SIGTERM);
        kill(moletwo, SIGTERM);
        exit(EXIT_SUCCESS);
    }
    else if (signalnum == SIGUSR1)
    {
        if (moleone)
            kill(moleone, SIGKILL);
        moleone = fork();
        if (moleone == 0)
        {
            if (randomnum == 1)
            {
                execve(moledir, moleOneArgs, NULL);
            }
            else if (randomnum == 2)
            {
                execve(moledir, moleTwoArgs, NULL);
            }
        }
    }
    else if (signalnum == SIGUSR2)
    {
        if (moletwo)
            kill(moletwo, SIGKILL);
        moletwo = fork();
        if (moletwo == 0)
        {
            if (randomnum == 1)
            {
                execve(moledir, moleOneArgs, NULL);
            }
            else if (randomnum == 2)
            {
                execve(moledir, moleTwoArgs, NULL);
            }
        }
    }
}

int main(void)
{

    pid_t daemon, sid;
    srand(time(0));
    daemon = fork();
    if (daemon < 0)
    {
        printf("fork failed");
        exit(EXIT_FAILURE);
    }
    if (daemon > 0)
    { // Child can continue to run even after the parent has finished executing
        printf("Daemon pid = %d\n", daemon);
        exit(EXIT_SUCCESS);
    }
    signal(SIGUSR1, sighandler);
    signal(SIGUSR2, sighandler);
    signal(SIGTERM, sighandler);
    getcwd(dir, 1500);

    /* Change the file mode mask */
    umask(0);

    /* Open any logs here */

    /* Create a new SID for the child process */
    sid = setsid();
    if (sid < 0)
    {
        /* Log the failure */
        exit(EXIT_FAILURE);
    }

    /* Change the current working directory */
    if ((chdir("/")) < 0)
    {
        exit(EXIT_FAILURE);
    }

    /* Close out the standard file descriptors */
    //Because daemons generally dont interact directly with user so there is no need of keeping these open
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    int fd = open("/dev/null", O_RDONLY);
    dup2(fd, STDIN_FILENO);
    dup2(fd, STDOUT_FILENO);
    dup2(fd, STDERR_FILENO);
    close(fd);

    /* Daemon-specific initialization goes here */
    /* An infinite loop */
    while (1)
    {
        pause();
    }
    exit(EXIT_SUCCESS);
}