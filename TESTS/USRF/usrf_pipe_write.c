#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../SENSORS/rpsensors.h"
#include "../FIFO/rppipe.h"

int main()
{
	/*	setup block	*/
	setup_usrf();
	if(create_pipe() != EXIT_SUCCESS)
	{
		perror("Failed to create pipe");
		exit(EXIT_FAILURE);
	}

	/*	write values of ultrasonic rangefinder in cantimeteres to pipe	*/
	int distance;
	while(1)
	{
		distance = get_distance_in_cm();
		if(write_value_to_pipe(distance) == EXIT_FAILURE)
        {
            perror("Failed to write value to pipe\n");
            exit(EXIT_FAILURE);
        }
        usleep(10000);
	}

}
