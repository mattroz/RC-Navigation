#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

#include "../RCC/rccore.h"
#include "../RCIP/rcip.h"

int main()
{
	RPiContext *RPi;
	PC104Context *PC104;

	/*	initialize contexts	*/
	if(rpi_init(&RPi) == -1)
	{
		perror("Failed to initialize Raspberry Pi context");
		exit(EXIT_FAILURE);
	}
	
	if(pc104_init(&PC104) == -1)
	{
		perror("Failed to initialize PC104 context");
		exit(EXIT_FAILURE);
	}
	
	/*	open I2C connection	*/	
	int file_i2c;
	if ((file_i2c = open(RPi->i2c_path, O_RDWR)) < 0)
    {
        perror("Failed to open the i2c bus");
        exit(EXIT_FAILURE);
    }

    if (ioctl(file_i2c, I2C_SLAVE, PC104->i2c_slave_addr) < 0)
    {
        perror("Failed to access a slave");
        exit(EXIT_FAILURE);
    }
	
	/*	wrap instruction packet and send it via I2C	*/
	rcip_instr_pack_t *ipacket;
	wrap_instr_packet(&ipacket, 30, 30);
	if(write(file_i2c, ipacket, sizeof *ipacket) != sizeof *ipacket)
	{
		perror("Failed to write data to i2c");
		exit(EXIT_FAILURE);
	}
	printf("%d %d\n", ipacket->left_engine, ipacket->right_engine);

	close(file_i2c);
		
	return 0;
}
