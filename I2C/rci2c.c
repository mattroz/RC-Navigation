#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>

#include "rci2c.h"
#include "../RCC/rccore.h"
#include "../RCIP/rcip.h"


/*	access i2c bus and set PC104 as a slave	*/
int open_i2c(RPiContext *rpi, PC104Context *pc104)
{
	/*	check if contexts've been initialized	*/
	if(rpi == NULL || pc104 == NULL) return RC_EINIT;
	
	/*	try to access i2c bus	*/
	rpi->i2c_bus_descriptor = open(rpi->i2c_path, O_RDWR);
	pc104->i2c_bus_descriptor = rpi->i2c_bus_descriptor;

	if(rpi->i2c_bus_descriptor < 0) 
	{	
		rpi->last_error = RC_I2C_EOPEN;
		return RC_I2C_EOPEN;
	}
	/*	set slave address and establish i2c connection	*/
	int access_stat = ioctl(rpi->i2c_bus_descriptor, 
							I2C_SLAVE,
							pc104->i2c_slave_addr);
	if(access_stat < 0) 
	{	
		return RC_I2C_ESLAVE;
	}
	
	return RC_SUCCESS;
}


/*	Send values to PC104 board using i2c protocol	*/
int send_to_slave_via_i2c(RPiContext *rpi, int l_engine, int r_engine)
{
	/*	check if context is not NULL and i2c connection've been opened	*/
	if(rpi == NULL) return RC_EINIT;
	if(rpi->i2c_bus_descriptor < 0) 
	{
		return RC_I2C_EOPEN; 
	}

	/*	wrap given values for engines to instruction packet	*/	
	rcip_instr_pack_t *ipacket;
    int status =  wrap_instr_packet(&ipacket, l_engine, r_engine);
	if(status != RC_SUCCESS) 
	{
		return status;
	}

	/*	try to send wrapped packet	*/
	status = write(rpi->i2c_bus_descriptor, ipacket, sizeof *ipacket);
	if(status != sizeof *ipacket) 
	{
		return RC_I2C_EWRITE;
	}

	free(ipacket);
	return RC_SUCCESS;
}


/*	Receive data from Sharp IR sensor via i2c protocol	*/
int receive_from_slave_via_i2c(PC104Context *pc104)
{
	 /*  check if context is not NULL and i2c connection've been opened  */
    if(pc104 == NULL) 
	{
		return RC_EINIT;
    }

	if(pc104->i2c_bus_descriptor < 0) 
	{
		pc104->last_error = RC_I2C_EOPEN;
		return RC_I2C_EOPEN;
	}

	int length = 4;
    unsigned char *buffer = malloc(sizeof(unsigned char) * length);
	
	int status = read(pc104->i2c_bus_descriptor, buffer, length);
	if(status != length) 
	{
		pc104->last_error = RC_I2C_EREAD;
		return RC_I2C_EREAD;
	}

	pc104->distance_from_IR_sensor = atoi(buffer);
    
	return RC_SUCCESS;
}
