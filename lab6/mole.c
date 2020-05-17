#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

void main(int argc, char **argv)
{
    char dir[1500];
    snprintf(dir, 1500, "%s/lab6.log", argv[2]);
    FILE *file = fopen(path, "a");
    char pop[10];
    if (file != 0 && argc > 1)
    {
        sprintf(pop, "Pop %s\n", argv[1]);
        fputs(pop, file);
        fclose(file);
    }
}
