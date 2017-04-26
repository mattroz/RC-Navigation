#include <stdio.h>
#include <stdlib.h>

#include "rccore.h"


/*Raspberry Pi context initializer and destructor definition*/
int rpi_init(RPiContext **rpi)
{
	*rpi = malloc(sizeof(RPiContext));
	
	if(*rpi == NULL) return RC_EINIT;

	(*rpi)->identifier = _RASPBERRY_;	
	(*rpi)->version = RPI_VERSION;
	(*rpi)->i2c_path = DEFAULT_I2C_PATH;
	(*rpi)->pipe_path = DEFAULT_PIPE_PATH;	
		
	return RC_SUCCESS;
}


void rpi_destruct(RPiContext *rpi)
{
	free(rpi);
}


/*	PC104 context initializer and destructor definition	*/
int pc104_init(PC104Context **pc104)
{
	*pc104 = malloc(sizeof(PC104Context));
	if(*pc104 == NULL) return RC_EINIT;
	
	(*pc104)->identifier = _PC104_;
	(*pc104)->version = PC104_VERSION;
	(*pc104)->i2c_slave_addr = DEFAULT_PC104_I2C_SLAVE_ADDR;	
	
	return RC_SUCCESS;
}


void pc104_destruct(PC104Context *pc104)
{
	free(pc104);
}


/*	Error handling	*/
void rcerror(RCErrorContext *error_context, void *culprit, int status)
{	
	/*	if culprit context hadn't been initialized, there is no way to spot 
		which context have failed ('cause we have NULL pointer instead of 
		context pointer, thats why this error is hadling separately)	*/
	if(culprit == NULL || error_context == NULL)
	{
		if(culprit != NULL)
		{
			free(culprit);
		}
		else if(error_context != NULL)
		{
			free(error_context);
		}
		fprintf(stderr, "Error: context haven't been initialized, abort\n");
		exit(EXIT_FAILURE);
	}
	
	/*	WARNING: POTENTIONALLY DANGEROUS CODE (TODO think about refactoring it somehow)	*/
	/*	check which context	caused an error	(mad typecasting) and set last error field. */
	if((((RPiContext*)culprit)->identifier == _RASPBERRY_))
	{
		error_context->culprit_context = _RASPBERRY_;
		error_context->last_error_code = ((RPiContext*)culprit)->last_error;
	}
	else if((((PC104Context*)culprit)->identifier == _PC104_))
	{
		error_context->culprit_context = _PC104_;		
		error_context->last_error_code = ((PC104Context*)culprit)->last_error;
	}
	else
	{
		error_context->culprit_context = "UNKNOWN";
		error_context->last_error_code = RC_EINIT;
	}
	
	int errcode = error_context->last_error_code;
	error_context->last_error_message = RCErrorMessage[errcode];
		
	puts("=========== ERROR ===========");
	fprintf(stderr, "Message: %s\nContext: %s\nError code: %d\n", 
					RCErrorMessage[errcode], 
					error_context->culprit_context, 
					errcode);
	puts("=============================");
	
	/*	if user threw exit flag, just exit after printing error message	*/
	if(status == RC_EXIT) 
	{
		free(culprit);
		free(error_context);	
		exit(EXIT_FAILURE);
	}
}
		
