#ifndef RCCORE_H
#define RCCORE_H

#include <stdint.h>

#ifndef RASPBERRY
#	define _RASPBERRY_ "RASPBERRY"
#else
#	error "Multiple definitions detected, should be defined once"
#endif

#ifndef _PC104_
#   define _PC104_ "PC104"
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

#ifndef RC_EXIT
#   define RC_EXIT 1
#else
#   error "Multiple definitions detected, should be defined once"
#endif

#ifndef RC_CONT
#   define RC_CONT 0
#else
#   error "Multiple definitions detected, should be defined once"
#endif



/*	Raspberry Pi context declaration	*/
typedef struct RPiContext
{
	uint8_t version;
	char *identifier;
	uint16_t distance_from_USRF_sensor;
	char *i2c_path;
	int i2c_bus_descriptor;
	char *pipe_path;
	uint8_t last_error;	
} RPiContext;


/*	RoboCake low-level board context declaration (PC104)	*/
typedef struct PC104Context
{
	uint8_t version;
	char *identifier;
	uint16_t i2c_slave_addr;
	int i2c_bus_descriptor;
	uint16_t distance_from_IR_sensor;
	uint8_t last_error;
} PC104Context;


/*	Global RoboCake error context.	*/
/*	Contains the last library error, including identifier of the
	context which caused an error.	*/
typedef struct RCErrorContext
{
	int last_error_code;
	char *last_error_message;	
	char *culprit_context;	
} RCErrorContext;


/*	RoboCake global error enumerator 	*/
typedef enum RCErrorCode
{
	RC_SUCCESS,		/*	return on success	*/
	RC_EINIT,		/*	initialization error	*/
	RC_EALLOC,		/*	memory allocation error	*/
	RC_PIPE_ECREATE,	/*	pipe creating error	*/		
	RC_PIPE_EREAD,		/*	error reading value from pipe	*/
	RC_PIPE_EWRITE,		/*	error writing value to pipe	*/		
	RC_I2C_EOPEN,	/*	error opening i2c connection	*/
	RC_I2C_EWRITE,	/*	error writing to slave via i2c	*/
	RC_I2C_EREAD,	/*	error reading value from i2c	*/
	RC_I2C_ESLAVE	/*	slave detection error	*/	
} rc_errcode_t;


/*	RoboCake error messages	*/
static char *RCErrorMessage[] = {
	"Initialization succeed",		/*	RC_SUCCESS	*/
	"Initialization failed",		/*	RC_EINIT	*/
	"Failed to allocate memory",		/*	RC_EALLOC	*/
	"Failed creating pipe",			/*	RC_PIPE_ECREATE	*/
	"Failed reading value from pipe",	/*	RC_PIPE_EREAD	*/
	"Failed writing value to pipe",		/*	RC_PIPE_EWRITE	*/
	"Failed to access the i2c bus ",	/*	RC_I2C_EOPEN	*/
	"Failed to send data via i2c",	/*	RC_I2C_EWRITE	*/
	"Failed to receive data via i2c",	/*	RC_I2C_EREAD	*/
	"Failed to access an i2c slave"	/*	RC_I2C_ESLAVE	*/
};

/*	contexts initializers and destructors declaration	*/
int rpi_init(RPiContext**);
void rpi_destruct(RPiContext*);
int pc104_init(PC104Context**);
void pc104_destruct(PC104Context*);


/*	TODO structures and functions for error handling	*/
void rcerror(RCErrorContext*, void*, int, int);


#endif
