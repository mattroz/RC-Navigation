all: 	read write

read:	usrf_pipe_read.c ../FIFO/rppipe.c ../SENSORS/rpsensors.c
		gcc -Wall usrf_pipe_read.c ../FIFO/rppipe.c ../SENSORS/rpsensors.c -g -o ./read -lwiringPi

write:	usrf_pipe_write.c ../FIFO/rppipe.c ../SENSORS/rpsensors.c
		gcc -Wall usrf_pipe_write.c ../FIFO/rppipe.c ../SENSORS/rpsensors.c -g -o ./write -lwiringPi

		
