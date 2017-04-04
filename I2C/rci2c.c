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
int receive_from_slave_via_i2c()
{

}
