#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//#include "../I2C/rci2c.h"
//#include "../RCC/rccore.h"

int capitalize_offset = -20;
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
	/*	get keycode and capitalize it	*/
	int keycode;
	int engine_select;	/*	0 - left, 1 - right	*/
	int direction;		/*	0 - minus, 1 - plus	*/

	while((keycode = getc(stdin)) != ESC)
	{
		switch(toupper(keycode))
		{
			case Q :
				printf("keycode for Q\n");
				continue;
			case A :
            	printf("keycode for A\n");
            	continue;
			case E :
            	printf("keycode for E\n");
            	continue;
			case D :
            	printf("keycode for A\n");
            	continue;
			case:
				continue;
		}
	}

	printf("%d\n", keycode);
	return 0;
}
