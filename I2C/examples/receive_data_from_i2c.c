#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

#include "../../RCC/rccore.h"
#include "../../RCIP/rcip.h"

int main()
{
    RPiContext *RPi;
    PC104Context *PC104;

    /*  initialize contexts */
    if(rpi_init(&RPi) == RC_EINIT)
    {
		rcerror(RC_EINIT);
    }

    if(pc104_init(&PC104) == RC_EINIT)
    {
		rcerror(RC_EINIT);
    }

    /*  open I2C connection */
    int file_i2c;
    if ((file_i2c = open(RPi->i2c_path, O_RDWR)) < 0)
    {
        perror("Failed to open the i2c bus");
        exit(EXIT_FAILURE);
    }

    if (ioctl(file_i2c, I2C_SLAVE, PC104->i2c_slave_addr) < 0)
    {
        perror("Failed to access an i2c slave");
        exit(EXIT_FAILURE);
    }

	/*	receive data from I2C	*/
	int length = 4;
	unsigned char *buffer = malloc(sizeof(unsigned char) * length);
	while(1)
	{
		if(read(file_i2c, buffer, length) != length)
		{
			perror("Failed to read from i2c");
			exit(EXIT_FAILURE);
		}	
		unsigned long numerical_part = atoi(buffer);
		printf("Data read: %lu\n", numerical_part);
	}
	
	close(file_i2c);

    return 0;
}
