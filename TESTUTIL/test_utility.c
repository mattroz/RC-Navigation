#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../I2C/rci2c.h"
#include "../RCC/rccore.h"

const int capitalize_offset = -20;
const int ascii_digit_offset = -48;

int left_engine_power = 0;
int right_engine_power = 0;

enum EKeyCodes
{
	Q	= 	81,
	A	= 	65,
	E	= 	69,
	D	= 	68,
	ESC	= 	27
};

enum EEngines
{
	LEFT = 0,
	RIGHT		
};

enum EDirection
{
	BACKWARD = -1,
	FORWARD = 1
};

/*	functions prototype	*/
int send(RPiContext*, int, int, int);


int main()
{
	/*	contexts	*/
	RPiContext *rpi;
	PC104Context *pc104;
	RCErrorContext *errcont = malloc(sizeof(RCErrorContext));
	
	int keycode = A;
	int engine_select = 0;	/*	0 - left, 1 - right	*/
	int direction = 1;		/*	0 - minus, 1 - plus	*/
	int power = 0;

	/*  initialize contexts */
    if(rpi_init(&rpi) == RC_EINIT)
    {
        rcerror(errcont, rpi, RC_EXIT);
    }

    if(pc104_init(&pc104))
    {
        rcerror(errcont, pc104, RC_EXIT);
    }
    
    /*  open I2C connection */
    if(open_i2c(rpi, pc104) != RC_SUCCESS)
    {
        rcerror(errcont, rpi, RC_EXIT);
    }


	/*	get keycode and power and capitalize it	*/
	while((keycode = getc(stdin)) != ESC)
	{
		/*	send previous values	*/
		send(rpi, engine_select, direction, power);

		power = getc(stdin);
		if(keycode == 10)	/*	if we caught newline, swap keycode and power, then getc power	*/
		{
			keycode = power;
			power = getc(stdin);		
		}

		power += ascii_digit_offset;
		switch(toupper(keycode))
		{
			case Q :
				printf("keycode for Q, %d\n", power);
				engine_select = LEFT;
				direction = FORWARD;
				send(rpi, engine_select, direction, power);
				continue;
			case A :
            	printf("keycode for A, %d\n", power);
            	engine_select = LEFT;
				direction = BACKWARD;
				continue;
			case E :
            	printf("keycode for E, %d\n", power);
            	engine_select = RIGHT;
				direction = FORWARD;	
				continue;
			case D :
            	printf("keycode for D, %d\n", power);
            	engine_select = RIGHT;
				direction = BACKWARD;
				continue;
			default:
				printf("once again\n");
				continue;
		}
	}

	rpi_destruct(rpi);
	pc104_destruct(pc104);
	free(errcont);	

	return 0;
}


/*	functions definition	*/
int send(RPiContext *_rpi, int es, int dir, int pow)
{
	/*	if direction is backward, change value's sign */
	pow *= dir;
	switch(es)
	{
		case LEFT:
			left_engine_power = pow;
			break;
		case RIGHT:
			right_engine_power = pow;
		default:
			return -1;			
	}

	send_to_slave_via_i2c(_rpi, left_engine_power, right_engine_power);
	
	return 0;	
}
