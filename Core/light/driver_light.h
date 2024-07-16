#pragma once

#include <stdint.h>


typedef uint8_t light_set_t;

enum light_id
{
	LIGHT_FRONTRIGHT = 		0,
	LIGHT_FRONTLEFT = 		1,
	LIGHT_BACKRIGHT = 		3,
	LIGHT_BACKLEFT = 		2
};

/* Function that read set from lamp and sets the LEDs */
void driver_light_setlight(uint8_t set, enum light_id);

void driver_light_send_sets(void);

void driver_light_sending_complete(void);

void driver_light_init(void);

