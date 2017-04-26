#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <linux/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>

#include "../rcpipe.h"
#include "../../RCC/rccore.h"

int main()
{
	RPiContext *RPi;
	PC104Context *PC104;
	RCErrorContext *errcont;

	/*  initialize contexts */
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

	/*	create pipe	*/
	if(create_pipe(RPi) != RC_SUCCESS)
	{
		pc104_destruct(PC104);
		rcerror(errcont, RPi, RC_EXIT);
	}

	int i = 0;
	while(1)
	{
		if(write_value_to_pipe(RPi, i++) != RC_SUCCESS)
		{
			rcerror(errcont, RPi, RC_EXIT);
		}
		usleep(1000);
	}

	pc104_destruct(PC104);
	rpi_destruct(RPi);
	error_context_destruct(errcont);
	
	return 0;
}

