#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Need atleast 1 argument\n");
        return 0;
    }
    unsigned int address = atoi(argv[1]);
    unsigned int pagesize = 4096;
    printf("The address %d contains:\npage number = %d\noffset = %d\n",
           address, address / pagesize, address % pagesize);
    return 0;
}
