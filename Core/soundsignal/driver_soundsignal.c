/* Module include */
#include "driver_soundsignal.h"

/* Other module includes */
#include "event.h"

/* Board hardware include */
#include "tim.h"

/* Standard library includes */
#include <stdint.h>
#include <stdbool.h>

/* Defines */
#define DELAY_PRESCALER_MULTIPLIER          10
#define DELAY_PRESCALER_CALC(delay)         ((delay * DELAY_PRESCALER_MULTIPLIER) - 1)

#define PRESCALER_HORN						5000
#define PRESCALER_TURN						1700
#define PRESCALER_EMERGENCY					1700
#define PRESCALER_DISTSENSORSBLOCK			400

/* Typedefs */
typedef uint32_t prescaler_t;

/* Enum declarations */
/* Higher number = higher priority */
enum priority
{
	PRIORITY_NONE 			 = 0,
	PRIORITY_TURN 			 = 1,
	PRIORITY_EMERGENCY 		 = 2,
	PRIORITY_DISTSENSORBLOCK = 3,
	PRIORITY_HORN			 = 4
};

/* Variables */
static enum priority priority = PRIORITY_NONE;

/* Static function definitions */
/* Changing tim prescaler function */
static void driver_soundsignal_boardhw_set_timprescaler(prescaler_t value)
{
    __HAL_TIM_SET_PRESCALER(&htim3, value);
}


/* Static function definitions */
/* Starting pwm function */
static void driver_soundsignal_boardhw_start_soundsignal_tim(void)
{
    HAL_TIM_Base_Start(&htim3);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
}


/* Stopping pwm function */
static void driver_soundsignal_boardhw_stop_soundsignal_tim(void)
{
	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
    HAL_TIM_Base_Stop(&htim3);
}


/* Function definitions */
/* Turning on sound signal functions
 * If priority of signal is higher than current priority (currently playing signal) change the settings and play that signal
 * If current priority is higher than signal's priority, do nothing */
void driver_soundsignal_on_horn(void)
{
    if (PRIORITY_HORN >= priority)
    {
        priority = PRIORITY_HORN;
        driver_soundsignal_boardhw_set_timprescaler(PRESCALER_HORN);
        driver_soundsignal_boardhw_start_soundsignal_tim();
    }
}


void driver_soundsignal_on_turn(void)
{
    if(PRIORITY_TURN >= priority)
    {
        priority = PRIORITY_TURN;
        driver_soundsignal_boardhw_set_timprescaler(PRESCALER_TURN);
        driver_soundsignal_boardhw_start_soundsignal_tim();
    }
}


void driver_soundsignal_on_emergency(void)
{
    if(PRIORITY_EMERGENCY >= priority)
    {
        priority = PRIORITY_EMERGENCY;
        driver_soundsignal_boardhw_set_timprescaler(PRESCALER_EMERGENCY);
        driver_soundsignal_boardhw_start_soundsignal_tim();
    }
}


void driver_soundsignal_on_distsensorblock(void)
{
    if(PRIORITY_DISTSENSORBLOCK >= priority)
    {
        priority = PRIORITY_DISTSENSORBLOCK;
        driver_soundsignal_boardhw_set_timprescaler(PRESCALER_DISTSENSORSBLOCK);
        driver_soundsignal_boardhw_start_soundsignal_tim();
    }
}


/* Turning off sound signal functions
 * If priotity isn't equal to that signal priority, don't turn off the pwm */
void driver_soundsignal_off_horn(void)
{
	if (PRIORITY_HORN == priority)
	{
		driver_soundsignal_boardhw_stop_soundsignal_tim();
		priority = PRIORITY_NONE;
	}
}


void driver_soundsignal_off_turn(void)
{
	if (PRIORITY_TURN == priority)
	{
		driver_soundsignal_boardhw_stop_soundsignal_tim();
		priority = PRIORITY_NONE;
	}
}


void driver_soundsignal_off_emergency(void)
{
	if (PRIORITY_EMERGENCY == priority)
	{
		driver_soundsignal_boardhw_stop_soundsignal_tim();
		priority = PRIORITY_NONE;
	}
}


void driver_soundsignal_off_distsensorblock(void)
{
	if (PRIORITY_DISTSENSORBLOCK == priority)
	{
		driver_soundsignal_boardhw_stop_soundsignal_tim();
		priority = PRIORITY_NONE;
	}
}
