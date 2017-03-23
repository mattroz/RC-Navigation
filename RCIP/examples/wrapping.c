#include <stdio.h>
#include <stdlib.h>

#include "../rcip.h"

int main()
{

	rcip_pack_t *packet = malloc(sizeof(rcip_pack_t));
	
	packet->instr = FORWARD;
	packet->pow = 0b11010011;
	
	printf("%d | %d\n", packet->instr, packet->pow);

	return 0;
}
