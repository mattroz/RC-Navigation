#ifndef RCPIPE_H
#define RCPIPE_H

#include "../RCC/rccore.h"

/*	Function for creating a pipe, returns error code 
 *	according to enum at RCC/rccore.h .
 *	Returns	RC_EINIT if Raspbery context pointer is NULL, 
 *	RC_PIPE_ECREATE if can't create the pipe and
 *	RC_SUCCESS on successfull pipe creating	*/
int create_pipe(RPiContext*);	

/*	Function for reading data from pipe. 
 *	Reads one value at a time, returns 
 *	RC_EINIT if context is NULL,
 *	RC_PIPE_EREAD on read error, or RC_SUCCESS */
int read_value_from_pipe(RPiContext*, int*);

/*	Function writes given value to the pipe.
 *	Returns RC_EINIT if context is NULL, 
 *	RC_SUCCESS or RC_PIPE_EWRITE on writing issues	*/
int write_value_to_pipe(RPiContext*, int);

#endif
