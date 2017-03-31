#include <stdio.h>
#include <stdlib.h>

#include "rccore.h"

/*Raspberry Pi context initializer and destructor definition*/
int rpi_init(RPiContext **rpi)
{
	*rpi = malloc(sizeof(RPiContext));
	if(*rpi == NULL)	return -1;

	(*rpi)->identifier = _RASPBERRY_;	
	(*rpi)->version = RPI_VERSION;
	(*rpi)->i2c_path = DEFAULT_I2C_PATH;
	(*rpi)->pipe_path = DEFAULT_PIPE_PATH;	
		
	return 0;
}

void rpi_destruct(RPiContext *rpi)
{
	free(rpi);
}


/*	PC104 context initializer and destructor definition	*/
int pc104_init(PC104Context **pc104)
{
	*pc104 = malloc(sizeof(PC104Context));
	if(*pc104 == NULL) return -1;
	
	(*pc104)->identifier = _PC104_;
	(*pc104)->version = PC104_VERSION;
	(*pc104)->i2c_slave_addr = DEFAULT_PC104_I2C_SLAVE_ADDR;	
	
	return 0;
}


void pc104_destruct(PC104Context *pc104)
{
	free(pc104);
}


/*	contexts' error handling	
void rc_err_handle(void *context)
{
	/*	check if this pointer not NULL	
	if(context == NULL)
	{
		perror("Context haven't been initialized");
		exit(EXIT_FAILURE);
	}	

	/*	check if we've been given either Raspberry or PC104 context	
	if(((RPiContext*)context)->identifier == _RASPBERRY_)
	{
		uint8_t errval = ((RPiContext*)context)->last_error;
		fprintf(stderr, "%s:", ,errval);					
	}
	else if(((PC104Context*)context)->identifier == _PC104_)
	{
	
	}
}	
*/		
