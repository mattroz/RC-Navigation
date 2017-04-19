all: obstac.out wlflw.c

obstac.out:	../SENSORS/rcsensors.c ../RCC/rccore.c ../I2C/rci2c.c ../RCIP/rcip.c
			gcc navmodule.c ../SENSORS/rcsensors.c ../RCC/rccore.c ../I2C/rci2c.c ../RCIP/rcip.c -g -o ./obstac.out -lwiringPi

wlflw.c:	../SENSORS/rcsensors.c ../RCC/rccore.c ../I2C/rci2c.c ../RCIP/rcip.c
			gcc wallfollowing.c ../SENSORS/rcsensors.c ../RCC/rccore.c ../I2C/rci2c.c ../RCIP/rcip.c -g -o ./wlflw.out -lwiringPi
