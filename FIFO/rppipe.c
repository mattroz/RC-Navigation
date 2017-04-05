#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <linux/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>

#include "../RCC/rccore.h"

/*---------------------------------------
 *	define function for pipe creating
 *---------------------------------------*/
int create_pipe(RPiContext *rpi)
{
	if(rpi == NULL)
	{
		return RC_EINIT;
	}	

	/*	create named pipe with presetted mode and the given name	*/
	mode_t pipemode = 0666;
	mkfifo(rpi->pipe_path, pipemode);
	
	if(errno == EEXIST && errno != -1)
	{
		return RC_SUCCESS;
	}
	
	rpi->last_error = RC_PIPE_ECREATE;
	return RC_PIPE_ECREATE;
}


/*---------------------------------------------------
 *  define function for reading value from the pipe
 *--------------------------------------------------*/
int read_value_from_pipe(RPiContext *rpi, int *value)
{
	if(rpi == NULL)
    {
        return RC_EINIT;
    }	

	FILE *pipe_descriptor;

	/*	start listening to the pipe	*/
	pipe_descriptor = fopen(rpi->pipe_path, "r");

	/*	handle pipe opening error	*/
	if(pipe_descriptor == NULL)
	{
		rpi->last_error = RC_PIPE_EREAD;
		return RC_PIPE_EREAD;
	}
	
	/*	get value from the pipe, then close connection	*/
	fscanf(pipe_descriptor, "%d", value);
	fclose(pipe_descriptor);
	
	return RC_SUCCESS;		
}


/*---------------------------------------------------
 *  define function for writing value to the pipe
 *--------------------------------------------------*/
int write_value_to_pipe(RPiContext *rpi, int value)
{
	if(rpi == NULL)
    {
        return RC_EINIT;
    }

	FILE *pipe_descriptor;
	
	/*	open pipe for writing	*/	
	pipe_descriptor = fopen(rpi->pipe_path, "w");
	
	/*	handle pipe opening error	*/
	if(pipe_descriptor == NULL)
	{
		rpi->last_error = RC_PIPE_EWRITE;
        return RC_PIPE_EWRITE;
	}
	
	/*	write value to the pipe and close it	*/
	fprintf(pipe_descriptor, "%d\n", value);
	fclose(pipe_descriptor);

	return RC_SUCCESS;
}
