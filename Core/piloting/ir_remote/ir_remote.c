/* Module include */
#include <ir_remote/ir_remote.h>

/* Driver include */
#include <ir_remote/driver_ir_remote.h>

/* Variables */
static volatile struct msg_frame ir_remote_msg;


/* Function definitions */
/* IR remote message bit received interrupt handler */
void ir_remote_IRQ(void)
{
	driver_ir_remote_IRQ(&ir_remote_msg);
}


/* Reading what remote button was pressed function */
button_code_t ir_remote_read_button(void)
{
	/* Check if msg was received from the correct remote */
	if (REMOTE_ADDR != ir_remote_msg.addr)
	{
		return MSG_INVALID_ADDR;
	}

	if (MSG_READY == driver_ir_remote_check_msg_state())
	{
		return ir_remote_msg.cmd;
	}

	else
	{
		return MSG_NOT_READY;
	}
}


/* Init function */
void ir_remote_init(void)
{
	driver_ir_remote_init();
}
