#pragma once

/* Standard library include */
#include "stdint.h"

/* Defines */
#define MSG_NOT_READY		0XFF
#define MSG_INVALID_ADDR	0xFE

#define REMOTE_ADDR			0

/* Typedefs */
typedef uint8_t button_code_t;

/* Function prototypes */
/* IR receiver interrupt handler */
void ir_remote_IRQ(void);

/* Reading what button was pressed function */
button_code_t ir_remote_read_button(void);

/* Init function */
void ir_remote_init(void);
