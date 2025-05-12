/* Module header include */
#include "setter.h"

/* Other module includes */
#include "motor.h"
#include "light.h"
#include "distsensor.h"
#include "soundsignal.h"
#include "safe_state.h"

/* Standard library include */
#include <stdbool.h>

/* Enum declarations */
enum state
{
	OFF,
	ON
};

/* Variables */
enum state light_normal_state = OFF;
enum state light_turnright_state = OFF;
enum state light_turnleft_state = OFF;
enum state light_emergency_state = OFF;

enum state horn_state = OFF;

static bool can_drive_forward = true;
static bool can_drive_backwards = true;

static enum motor_direction drive_direction = MOTOR_DIRECTION_STOP;

/* Function prototypes */
/* Driving functions */
void stop(void)
{
	drive_direction = MOTOR_DIRECTION_STOP;

	motor_stopall();

	light_seton_stopback();
	light_setoff_reversingback();
}


void accelerate_forward_to_max_if_can_drive(void)
{
	drive_direction = MOTOR_DIRECTION_FORWARD;

	if (true == can_drive_forward)
	{
		motor_accelerate_forward_to_max();

		light_setoff_stopback();
		light_setoff_reversingback();

		soundsignal_off_distsensorblock();
	}

	else
	{
		soundsignal_on_distsensorblock();
	}
}


void accelerate_backwards_to_max_if_can_drive(void)
{
	drive_direction = MOTOR_DIRECTION_BACKWARDS;

	if (true == can_drive_backwards)
	{
		motor_accelerate_backwards_to_max();

		light_setoff_stopback();
		light_seton_reversingback();

		soundsignal_off_distsensorblock();
	}

	else
	{
		soundsignal_on_distsensorblock();
	}
}


void turn_right(void)
{
	motor_turn_right();
}


void turn_left(void)
{
	motor_turn_left();
}


/* Light functions */
void change_light_normal(void)
{
	if (OFF == light_normal_state)
	{
		light_seton_normalfront();
		light_normal_state = ON;
	}

	else
	{
		light_setoff_normalfront();
		light_normal_state = OFF;
	}
}


void change_light_turnright(void)
{
	if (ON == light_turnleft_state)
	{
		return;
	}

	if (OFF == light_turnright_state)
	{
		light_seton_turnright();
		soundsignal_on_turn();
		light_turnright_state = ON;
	}

	else
	{
		light_setoff_turnright();
		soundsignal_off_turn();
		light_turnright_state = OFF;
	}
}


void change_light_turnleft(void)
{
	if (ON == light_turnright_state)
	{
		return;
	}

	if (OFF == light_turnleft_state)
		{
			light_seton_turnleft();
			soundsignal_on_turn();
			light_turnleft_state = ON;
		}

	else
	{
		light_setoff_turnleft();
		soundsignal_off_turn();
		light_turnleft_state = OFF;
	}
}


void change_light_emergency(void)
{
	if (OFF == light_emergency_state)
	{
		light_seton_emergencyall();
		soundsignal_on_emergency();
		light_emergency_state = ON;
	}

	else
	{
		light_setoff_emergencyall();
		soundsignal_off_emergency();
		light_emergency_state = OFF;
	}
}


/* Sound signal function */
void horn(void)
{
	if (OFF == horn_state)
	{
		soundsignal_on_horn();
		horn_state = ON;
	}

	else
	{
		soundsignal_off_horn();
		horn_state = OFF;
	}
}


/* Giving permission to drive function */
void check_distance_from_obstacles_and_eventually_stop_motors()
{
	/* Obstacles detected and driving towards them */
	if ((true == distsensor_is_obst_inrange_front()) && (MOTOR_DIRECTION_FORWARD == drive_direction))
	{
		stop();
		can_drive_forward = false;
	}

	/* Obstacles detected but driving backwards/staying */
	else if (true == distsensor_is_obst_inrange_front())
	{
		can_drive_forward = false;
	}

	/* Obstacles not detected */
	else
	{
		can_drive_forward = true;
	}

	/* Obstacles detected and driving towards them */
	if ((true == distsensor_is_obst_inrange_back()) && (MOTOR_DIRECTION_BACKWARDS == drive_direction))
	{
		stop();
		can_drive_backwards = false;
	}

	/* Obstacles detected but driving forward/staying */
	else if (true == distsensor_is_obst_inrange_back())
	{
		can_drive_backwards = false;
	}

	/* Obstacles not detected */
	else
	{
		can_drive_backwards = true;
	}
}
