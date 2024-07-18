#pragma once

/* Standard library include */
#include "stdint.h"


/* Typedefs */
typedef uint8_t addr_t;
typedef uint8_t button_code_t;

/* Enum declarations */
enum msg_state
{
	MSG_UNKNOWN,
	MSG_ERROR,
	MSG_INCOMING,
	MSG_MERGING,
	MSG_READY
};

/* Structure declarations */
struct msg_frame
{
	addr_t addr;
	addr_t inv_addr;
	button_code_t cmd;
	button_code_t inv_cmd;
};

/* Function prototypes */
/* IR received interrupt handler */
void driver_ir_remote_IRQ(volatile struct msg_frame *msg_buffer);

/* Checking msg state function */
enum msg_state driver_ir_remote_check_msg_state(void);

/* Init function */
void driver_ir_remote_init(void);
