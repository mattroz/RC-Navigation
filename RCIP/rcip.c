#include <stdlib.h>
#include <unistd.h>

#include "rcip.h"
#include "../RCC/rccore.h"

/*	Define instruction packet wrapping. 
 *	Since we only need to wrap instruction packets,
 *	there is no need to write the same function for data packets	*/
int wrap_instr_packet(rcip_instr_pack_t **packet, int leftval, int rightval)
{
	/*	handle packet allocation error	*/
	if(*packet == NULL)
	{
		return RC_EALLOC;		
	}

	(*packet)->left_engine = leftval;
	(*packet)->right_engine = rightval;	
	
	return RC_SUCCESS;
}

/*	TODO add to this function's declaration two chars for parsing them/
int unwrap_data_packet(rcip_data_pack_t **packet)
{
	
}
*/
