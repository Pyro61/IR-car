#pragma once

/* Standard library includes */
#include <stdint.h>
#include <stdbool.h>

/* Defines */
#define LIGHTS_AMOUNT	4
#define LEDS_IN_LIGHT	7

/* Function prototypes */
/* Check whether the transmission is in progress function */
bool ws2812b_is_transmit_possible(void);

/* Coding the RGB code to the correct LED function */
void ws2812b_code(uint8_t r, uint8_t g, uint8_t b, uint8_t light, uint8_t led);

/* Sending the RGB codes to LEDs function */
void ws2812b_send(void);

/* End of RGB codes transmit function */
void ws2812b_end_of_transmit(void);

/* Init function */
void ws2812b_init(void);






