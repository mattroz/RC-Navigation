#include <stdio.h>
#include <stdlib.h>

#include "rccore.h"


/*Raspberry Pi context initializer and destructor definition*/
int rpi_init(RPiContext **rpi)
{
	*rpi = malloc(sizeof(RPiContext));
	if(*rpi == NULL)	return RC_EALLOC;

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
	if(*pc104 == NULL) return RC_EALLOC;
	
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
void rcerror(int errcode)
{
	fprintf(stderr, "%s, error code: %d\n", RCErrorMessage[errcode], errcode);
	exit(EXIT_FAILURE);
}	
		
