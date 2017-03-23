#ifndef RPPIPE_H
#define RPPIPE_H

extern const char *pipepath;

/*	function for creating a pipe, returns EXIT_STATUS on success
 *	or some of mkfifo(3) error statuses	*/
int create_pipe();	

/*	function for reading data from pipe. 
 *	Reads one value at a time, returns 
 *	either value or EXIT_FAILURE on error */
int read_value_from_pipe();

/*	function writes given value to the pipe.
 *	Returns EXIT_SUCCESS or EXIT_FAILURE, depends on
 *	what has happened there	*/
int write_value_to_pipe(int);

#endif
