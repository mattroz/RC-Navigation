#ifndef RCIP_H
#define RCIP_H

/*	packet to low-level board	
 *	size: 2 bytes	*/
typedef struct rcip_instruction_packet
{
	unsigned char instr;
	signed char pow;
} rcip_instr_pack_t;

/*	packet from low-level board
 *	size: 8 bytes	*/
/*TODO need to find out how many sensors do we have onboard */
typedef struct rcip_data_packet
{
	unsigned char usrf_data[2];	//	two ultrasonic sensors
	unsigned char ir_data[2];	//	two infrared sensors		
} rcip_data_pack_t;


enum instruction
{
	BACK = 0b000,
	LEFT = 0b001,
	RIGHT = 0b010,
	FORWARD = 0b011,
	STOP = 0b111
};


#endif
