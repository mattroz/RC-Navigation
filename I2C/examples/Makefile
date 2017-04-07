all:	receive.out send.out

receive.out:	../../RCIP/rcip.c ../../RCC/rccore.c ../rci2c.c
				gcc receive_data_from_i2c.c ../../RCIP/rcip.c ../../RCC/rccore.c ../rci2c.c -g -o ./receive.out

send.out:		../../RCIP/rcip.c ../../RCC/rccore.c ../rci2c.c
				gcc send_instr_packet.c ../../RCIP/rcip.c ../../RCC/rccore.c ../rci2c.c -g -o ./send.out
