#include <stdio.h>
#include <stdlib.h>

#include "../rccore.h"

int main()
{
	RPiContext *rpi;
	PC104Context *pc104;
	
	if(rpi_init(&rpi) == -1)
	{
		perror("Failed to initialize Raspberry Pi context");
		exit(EXIT_FAILURE);
	}
	
	if(pc104_init(&pc104) == -1)
	{
		perror("Failed to initialize PC104 context");
		exit(EXIT_FAILURE);
	}
	
	puts("\nInitialization successed");
	printf("\tRPi version: %d\n\tRPi I2C: %s\n\tRPi pipe: %s\n", rpi->version, rpi->i2c_path, rpi->pipe_path);
	printf("\n\tPC104 version: %d\n\tPC104 i2c addr: 0x%X\n", pc104->version, pc104->i2c_slave_addr);

	rpi_destruct(rpi);
	pc104_destruct(pc104);

	return 0;
}
