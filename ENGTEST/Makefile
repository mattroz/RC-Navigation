all:	testutil.out

testutil.out:	../RCC/rccore.c ../I2C/rci2c.c ../RCIP/rcip.c
				gcc -Wno-unused-function test_utility.c ../RCC/rccore.c ../I2C/rci2c.c ../RCIP/rcip.c -g -o ./testutil.out

