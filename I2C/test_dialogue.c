#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>			
#include <fcntl.h>				
#include <sys/ioctl.h>			
#include <linux/i2c-dev.h>		

#include "../RCIP/rcip.h"

static const char *filename = "/dev/i2c-1";

int main(int argc, char **argv)
{
	int file_i2c;
	int length = 4;
	int res;
	unsigned char *buffer = malloc(sizeof(unsigned char) * length);
	rcip_instr_pack_t *ipacket;

	if ((file_i2c = open(filename, O_RDWR)) < 0)
	{
		printf("Failed to open the i2c bus");
		exit(EXIT_FAILURE);
	}
	
	int slave_addr = 0x02;
	if (ioctl(file_i2c, I2C_SLAVE, slave_addr) < 0)
	{
		printf("Failed to access a slave.\n");
		exit(EXIT_FAILURE);
	}

	if(argv[1][0] == 'r')
	{
		//	READ BYTES	
		while(read(file_i2c, buffer, length) == length)
		{
	    	unsigned long numerical_part = atoi(buffer);
			printf("Data read: %lu\n", numerical_part);
		}
		printf("Failed to read data from i2c\n.");
		exit(EXIT_FAILURE);
	}
	else if(argv[1][0] == 'w')	
	{
		//	WRITE BYTES
		wrap_instr_packet(&ipacket, atoi(argv[2]), atoi(argv[3]));	
		if(write(file_i2c, ipacket, sizeof *ipacket) != sizeof *ipacket)
		{
			printf("Failed to write data to i2c\n");
			exit(EXIT_FAILURE);
		} 	
		printf("%d\n", *ipacket);
	}

	return 0;

