#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <linux/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>

#include "../RCC/rccore.h"

const char *pipepath = "/var/run/raspi_pipe";

/*---------------------------------------
 *	define function for pipe creating
 *---------------------------------------*/
int create_pipe()
{
	/*	create named pipe with presetted mode and the given name	*/
	mode_t pipemode = 0666;
	int status = mkfifo(pipepath, pipemode);
	
	if(errno == EEXIST && errno != -1)
	{
		return RC_SUCCESS;
	}

	return RC_EPIPE_CREATE;
}


/*---------------------------------------------------
 *  define function for reading value from the pipe
 *--------------------------------------------------*/
int read_value_from_pipe()
{
	FILE *pipe_descriptor;
	int value;

	/*	start to listen to the pipe	*/
	pipe_descriptor = fopen(pipepath, "r");

	/*	handle pipe opening error	*/
	if(pipe_descriptor == NULL)
	{
		perror("Failed reading value from pipe");
		exit(EXIT_FAILURE);	
	}
	
	/*	get value from the pipe, then close connection	*/
	fscanf(pipe_descriptor, "%d", &value);
	fclose(pipe_descriptor);
	
	return value;		
}


/*---------------------------------------------------
 *  define function for writing value to the pipe
 *--------------------------------------------------*/
int write_value_to_pipe(int value)
{
	FILE *pipe_descriptor;
	
	/*	open pipe for writing	*/	
	pipe_descriptor = fopen(pipepath, "w");
	
	/*	handle pipe opening error	*/
	if(pipe_descriptor == NULL)
	{
		return EXIT_FAILURE;
	}
	
	/*	write value to the pipe and close it	*/
	fprintf(pipe_descriptor, "%d\n", value);
	fclose(pipe_descriptor);

	return EXIT_SUCCESS;
}
