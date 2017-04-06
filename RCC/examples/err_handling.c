#include <stdio.h>
#include <stdlib.h>

#include "../rccore.h"

int main()
{
	RPiContext *RPi;
	PC104Context *PC104;
	RCErrorContext *errcont = malloc(sizeof(RCErrorContext));
	/*
	if(rpi_init(&RPi) == RC_EINIT)
	{
		rcerror(errcont, RPi, RC_EINIT, RC_EXIT);
	}*/
	
	if(pc104_init(&PC104) == RC_EINIT)
	{
		rcerror(errcont, PC104, RC_EXIT);
	}

	rcerror(errcont, RPi, RC_EXIT);
	
	rpi_destruct(RPi);
	pc104_destruct(PC104);
	free(errcont);

	
	return 0;
}
