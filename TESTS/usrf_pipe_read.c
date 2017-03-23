#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <linux/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>

#include "../FIFO/rppipe.h"
#include "../SENSORS/rpsensors.h"

int main(void)
{
    if(create_pipe() != EXIT_SUCCESS)
    {
        perror("Failed to create pipe");
        exit(EXIT_FAILURE);
    }

	int data[2];
    
	/*	receive data with the outliers filtration	*/
	while(1)
    {
		data[1] = read_value_from_pipe();
		data[1] = (data[1] > USRF_MAX_VAL_CM) ? data[0] : data[1];	

        printf("received: %d\n", data[1]);
    	data[0] = data[1];
	}

    return 0;
}
