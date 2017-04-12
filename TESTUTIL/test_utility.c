#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//#include "../I2C/rci2c.h"
//#include "../RCC/rccore.h"

int capitalize_offset = -20;
typedef enum EKeyCodes
{
	Q = 81,
	A = 65,
	E = 69,
	D = 68
}key_code_t;


int main()
{
	int keycode = getc(stdin);
	switch(toupper(keycode))
	{
		case Q :
			printf("keycode for Q\n");
			break;
		case A :
            printf("keycode for A\n");
            break;
		case E :
            printf("keycode for E\n");
            break;
		case D :
            printf("keycode for A\n");
            break;
	}

	printf("%d\n", keycode);
	return 0;
}
