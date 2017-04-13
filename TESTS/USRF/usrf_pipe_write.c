#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../../SENSORS/rcsensors.h"
#include "../../FIFO/rcpipe.h"
#include "../../RCC/rccore.h"

int main()
{
	RPiContext *rpi;
	rpi_init(&rpi);

	/*	setup block	*/
	setup_usrf();
	if(create_pipe(rpi) != RC_SUCCESS)
	{
		perror("Failed to create pipe");
		exit(EXIT_FAILURE);
	}

	/*	write values of ultrasonic rangefinder in cantimeteres to pipe	*/
	int distance;
	while(1)
	{
		distance = get_distance_in_cm();
		if(write_value_to_pipe(rpi, distance) == EXIT_FAILURE)
        {
            perror("Failed to write value to pipe\n");
            exit(EXIT_FAILURE);
        }
        usleep(10000);
	}

}
