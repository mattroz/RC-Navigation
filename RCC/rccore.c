#include <stdio.h>
#include <stdlib.h>

#include "rccore.h"

/*Raspberry Pi context initializer and destructor definition*/
int rpi_init(RPiContext **rpi)
{
	*rpi = malloc(sizeof(RPiContext));
	if(*rpi == NULL)	return -1;
	
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

	(*pc104)->version = PC104_VERSION;
	(*pc104)->i2c_slave_addr = DEFAULT_PC104_I2C_SLAVE_ADDR;	
	
	return 0;
}


void pc104_destruct(PC104Context *pc104)
{
	free(pc104);
}
