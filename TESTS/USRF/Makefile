all: 	read.out write.out

read.out:	usrf_pipe_read.c ../../FIFO/rcpipe.c ../../SENSORS/rcsensors.c ../../RCC/rccore.h
		gcc usrf_pipe_read.c ../../FIFO/rcpipe.c ../../SENSORS/rcsensors.c  ../../RCC/rccore.c -g -o ./read -lwiringPi

write.out:	usrf_pipe_write.c ../../FIFO/rcpipe.c ../../SENSORS/rcsensors.c ../../RCC/rccore.c
		gcc usrf_pipe_write.c ../../FIFO/rcpipe.c ../../SENSORS/rcsensors.c ../../RCC/rccore.c -g -o ./write -lwiringPi

		
