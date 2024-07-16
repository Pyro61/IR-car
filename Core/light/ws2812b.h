#pragma once

#include <stdint.h>
#include <stdbool.h>


#define LIGHTS_AMOUNT	4
#define LEDS_IN_LIGHT	7

/* Check whether the transmission is in progress */
bool ws2812b_is_transmit_possible(void);

/* Coding the RGB code to the right LED function */
void ws2812b_code(uint8_t r, uint8_t g, uint8_t b, uint8_t light, uint8_t led);

/* Sending the RGB codes to LEDs function */
void ws2812b_send(void);

/* End of transmit function */
void ws2812b_end_of_transmit(void);

/* Initializing the lamps with blank color function */
void ws2812b_init(void);






