#include <stdio.h>
#include <stdlib.h>
#include "../rpsensors.h"


int main()
{
	/*	setup block	*/
	setup_usrf();

	/*	data translation to output (potentionally, PIPE)	*/
	while(1)
	{
		int distance = get_distance_in_cm();
		printf("%d cm\n", distance);
	}
}
