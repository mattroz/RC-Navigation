#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <wiringPi.h>

#include "rcsensors.h"
#include "../RCC/rccore.h"

#ifndef USRF_COEFF
#	define USRF_COEFF 58
#endif

/*	pins numeration according to WiringPi pinout, 
 *	see pinout.xyz web site	*/
const uint8_t PIN_USRF_TRIG = 5;
const uint8_t PIN_USRF_ECHO = 4;

void setup_usrf()
{
	/*	setup ultrasonic pins	*/
	wiringPiSetup();
	pinMode(PIN_USRF_TRIG, OUTPUT);
	pinMode(PIN_USRF_ECHO, INPUT);

	/*	start trigger pin with LOW value	*/
	digitalWrite(PIN_USRF_TRIG, LOW);
	delay(30);
}

/*	Get distance from ultrasonic rangefinder 
 *	which is located on RPi board	*/
int get_distance_USRF(RPiContext *rpi)
{
	if(rpi == NULL)
	{
		return RC_EINIT;
	}

	/*	send pulse to trig pin	*/
	digitalWrite(PIN_USRF_TRIG, HIGH);
	delayMicroseconds(20);
	digitalWrite(PIN_USRF_TRIG, LOW);

	/*	start echo	*/
	while(digitalRead(PIN_USRF_ECHO) == LOW)
		;

	/*	end echo	*/
	long startTime = micros();
	while(digitalRead(PIN_USRF_ECHO) == HIGH)
		;
	long travelTime = micros() - startTime;

	/*	convert distance in cm	*/
	int distance = travelTime / USRF_COEFF;
	rpi->distance_from_USRF_sensor = distance;

	return RC_SUCCESS;
}
