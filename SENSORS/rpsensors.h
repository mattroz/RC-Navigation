#ifndef RPSENSORS_H
#define RPSENSORS_H

#include <stdint.h>

#ifndef USRF_MAX_VAL_CM
#	define USRF_MAX_VAL_CM 300
#else
#	error "Multiple definitions, should be defined once"
#endif

/*	HC-SR04 ultrasonic rangefinder variables declarations	*/
const uint8_t PIN_USRF_TRIG;
const uint8_t PIN_USRF_ECHO;

/*	HC-SR04 functions declarations	*/
void setup_usrf();
int get_distance_in_cm();


#endif
