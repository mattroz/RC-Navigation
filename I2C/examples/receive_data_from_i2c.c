#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

#include "../../RCC/rccore.h"
#include "../../RCIP/rcip.h"
#include "../rci2c.h"

int main()
{
    	RPiContext *RPi;
    	PC104Context *PC104;
	RCErrorContext *errcont = malloc(sizeof(RCErrorContext));

	/*  initialize contexts */
	if(rpi_init(&RPi) == RC_EINIT)
	{
		rcerror(errcont, RPi, RC_EINIT, RC_EXIT);
	}

	if(pc104_init(&PC104) == RC_EINIT)
	{
		rcerror(errcont, PC104, RC_EINIT, RC_EXIT);
    	}

    	/*  open I2C connection */
	int status;
	if((status = open_i2c(RPi, PC104)) != RC_SUCCESS)
	{
		rcerror(errcont, RPi, status, RC_EXIT);		
	}

	/*	receive data from I2C	*/
	while(receive_from_slave_via_i2c(PC104) == RC_SUCCESS)
	{
		printf("Data read: %lu\n", PC104->distance_from_IR_sensor);	
	}
		
	close(RPi->i2c_bus_descriptor);
	
	free(errcont);
	rpi_destruct(RPi);
	pc104_destruct(PC104);
	
	rcerror(errcont, PC104, PC104->last_error, RC_CONT);	

	return 0;
}
