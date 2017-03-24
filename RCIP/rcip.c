#include <stdlib.h>
#include <unistd.h>

#include "rcip.h"

/*	Define instruction packet wrapping. 
 *	Since we only need to wrap instruction packets,
 *	there is no need to write the same function for data packets	*/
int wrap_instr_packet(rcip_instr_pack_t **packet, int _instr, int _pow)
{
	/*	allocate memory for a packet and handle allocation error	*/
	*(packet) = malloc(sizeof(rcip_instr_pack_t));
	if(*(packet) == NULL)
	{
		return -1;		
	}
	
	*(packet)->instr = _instr;
	*(packet)->pow = _pow;	
	
	return 0;
}


int unwrap_data_packet()
{

}
