#include "piloting.h"
#include "ir_remote/ir_remote.h"
#include "ir_remote/ir_remote_buttons_codes.h"
#include "setter.h"
#include "safe_state.h"
#include <stdbool.h>
#include "gpio.h"

#define COMMANDS_NUM		10
#define INVALID_BUTTON		0xEE

typedef void (*cmd_funptr_t)(void);
typedef uint8_t cmd_code_t;

/* Flag changed to false when the remote message is ready and changed to true after executing the command */
extern bool is_cmd_executed;

static const cmd_funptr_t cmd_table[COMMANDS_NUM] =
{
	&stop,
	&accelerate_forward_to_max_if_can_drive,
	&accelerate_backwards_to_max_if_can_drive,
	&turn_right,
	&turn_left,
	&change_light_normal,
	&change_light_turnright,
	&change_light_turnleft,
	&change_light_emergency,
	&horn
};


static cmd_code_t decode_button_code(button_code_t code)
{
	switch (code)
	{
		case IR_REMOTE_CODE_ONOFF:
		{
			return 0;
		}

		case IR_REMOTE_CODE_PLUS:
		{
			return 1;
		}

		case IR_REMOTE_CODE_MINUS:
		{
			return 2;
		}

		case IR_REMOTE_CODE_FORWARD:
		{
			return 3;
		}

		case IR_REMOTE_CODE_REWIND:
		{
			return 4;
		}

		case IR_REMOTE_CODE_MENU:
		{
			return 5;
		}

		case IR_REMOTE_CODE_3:
		{
			return 6;
		}

		case IR_REMOTE_CODE_1:
		{
			return 7;
		}

		case IR_REMOTE_CODE_2:
		{
			return 8;
		}

		case IR_REMOTE_CODE_PLAY:
		{
			return 9;
		}

		default:
		{
			return INVALID_BUTTON;
		}

	}
}


void execute_cmd_if_pending(void)
{
	/* Check if command was already executed */
	if (true == is_cmd_executed)
	{
		return;
	}

	button_code_t button_code = ir_remote_read_button();

	/* Check if command was read from the correct remote */
	if (MSG_INVALID_ADDR == button_code)
	{
		return;
	}

	/* Check if there is a pending command */
	if (MSG_NOT_READY == button_code)
	{
		return;
	}

	cmd_code_t cmd = decode_button_code(button_code);

	/* Check if was clicked button without assigned command */
	if (INVALID_BUTTON == cmd)
	{
		return;
	}

	cmd_table[cmd]();
	is_cmd_executed = true;
	//HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
}
