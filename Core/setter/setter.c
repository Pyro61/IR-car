#include "setter.h"
#include "motor.h"
#include "light.h"
#include "distsensor.h"
#include "soundsignal.h"
#include "safe_state.h"
#include <stdbool.h>

enum state
{
	OFF,
	ON
};

enum state light_normal_state = OFF;
enum state light_turnright_state = OFF;
enum state light_turnleft_state = OFF;
enum state light_emergency_state = OFF;

enum state horn_state = OFF;

static bool can_drive_forward = true;
static bool can_drive_backwards = true;

static enum motor_direction drive_direction = MOTOR_DIRECTION_STOP;

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
	if (OFF == light_turnright_state)
		{
			light_seton_turnright();
			light_turnright_state = ON;
		}

		else
		{
			light_setoff_turnright();
			light_turnright_state = OFF;
		}
}


void change_light_turnleft(void)
{
	if (OFF == light_turnleft_state)
		{
			light_seton_turnleft();
			light_turnleft_state = ON;
		}

		else
		{
			light_setoff_turnleft();
			light_turnleft_state = OFF;
		}
}


void change_light_emergency(void)
{
	if (OFF == light_emergency_state)
		{
			light_seton_emergencyall();
			light_emergency_state = ON;
		}

		else
		{
			light_setoff_emergencyall();
			light_emergency_state = OFF;
		}
}


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


void check_distance_from_obstacles_and_eventually_stop_motors()
{
	if ((true == distsensor_is_obst_inrange_front()) && (MOTOR_DIRECTION_FORWARD == drive_direction))
	{
		stop();
		can_drive_forward = false;
	}

	else if (true == distsensor_is_obst_inrange_front())
	{
		can_drive_forward = false;
	}

	else
	{
		can_drive_forward = true;
	}


	if ((true == distsensor_is_obst_inrange_back()) && (MOTOR_DIRECTION_BACKWARDS == drive_direction))
	{
		stop();
		can_drive_backwards = false;
	}

	else if (true == distsensor_is_obst_inrange_back())
	{
		can_drive_backwards = false;
	}

	else
	{
		can_drive_backwards = true;
	}
}
