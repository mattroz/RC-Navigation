#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <unistd.h>

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
		rpi->last_error = RC_I2C_ESLAVE;	
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
		rpi->last_error = RC_I2C_EOPEN;
		return RC_I2C_EOPEN; 
	}

	/*	wrap given values for engines to instruction packet	*/	
	rcip_instr_pack_t *ipacket = malloc(sizeof(rcip_instr_pack_t));
	int status =  wrap_instr_packet(&ipacket, l_engine, r_engine);
	if(status != RC_SUCCESS) 
	{
		rpi->last_error = status;
		free(ipacket);
		return status;
	}

	/*	try to send wrapped packet	*/
	status = write(rpi->i2c_bus_descriptor, ipacket, sizeof(rcip_instr_pack_t));
	if(status != sizeof(rcip_instr_pack_t)) 
	{
		rpi->last_error = RC_I2C_EWRITE;
		free(ipacket);
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

	/*	receive 3 bytes: high and low for voltage 
	 *	and 1 byte for distance from IR sensor	*/
	unsigned char raw_data[3];

	int status = read(pc104->i2c_bus_descriptor, raw_data, 3);
	if(status != 3)
	{
		pc104->last_error = RC_I2C_EREAD;
		return RC_I2C_EREAD;
	}
	
	//printf("%u %u\n", (uint8_t)raw_data[0], (uint8_t)raw_data[1]);

	/*	bit twiddling for getting voltage value	*/	
	pc104->battery_voltage_mV = (uint16_t)((raw_data[0] << 8) 
								| raw_data[1]);
	pc104->distance_from_IR_sensor = raw_data[2];

	return RC_SUCCESS;
}
