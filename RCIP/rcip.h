#ifndef RCIP_H
#define RCIP_H

/*	packet to low-level board	
 *	size: 2 bytes	*/
typedef struct rcip_instruction_packet
{
	signed char left_engine;
	signed char right_engine;
} rcip_instr_pack_t;



/*	packet from low-level board
 *	size: 2 bytes	*/
typedef struct rcip_data_packet
{
	unsigned char usrf_data;	//	one ultrasonic sensor
	unsigned char ir_data;		//	one infrared sensor		
} rcip_data_pack_t;


/*	this enumerator won't be used for awhile	*/
enum instruction
{
	BACK = 0b000,
	LEFT = 0b001,
	RIGHT = 0b010,
	FORWARD = 0b011,
	STOP = 0b111
};

/*	declare functions for packets wrapping and unwrapping	*/
int wrap_instr_packet(rcip_instr_pack_t**, int, int);
int unwrap_data_packet(rcip_data_pack_t**);


#endif
