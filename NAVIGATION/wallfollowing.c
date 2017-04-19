#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

#include "../RCC/rccore.h"
#include "../I2C/rci2c.h"
#include "../SENSORS/rcsensors.h"

#define ENG_VAL 7

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

int last_command = STOP;


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
	while(receive_from_slave_via_i2c(PC104) == RC_SUCCESS)
	{
//		printf("%d\n", PC104->distance_from_IR_sensor);
		if((PC104->distance_from_IR_sensor >= 7) && (PC104->distance_from_IR_sensor <= 13))
		{
			forward(RPi);
			continue;
		}	
		
		if(PC104->distance_from_IR_sensor > 13)
		{
//			stop(RPi);
			left(RPi);
//			usleep(500000);
//			stop(RPi);
			continue;
		}
	
		if(PC104->distance_from_IR_sensor < 7)
		{
//			stop(RPi);
			right(RPi);
//			usleep(500000);
//			stop(RPi);
			continue;
		}
//		forward(RPi);
	}	


	/*	dispose all contexts and close i2c	*/	
	close(RPi->i2c_bus_descriptor);
	rpi_destruct(RPi);
	pc104_destruct(PC104);
	free(errcontext);

	return 0;
}


int forward(RPiContext* rpi)
{
	if(last_command != FORWARD)
	{	
		puts("FORWARD");
		last_command = FORWARD;
		return send_to_slave_via_i2c(rpi, ENG_VAL, ENG_VAL);	
	}
	return 0;
}

int backward(RPiContext *rpi)
{
	if(last_command != BACKWARD)
	{
		puts("BACKWARD");
		last_command = BACKWARD;
		return send_to_slave_via_i2c(rpi, -ENG_VAL, -ENG_VAL);
	}
	return 0;
}

int left(RPiContext *rpi)
{	
	if(last_command != LEFT)
	{
		puts("LEFT");
		last_command = LEFT;
		return send_to_slave_via_i2c(rpi, 0, ENG_VAL);
	}
	return 0;
}

int right(RPiContext *rpi)
{
	if(last_command != RIGHT)
	{
		puts("RIGHT");
		last_command = RIGHT;
		return send_to_slave_via_i2c(rpi, ENG_VAL, 0);
	}
	return 0;
}

int stop(RPiContext *rpi)
{
	if(last_command != STOP)
	{
		puts("STOP");
		last_command = STOP;
		return send_to_slave_via_i2c(rpi, 0, 0);
	}
	return 0;
}
