all: stop.out wlflw.out maze.out

stop.out:	../SENSORS/rcsensors.c ../RCC/rccore.c ../I2C/rci2c.c ../RCIP/rcip.c
			gcc stop_if_obstacle.c ../SENSORS/rcsensors.c ../RCC/rccore.c ../I2C/rci2c.c ../RCIP/rcip.c -g -o ./stop.out -lwiringPi

wlflw.out:	../SENSORS/rcsensors.c ../RCC/rccore.c ../I2C/rci2c.c ../RCIP/rcip.c
			gcc wallfollowing.c ../SENSORS/rcsensors.c ../RCC/rccore.c ../I2C/rci2c.c ../RCIP/rcip.c -g -o ./wlflw.out -lwiringPi

maze.out:	../SENSORS/rcsensors.c ../RCC/rccore.c ../I2C/rci2c.c ../RCIP/rcip.c
			gcc maze_passing.c ../SENSORS/rcsensors.c ../RCC/rccore.c ../I2C/rci2c.c ../RCIP/rcip.c -g -o ./maze.out -lwiringPi
