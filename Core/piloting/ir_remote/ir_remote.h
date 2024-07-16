#pragma once

#include "stdint.h"


#define MSG_NOT_READY		0XFF
#define MSG_INVALID_ADDR	0xFE

#define REMOTE_ADDR			0

typedef uint8_t button_code_t;

void ir_remote_IRQ(void);

button_code_t ir_remote_read_button(void);

void ir_remote_init(void);
