/* Module header include */
#include <ir_remote/driver_ir_remote.h>

/* Board hardware include */
#include "tim.h"

/* Standard library include */
#include "stdbool.h"

/* Defines */
#define MSG_SIZE				32

#define ADDR_MASK				0
#define INV_ADDR_MASK			8
#define CMD_MASK				16
#define INV_CMD_MASK			24

#define ADDR_ERROR				0xFF
#define CMD_ERROR				0xFE

#define WRITE_ONE_HIGHEST_BIT	0x80000000

/* Typedefs */
typedef uint32_t time_us_t;

/* Enum declarations */
enum pulse
{
	PULSE_NONE,
	PULSE_0,
	PULSE_1,
	PULSE_START,
	PULSE_REPEAT
};

/* Vatiables */
volatile static uint32_t received_msg;
static uint8_t received_bits;

static enum msg_state msg_state_flag = MSG_UNKNOWN;

/* Must be not static, changed to true in piloting module */
bool is_cmd_executed = false;

/* Static function definitions */
/* Calculating received from ir received pulse function */
static enum pulse calc_pulse(time_us_t time)
{
	if (time < 250)
	{
		return PULSE_NONE;
	}

	else if (time < 1200)
	{
		return PULSE_0;
	}

	else if (time < 2000)
	{
		return PULSE_1;
	}

	else if (time < 3000)
	{
		return PULSE_REPEAT;
	}

	else if (time < 6000)
	{
		return PULSE_START;
	}

	else
	{
		return PULSE_NONE;
	}
}


/* Checking received data correctness functions */
static bool check_addr_correctness(addr_t addr, addr_t inv_addr)
{
	if (addr != ((~inv_addr) & 0xFF))
	{
		msg_state_flag = MSG_ERROR;

		return false;
	}

	return true;
}


static bool check_cmd_correctness(addr_t cmd, addr_t inv_cmd)
{
	if (cmd != ((~inv_cmd) & 0xFF))
	{
		msg_state_flag = MSG_ERROR;

		return false;
	}

	return true;
}


/* Merging received message function */
static void merge_msg(volatile struct msg_frame *msg_buffer)
{
	msg_state_flag = MSG_MERGING;

	addr_t tmp_addr = (received_msg >> ADDR_MASK) & 0xFF;
	addr_t tmp_inv_addr = (received_msg >> INV_ADDR_MASK) & 0xFF;
	button_code_t tmp_cmd = (received_msg >> CMD_MASK) & 0xFF;
	button_code_t tmp_inv_cmd = (received_msg >> INV_CMD_MASK) & 0xFF;

	if (true != check_addr_correctness(tmp_addr, tmp_inv_addr))
	{
		return;
	}

	if (true != check_cmd_correctness(tmp_addr, tmp_inv_addr))
	{
		return;
	}

	msg_buffer -> addr = tmp_addr;
	msg_buffer -> inv_addr = tmp_inv_addr;
	msg_buffer -> cmd = tmp_cmd;
	msg_buffer -> inv_cmd = tmp_inv_cmd;

	msg_state_flag = MSG_READY;
	is_cmd_executed = false;
}


/* Function definitions */
/* Received pulse from ir received interrupt handler */
void driver_ir_remote_IRQ(volatile struct msg_frame *msg_buffer)
{
	enum pulse received_pulse = calc_pulse(HAL_TIM_ReadCapturedValue(&htim15, TIM_CHANNEL_1));

	if(PULSE_START == received_pulse)
	{
		msg_state_flag = MSG_INCOMING;
		received_msg = 0;
		received_bits = 0;
		return;
	}

	if (MSG_INCOMING != msg_state_flag)
	{
		return;
	}

	/* All message bits are received */
	if (received_bits >= MSG_SIZE)
	{
		merge_msg(msg_buffer);
		return;
	}

	switch (received_pulse)
	{
		case PULSE_0:
		{
			received_msg >>= 1;
			received_bits++;
			break;
		}

		case PULSE_1:
		{
			received_msg = (received_msg >> 1) | WRITE_ONE_HIGHEST_BIT;
			received_bits++;
			break;
		}

		case PULSE_REPEAT:
		{
			if (0 == received_bits)
			{
				received_bits = MSG_SIZE;
			}
			break;
		}

		case PULSE_NONE:
		default:
		{
			received_bits = 0;
			break;
		}
	}
}


/* Checking msg_state function */
enum msg_state driver_ir_remote_check_msg_state(void)
{
	return msg_state_flag;
}


/* Init function */
void driver_ir_remote_init(void)
{
	HAL_TIM_Base_Start(&htim15);
	HAL_TIM_IC_Start_IT(&htim15, TIM_CHANNEL_1);
}

