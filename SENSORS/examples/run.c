#include <stdio.h>
#include <stdlib.h>

#include "../rcsensors.h"
#include "../../FIFO/rcpipe.h"
#include "../../RCC/rccore.h"

int main()
{
	/*	setup block	*/
	setup_USRF();

	RPiContext *rpi;
	RCErrorContext *errcont;
	error_context_init(&errcont);
	rpi_init(&rpi);
		
	int data[2];
	/*	data translation to output (potentionally, PIPE)	*/
	while(1)
	{
		if(get_distance_USRF(rpi) == RC_EINIT)
		{
			rcerror(errcont, rpi, RC_EXIT);
		}
     
		data[1] = rpi->distance_from_USRF_sensor;
		data[1] = (data[1] > USRF_MAX_VAL_CM) ? data[0] : data[1];

        printf("received: %d\n", data[1]);
        data[0] = data[1];
	}
	
	rpi_destruct(rpi);
	error_context_destruct(errcont);
	
	return 0;
}
