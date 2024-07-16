#pragma once

#include "stdint.h"


typedef uint8_t addr_t;
typedef uint8_t button_code_t;

enum msg_state
{
	MSG_UNKNOWN,
	MSG_ERROR,
	MSG_INCOMING,
	MSG_MERGING,
	MSG_READY
};

struct msg_frame
{
	addr_t addr;
	addr_t inv_addr;
	button_code_t cmd;
	button_code_t inv_cmd;
};


void driver_ir_remote_IRQ(volatile struct msg_frame *msg_buffer);

void driver_ir_remote_init(void);

enum msg_state driver_ir_remote_check_msg_state(void);


