#ifndef RCI2C_H
#define RCI2C_H

#include "../RCC/rccore.h"

/*	Open i2c connection between master (arg1) and slave (arg2). 
 *	Since Raspberry Pi can communicate via i2c only as a master,	
 *	we throw RPiContext as a first arg, and PC104Context as a second one.
 *	Returns: 
 *  -- RC_EINIT, if RPi and PC104 contexts hadn't been initialized;	
 *	-- RC_I2C_EOPEN, if failed to get an access to i2c device file;
 *	-- RC_I2C_ESLAVE, if failed to establish connection with PC104 as a slave;
 *	-- RC_SUCCESS on successfull i2c acces configuring.	*/
int open_i2c(RPiContext*, PC104Context*);

/*	Send values from Raspberry Pi to PC104 engines via i2c for navigation.
 *	arg1 and arg2 are the values passing to the left and right engines 
 *	respectively.
 *	Returns:
 *	-- RC_EINIT, if RPi context hadn't been initialized; 
 *	-- RC_I2C_EOPEN, if failed to get an access to i2c device file;
 *	-- status of packet wrapping, see wrap_instr_packet() at RCIP/rcip.h;
 *	-- RC_I2C_EWRITE if failed to send a packet to PC104 via i2c;
 *	-- RC_SUCCESS on successfull i2c access configuring.	*/
int send_to_slave_via_i2c(RPiContext*, int, int);

/*	Receive data from Sharp IR which is on the PC104 board	
 *	Returns:
 *	-- RC_EINIT, if PC104 context hadn't been initialized; 
 *	-- RC_I2C_EOPEN, if failed to get an access to i2c device file;
 *	-- RC_EALLOC, if failed to allocate memory for data buffer;
 *	-- RC_I2C_EREAD if failed to receive data from PC104 board via i2c;
 *	-- RC_SUCCESS on successfull i2c access configuring.    */
int receive_from_slave_via_i2c(PC104Context*);


#endif
