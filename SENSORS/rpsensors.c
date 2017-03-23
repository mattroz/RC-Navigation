#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <wiringPi.h>

#include "rpsensors.h"

#define COEFF 58

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


int get_distance_in_cm() 
{
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
	int distance = travelTime / COEFF;

	return distance;
}
