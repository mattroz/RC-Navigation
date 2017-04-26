#include <stdio.h>
#include <stdlib.h>

#include "../rccore.h"

int main()
{
	RPiContext *RPi;
	PC104Context *PC104;
	RCErrorContext *errcont;
	
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
	
	rpi_destruct(RPi);
	pc104_destruct(PC104);
	error_context_destruct(errcont);

	
	return 0;
}
