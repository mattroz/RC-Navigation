all:	receive.out send.out

receive.out:	../RCIP/rcip.c ../RCC/rccore.c
				gcc receive_data_from_i2c.c ../RCIP/rcip.c ../RCC/rccore.c -g -o ./receive.out

send.out:		../RCIP/rcip.c ../RCC/rccore.c
				gcc send_instr_packet.c ../RCIP/rcip.c ../RCC/rccore.c -g -o ./send.out
