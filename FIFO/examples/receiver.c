#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <linux/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include "rppipe.h"


int main(void)
{
    if(create_pipe() != EXIT_SUCCESS)
    {
        perror("Failed to create pipe");
        exit(EXIT_FAILURE);
    }

    while(1)
    {
		printf("received: %d\n", read_value_from_pipe());
    }

    return 0;
}   
