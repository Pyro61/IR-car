#include <ir_remote/driver_ir_remote.h>
#include <ir_remote/ir_remote.h>


static volatile struct msg_frame ir_remote_msg;


void ir_remote_IRQ(void)
{
	driver_ir_remote_IRQ(&ir_remote_msg);
}


button_code_t ir_remote_read_button(void)
{
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


void ir_remote_init(void)
{
	driver_ir_remote_init();
}
