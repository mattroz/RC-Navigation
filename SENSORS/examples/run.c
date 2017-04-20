#include <stdio.h>
#include <stdlib.h>

#include "../rcsensors.h"
#include "../../FIFO/rcpipe.h"
#include "../../RCC/rccore.h"

int main()
{
	/*	setup block	*/
	setup_usrf();

	RPiContext *rpi;
	RCErrorContext *errcontext = malloc(sizeof(RCErrorContext));
	rpi_init(&rpi);
		
	int data[2];
	/*	data translation to output (potentionally, PIPE)	*/
	while(1)
	{
		if(get_distance_USRF(rpi) == RC_EINIT)
		{
			rcerror(errcontext, rpi, RC_EXIT);
		}
     
		data[1] = rpi->distance_from_USRF_sensor;
		data[1] = (data[1] > USRF_MAX_VAL_CM) ? data[0] : data[1];

        printf("received: %d\n", data[1]);
        data[0] = data[1];
	}
}
