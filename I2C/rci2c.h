#ifndef RCI2C_H
#define RCI2C_H

#include "../RCC/rccore.h"

/*	Open i2c connection between master (arg1) and slave (arg2). */
/*	Since Raspberry Pi can communicate via i2c only as a master,	*/
/*	we throw RPiContext as a first arg, and PC104Context as a second one	*/
int open_i2c(RPiContext*, PC104Context*);

/*	Send values from Raspberry Pi to PC104 engines via i2c for navigation.	*/
/*	arg1 and arg2 are the values passing to the left and right engines 
	respectively	*/
int send_to_slave_via_i2c(int, int);

/*	TODO Receive data from Sharp which is on the PC104 board	*/
int receive_from_slave_via_i2c();


#endif
