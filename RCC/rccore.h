#ifndef RCCORE_H
#define RCCORE_H

#include <stdint.h>

#ifndef RASPBERRY
#	define _RASPBERRY_ "raspberry"
#else
#	error "Multiple definitions detected, should be defined once"
#endif

#ifndef _PC104_
#   define _PC104_ "pc104"
#else
#   error "Multiple definitions detected, should be defined once"
#endif

#ifndef RPI_VERSION
#	define RPI_VERSION 3
#else
#	error "Multiple definitions detected, should be defined once"
#endif

#ifndef PC104_VERSION
#	define PC104_VERSION 1
#else 
#	error "Multiple definitions detected, should be defined once"
#endif

/*	define default settings	*/
#ifndef DEFAULT_I2C_PATH
#	define DEFAULT_I2C_PATH "/dev/i2c-1"
#else
#	error "Multiple definitions detected, should be defined once"
#endif

#ifndef DEFAULT_PIPE_PATH
#	define DEFAULT_PIPE_PATH "/var/run/raspi_pipe"
#else
#	error "Multiple definitions detected, should be defined once"
#endif

#ifndef DEFAULT_PC104_I2C_SLAVE_ADDR
#	define DEFAULT_PC104_I2C_SLAVE_ADDR 0x02
#else
#   error "Multiple definitions detected, should be defined once"
#endif

/*	Raspberry Pi context declaration	*/
typedef struct RPiContext
{
	uint8_t version;
	char *identifier;
	char *i2c_path;
	char *pipe_path;
	uint8_t last_error;
	
} RPiContext;


/*	RoboCake low-level board context declaration (PC104)	*/
typedef struct PC104Context
{
	uint8_t version;
	char *identifier;
	uint16_t i2c_slave_addr;
	uint8_t last_error;
} PC104Context;


/*	contexts initializers and destructors declaration	*/
int rpi_init(RPiContext**);
void rpi_destruct(RPiContext*);
int pc104_init(PC104Context**);
void pc104_destruct(PC104Context*);


/*	TODO structures and functions for error handling	*/
void rc_err_handle(void*);


#endif
