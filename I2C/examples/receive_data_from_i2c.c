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
	RCErrorContext *errcont;

	/*  initialize contexts */
	if(error_context_init(&errcont) == RC_EINIT)
	{
		rcerror(errcont, NULL, RC_EXIT);
	}

	if(rpi_init(&RPi) == RC_EINIT)
	{
		rcerror(errcont, RPi, RC_EXIT);
	}

	if(pc104_init(&PC104) == RC_EINIT)
	{
		rpi_destruct(RPi);
		rcerror(errcont, PC104, RC_EXIT);
	}

    	/*  open I2C connection */
	int status;
	if((status = open_i2c(RPi, PC104)) != RC_SUCCESS)
	{
		pc104_destruct(PC104);
		rcerror(errcont, RPi, RC_EXIT);		
	}

	/*	receive data from I2C	*/
	while(receive_from_slave_via_i2c(PC104) == RC_SUCCESS)
	{
		printf("\nData read: %d\nVoltage: %d\n", 
					PC104->distance_from_IR_sensor,
					PC104->battery_voltage_mV);	
	}
		
	close(RPi->i2c_bus_descriptor);	
	rpi_destruct(RPi);
	pc104_destruct(PC104);
	error_context_destruct(errcont);	

	return 0;
}
