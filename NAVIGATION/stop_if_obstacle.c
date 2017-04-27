#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

#include "../RCC/rccore.h"
#include "../I2C/rci2c.h"
#include "../SENSORS/rcsensors.h"

#define ENG_VAL 9


int left(RPiContext*);
int right(RPiContext*);
int backward(RPiContext*);
int forward(RPiContext*);
int stop(RPiContext*);

enum EDirections
{
	FORWARD = 11,
	BACKWARD = 00,
	LEFT = 10,
	RIGHT = 01,
	STOP = -1
};


int main(int argc, char **argv)
{
	/*	INITIALIZATION PART	*/
	RPiContext *RPi;
	PC104Context *PC104;
	RCErrorContext *errcont;
	
	if(error_context_init(&errcont) != RC_SUCCESS)
	{
		rcerror(errcont, NULL, RC_EXIT);
	}

	if(rpi_init(&RPi) != RC_SUCCESS)
	{	
		rcerror(errcont, RPi, RC_EXIT);		
	}
	
	if(pc104_init(&PC104) != RC_SUCCESS)
	{
		rcerror(errcont, PC104, RC_CONT);
		rpi_destruct(RPi);
	}
	
	if(open_i2c(RPi, PC104) != RC_SUCCESS)
	{
		pc104_destruct(PC104);
		rcerror(errcont, RPi, RC_EXIT);
	}
	
	setup_USRF();
	/*	INITIALIZATION END	*/
		

	int last_command = STOP;
	/*	receive data from ultrasonic sensor and change steering vector	*/
	while(get_distance_USRF(RPi) == RC_SUCCESS)	
	{
		if(RPi->distance_from_USRF_sensor <= 5)
		{
			break;	
		}

		if(RPi->distance_from_USRF_sensor < 15)
		{
			if(last_command != STOP)
			{
				stop(RPi);
				last_command = STOP;
			}
		}
		else
		{
			if(last_command != FORWARD)
			{
				forward(RPi);
				last_command = FORWARD;
			}
		}
	}
	
	close(RPi->i2c_bus_descriptor);
	rpi_destruct(RPi);
	pc104_destruct(PC104);
	error_context_destruct(errcont);

	return 0;
}


int forward(RPiContext* rpi)
{
	puts("FORWARD");
	return send_to_slave_via_i2c(rpi, ENG_VAL, ENG_VAL);	
}

int backward(RPiContext *rpi)
{
	puts("BACKWARD");
	return send_to_slave_via_i2c(rpi, -ENG_VAL, -ENG_VAL);
}

int left(RPiContext *rpi)
{	
	puts("LEFT");
	return send_to_slave_via_i2c(rpi, -ENG_VAL, ENG_VAL);
}

int right(RPiContext *rpi)
{
	puts("RIGHT");
	return send_to_slave_via_i2c(rpi, ENG_VAL, -ENG_VAL);
}

int stop(RPiContext *rpi)
{
	puts("STOP");
	return send_to_slave_via_i2c(rpi, 0, 0);
}
