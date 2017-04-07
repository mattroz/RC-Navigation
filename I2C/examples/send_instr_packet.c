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

	/*	initialize contexts	*/
	if(rpi_init(&RPi) == RC_EINIT)
	{
		rcerror(errcont, RPi, RC_EXIT);
	}
	
	if(pc104_init(&PC104) == RC_EINIT)
	{
		rcerror(errcont, RPi, RC_EXIT);
	}
	
	/*	open I2C connection	*/	
	if(open_i2c(RPi, PC104) != RC_SUCCESS)
	{
		rcerror(errcont, RPi, RC_EXIT);
	}

	while(1)
	{
		if(send_to_slave_via_i2c(RPi, 10, 10) != RC_SUCCESS)
		{
			rcerror(errcont, RPi, RC_CONT);
		}
	}	

	close(RPi->i2c_bus_descriptor);
		
	return 0;
}
