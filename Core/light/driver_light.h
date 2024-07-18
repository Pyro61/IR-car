#pragma once

/* Standard library include */
#include <stdint.h>

/* Typedefs */
typedef uint8_t light_set_t;

/* Enums */
enum light_id
{
	LIGHT_FRONTRIGHT = 		0,
	LIGHT_FRONTLEFT = 		1,
	LIGHT_BACKRIGHT = 		3,
	LIGHT_BACKLEFT = 		2
};

/* Function prototypes */
/* Reading set from lamps and sets the LEDs function */
void driver_light_setlight(uint8_t set, enum light_id);

/* Sending light codes function */
void driver_light_send_sets(void);

/* End of sending function */
void driver_light_sending_completed(void);

/* Init function */
void driver_light_init(void);

