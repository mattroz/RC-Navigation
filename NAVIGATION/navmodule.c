#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../RCC/rccore.h"
#include "../I2C/rci2c.h"
#include "../SENSORS/rcsensors.h"


int main(int argc, char **argv)
{
	/*	INITIALIZATION PART	*/
	RPiContext *RPi;
	PC104Context *PC104;
	RCErrorContext *errcontext = malloc(sizeof(RCErrorContext));
	
	if(errcontext == NULL)
	{
		rcerror(errcontext, NULL, RC_EXIT);
	}

	if(rpi_init(&RPi) != RC_SUCCESS)
	{	
		rcerror(errcontext, RPi, RC_EXIT);		
	}
	
	if(pc104_init(&PC104) != RC_SUCCESS)
	{
		rcerror(errcontext, PC104, RC_CONT);
		rpi_destruct(RPi);
	}
	
	if(open_i2c(RPi, PC104) != RC_SUCCESS)
	{
		pc104_destruct(PC104);
		rcerror(errcontext, RPi, RC_EXIT);
	}
	
	setup_usrf();
	/*	INITIALIZATION END	*/
		

	/*	receive data from ultrasonic sensor and change steering vector	*/
	while(1)	
	{
		RPi->distance_from_USRF_sensor = get_distance_in_cm();
		if(RPi->distance_from_USRF_sensor < 15)
		{
			if(send_to_slave_via_i2c(RPi, 0, 0) == RC_SUCCESS)
				puts("STOP");
		}
		else
		{
			if(send_to_slave_via_i2c(RPi, 7, 7) == RC_SUCCESS)
				puts("FORWARD");
		}
		usleep(5000);
	}
	
	close(RPi->i2c_bus_descriptor);
	rpi_destruct(RPi);
	pc104_destruct(PC104);
	free(errcontext);

	return 0;
}
