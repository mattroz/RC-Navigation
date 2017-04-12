#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../I2C/rci2c.h"
#include "../RCC/rccore.h"

const int capitalize_offset = -20;
const int ascii_digit_offset = -48;

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
	MINUS = 0,
	PLUS
};


int main()
{
	/*	contexts	*/
	RPiContext *rpi;
	PC104Context *pc104;
	RCErrorContext *errcont = malloc(sizeof(RCErrorContext));
	
	/*	initialize contexts	*/
	rpi_init(&rpi);
	pc104_init(&pc104);

	/*	get keycode and capitalize it	*/
	int keycode;
	int engine_select;	/*	0 - left, 1 - right	*/
	int direction;		/*	0 - minus, 1 - plus	*/
	int power;

	while((keycode = getc(stdin)) != ESC)
	{
		power = getc(stdin);
		if(keycode == 10)	/*	if we caught newline, swap keycode and power, then getc power	*/
		{
			keycode = power;
			power = getc(stdin);		
		}

		switch(toupper(keycode))
		{
			case Q :
				printf("keycode for Q, %d\n", power+ascii_digit_offset);
				engine_select = LEFT;
				continue;
			case A :
            	printf("keycode for A, %d\n", power+ascii_digit_offset);
            	continue;
			case E :
            	printf("keycode for E, %d\n", power+ascii_digit_offset);
            	continue;
			case D :
            	printf("keycode for D, %d\n", power+ascii_digit_offset);
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
