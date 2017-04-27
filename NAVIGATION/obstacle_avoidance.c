#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

#include "../RCC/rccore.h"
#include "../I2C/rci2c.h"
#include "../SENSORS/rcsensors.h"

#define ENG_VAL 5

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
		

	
	/*	receive data from ultrasonic sensor and change steering vector	*/
	while(receive_from_slave_via_i2c(PC104) == RC_SUCCESS)
	{
		get_distance_USRF(RPi);
		//printf("%d\n", RPi->distance_from_USRF_sensor);
		printf("%d\n", PC104->distance_from_IR_sensor);
		
		/*	check if we have an obstacle in front of the robot	*/
		if(RPi->distance_from_USRF_sensor <= 10)
		{
			stop(RPi);
			sleep(1);
			right(RPi);
			continue;
		}
	
		if((PC104->distance_from_IR_sensor >= 7) && (PC104->distance_from_IR_sensor <= 12))
		{
			forward(RPi);
			continue;
		}	
		
		if(PC104->distance_from_IR_sensor > 13)
		{
			left(RPi);
			continue;
		}
	
		if(PC104->distance_from_IR_sensor < 7)
		{
			right(RPi);
			continue;
		}
	}	


	/*	deallocate all contexts and close i2c	*/	
	close(RPi->i2c_bus_descriptor);
	rpi_destruct(RPi);
	pc104_destruct(PC104);
	error_context_destruct(errcont);

	return 0;
}


int forward(RPiContext* rpi)
{
	if(last_command != FORWARD)
	{	
		puts("FORWARD");
		last_command = FORWARD;
		return send_to_slave_via_i2c(rpi, ENG_VAL+3, ENG_VAL+3);	
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
		return send_to_slave_via_i2c(rpi, -ENG_VAL, ENG_VAL);
	}
	return 0;
}

int right(RPiContext *rpi)
{
	if(last_command != RIGHT)
	{
		puts("RIGHT");
		last_command = RIGHT;
		return send_to_slave_via_i2c(rpi, ENG_VAL, -ENG_VAL);
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
