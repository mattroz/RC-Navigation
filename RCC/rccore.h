#ifndef RCCORE_H
#define RCCORE_H

#include <stdint.h>

#define RPI_VERSION 3
#define PC104_VERSION 1

/*	define default settings	*/
#define DEFAULT_I2C_PATH "/dev/i2c-1"
#define DEFAULT_PIPE_PATH "/var/run/raspi_pipe"
#define DEFAULT_PC104_I2C_SLAVE_ADDR 0x02

/*	Raspberry Pi context declaration	*/
typedef struct RPiContext
{
	uint8_t version;
	char *i2c_path;
	char *pipe_path;
} RPiContext;


/*	RoboCake low-level board context declaration (PC104)	*/
typedef struct PC104Context
{
	uint8_t version;
	uint16_t i2c_slave_addr;
} PC104Context;


/*	contexts initializers and destructors declaration	*/
int rpi_init(RPiContext**);
void rpi_destruct(RPiContext*);
int pc104_init(PC104Context**);
void pc104_destruct(PC104Context*);

#endif
