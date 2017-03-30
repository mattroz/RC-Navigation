#ifndef RCCORE_H
#define RCCORE_H

#include <stdint.h>

/*	Raspberry Pi context declaration	*/
typedef struct RPiContext
{
	uint8_t version,
	char[512] i2c_path,
	char[512] pipe_path
} RPiContext;


/*	RoboCake low-level board context declaration (PC104)	*/
typedef struct PC104Context
{
	uint8_t version;
	char[512] i2c_slave_addr
} PC104Context;


#endif
