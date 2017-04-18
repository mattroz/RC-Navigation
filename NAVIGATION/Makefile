all: nav.out

nav.out:	../SENSORS/rcsensors.c ../RCC/rccore.c ../I2C/rci2c.c ../RCIP/rcip.c
			gcc navmodule.c ../SENSORS/rcsensors.c ../RCC/rccore.c ../I2C/rci2c.c ../RCIP/rcip.c -g -o ./nav.out -lwiringPi

