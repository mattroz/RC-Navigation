#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <linux/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>

#include "../rppipe.h"
#include "../../RCC/rccore.h"

int main()
{
	RPiContext *RPi;
	PC104Context *PC104;
	RCErrorContext *errcont = malloc(sizeof(RCErrorContext));	

	/*	initialize contexts	*/
	if(rpi_init(&RPi) == RC_EINIT)
	{
		rcerror(errcont, RPi, RC_EINIT, RC_EXIT);
	}

	if(pc104_init(&PC104) == RC_EINIT)
    {
        rcerror(errcont, PC104, RC_EINIT, RC_EXIT);
    }


    if(create_pipe(RPi) != RC_SUCCESS)
    {
		rcerror(errcont, RPi, RPi->last_error, RC_EXIT);
    }

	int value;
    while(1)
    {	
		if(read_value_from_pipe(RPi, &value) != RC_SUCCESS)
		{
			rcerror(errcont, RPi, RPi->last_error, RC_EXIT);
		}
	
		printf("received: %d\n", value);
    }

	pc104_destruct(PC104);
	rpi_destruct(RPi);
	free(errcont);

    return 0;
}   
