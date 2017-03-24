#include <stdio.h>
#include <stdlib.h>

#include "../rcip.h"

int main()
{

	rcip_instr_pack_t *ipacket = malloc(sizeof(rcip_instr_pack_t));
	rcip_data_pack_t *dpacket = malloc(sizeof(rcip_data_pack_t));

	/*	wrap -22 and 20	*/
	if(wrap_instr_packet(&ipacket, 0b11101010, 0b00010100) != 0)
	{
		perror("Failed to wrap an instruction packet\n");
		exit(EXIT_FAILURE);	
	}

	/*	
	if(unwrap_data_packet(&dpacket) != 0)
	{
		perror("Failed to unwrap a data packet\n");
		exit(EXIT_FAILURE);
	}
	
	ipacket->instr = FORWARD;
	ipacket->pow = 0b11010011;
	*/
	dpacket->usrf_data = 10;
	dpacket->ir_data = 42; 
	
	printf("instruction packet: %d | %d\n", ipacket->left_engine, ipacket->right_engine);
	printf("data packet: %d | %d\n", dpacket->usrf_data, dpacket->ir_data);

	free(ipacket);
	free(dpacket);

	return 0;
}
