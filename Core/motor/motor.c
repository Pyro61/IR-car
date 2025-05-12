/* Module header include */
#include "motor.h"

/* Other modules includes */
#include "driver_motor.h"

/* Standard library includes */
#include "stdlib.h"

/* Defines */
#define MOTOR_GEAR_TO_SPEED_MULTIPLIER		300

#define MOTOR_GEAR_MAX						3
#define MOTOR_GEAR_MIN						-3

#define MOTOR_CHANGE_GEAR_UP				1
#define MOTOR_CHANGE_GEAR_DOWN				-1

#define MOTOR_TURN_SPEED_DIVIDER			3

/* Macros */
#define CALC_SPEED_STRAIGHT()				(gear * MOTOR_GEAR_TO_SPEED_MULTIPLIER)
#define CALC_SPEED_TURN()					((CALC_SPEED_STRAIGHT()) / MOTOR_TURN_SPEED_DIVIDER)

/* Typedefs */
typedef int8_t gear_t;

/* Variables */
static gear_t gear = 0;

/* Structures */
static struct motor motor_frontright = {0, MOTOR_DIRECTION_STOP, 0};
static struct motor motor_frontleft = {0, MOTOR_DIRECTION_STOP, 1};
static struct motor motor_backright = {0, MOTOR_DIRECTION_STOP, 2};
static struct motor motor_backleft = {0, MOTOR_DIRECTION_STOP, 3};


/* Static function definitions */
/* "Gear" change function */
static void motor_gear_change(gear_t change)
{
	gear += change;
	if (MOTOR_GEAR_MIN > gear || MOTOR_GEAR_MAX < gear)
	{
		if (0 < change)
		{
			gear = MOTOR_GEAR_MAX;
		}

		else if (0 > change)
		{
			gear = MOTOR_GEAR_MIN;
		}
	}
}


/* Entering values of motor and set board hardware function */
static void motor_entervalues(struct motor *motor, const motorspeed_t givenspeed, const enum motor_direction givendirection)
{
    motor -> direction = givendirection;
    motor -> speed = givenspeed;

    driver_motor_setboardhw(motor);
}


/* Giving speed and driving direction to the struct functions */
static void motor_givespeed_and_direction_frontright(const motorspeed_t givenspeed, const enum motor_direction givendirection)
{
    motor_entervalues(&motor_frontright, givenspeed, givendirection);
}


static void motor_givespeed_and_direction_frontleft(const motorspeed_t givenspeed, const enum motor_direction givendirection)
{
    motor_entervalues(&motor_frontleft, givenspeed, givendirection);
}


static void motor_givespeed_and_direction_backright(const motorspeed_t givenspeed, const enum motor_direction givendirection)
{
    motor_entervalues(&motor_backright, givenspeed, givendirection);
}


static void motor_givespeed_and_direction_backleft(const motorspeed_t givenspeed, const enum motor_direction givendirection)
{
    motor_entervalues(&motor_backleft, givenspeed, givendirection);
}


/* Choosing direction function */
static enum motor_direction motor_choose_direction(motorspeed_t speed)
{
	if (0 < speed)
	{
		return MOTOR_DIRECTION_FORWARD;
	}

	if (0 > speed)
	{
		return MOTOR_DIRECTION_BACKWARDS;
	}

	else
	{
		return MOTOR_DIRECTION_STOP;
	}
}

/* Functions definitions */
/* Driving straight functions */
void motor_accelerate_forward_to_max(void)
{
	motor_gear_change(MOTOR_CHANGE_GEAR_UP);

	motorspeed_t speed_all = CALC_SPEED_STRAIGHT();

	enum motor_direction direction_all = motor_choose_direction(speed_all);

	motor_givespeed_and_direction_frontright(abs(speed_all), direction_all);
	motor_givespeed_and_direction_frontleft(abs(speed_all), direction_all);
	motor_givespeed_and_direction_backright(abs(speed_all), direction_all);
	motor_givespeed_and_direction_backleft(abs(speed_all), direction_all);
}


void motor_accelerate_backwards_to_max(void)
{
	motor_gear_change(MOTOR_CHANGE_GEAR_DOWN);

	motorspeed_t speed_all = CALC_SPEED_STRAIGHT();

	enum motor_direction direction_all = motor_choose_direction(speed_all);

	motor_givespeed_and_direction_frontright(abs(speed_all), direction_all);
	motor_givespeed_and_direction_frontleft(abs(speed_all), direction_all);
	motor_givespeed_and_direction_backright(abs(speed_all), direction_all);
	motor_givespeed_and_direction_backleft(abs(speed_all), direction_all);
}


/* Turning functions */
void motor_turn_right(void)
{
	motorspeed_t speed_right = CALC_SPEED_TURN();
	motorspeed_t speed_left = CALC_SPEED_STRAIGHT();

	enum motor_direction direction_right = motor_choose_direction(speed_right);
	enum motor_direction direction_left = motor_choose_direction(speed_left);

	motor_givespeed_and_direction_frontright(abs(speed_right), direction_right);
	motor_givespeed_and_direction_frontleft(abs(speed_left), direction_left);
	motor_givespeed_and_direction_backright(abs(speed_right), direction_right);
	motor_givespeed_and_direction_backleft(abs(speed_left), direction_left);
}


void motor_turn_left(void)
{
	motorspeed_t speed_right = CALC_SPEED_STRAIGHT();
	motorspeed_t speed_left = CALC_SPEED_TURN();

	enum motor_direction direction_right = motor_choose_direction(speed_right);
	enum motor_direction direction_left = motor_choose_direction(speed_left);

	motor_givespeed_and_direction_frontright(abs(speed_right), direction_right);
	motor_givespeed_and_direction_frontleft(abs(speed_left), direction_left);
	motor_givespeed_and_direction_backright(abs(speed_right), direction_right);
	motor_givespeed_and_direction_backleft(abs(speed_left), direction_left);
}


/* Stopping all motors function */
void motor_stopall(void)
{
	gear = 0;

    motor_entervalues(&motor_frontright, 0, MOTOR_DIRECTION_STOP);
    motor_entervalues(&motor_frontleft, 0, MOTOR_DIRECTION_STOP);
    motor_entervalues(&motor_backright, 0, MOTOR_DIRECTION_STOP);
    motor_entervalues(&motor_backleft, 0, MOTOR_DIRECTION_STOP);
}


/* Init function */
void motor_initall(void)
{
	gear = 0;

    motor_entervalues(&motor_frontright, 0, MOTOR_DIRECTION_STOP);
    motor_entervalues(&motor_frontleft, 0, MOTOR_DIRECTION_STOP);
    motor_entervalues(&motor_backright, 0, MOTOR_DIRECTION_STOP);
    motor_entervalues(&motor_backleft, 0, MOTOR_DIRECTION_STOP);

    driver_motor_select_mode(PHASE_ENABLE_MODE);
}
