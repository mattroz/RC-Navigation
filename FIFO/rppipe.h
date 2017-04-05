#ifndef RPPIPE_H
#define RPPIPE_H

#include "../RCC/rccore.h"

/*	Function for creating a pipe, returns error code 
 *	according to enum at RCC/rccore.h	*/
int create_pipe(RPiContext*);	

/*	Function for reading data from pipe. 
 *	Reads one value at a time, returns 
 *	RC_PIPE_EREAD on read error, or RC_SUCCESS */
int read_value_from_pipe(RPiContext*, int*);

/*	function writes given value to the pipe.
 *	Returns either RC_SUCCESS or RC_PIPE_EWRITE
 *	on writing issues	*/
int write_value_to_pipe(RPiContext*, int);

#endif
