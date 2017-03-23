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

	int i = 0;
	while(1)
	{
		if(write_value_to_pipe(i++) == EXIT_FAILURE)
		{
			perror("Failed to write value to pipe\n");
			exit(EXIT_FAILURE);
		}
		usleep(1000);
	}

	return 0;
}

