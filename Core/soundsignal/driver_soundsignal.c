#include "driver_soundsignal.h"
#include "tim.h"
#include "event.h"
#include <stdint.h>
#include <stdbool.h>


#define DELAY_PRESCALER_MULTIPLIER          10
#define DELAY_PRESCALER_CALC(delay)         ((delay * DELAY_PRESCALER_MULTIPLIER) - 1)

#define PRESCALER_HORN						5000
#define PRESCALER_TURN						1700
#define PRESCALER_EMERGENCY					1700
#define PRESCALER_DISTSENSORSBLOCK			400

enum priority
{
	PRIORITY_NONE 			 = 0,
	PRIORITY_TURN 			 = 1,
	PRIORITY_EMERGENCY 		 = 2,
	PRIORITY_DISTSENSORBLOCK = 3,
	PRIORITY_HORN			 = 4
};

typedef uint32_t prescaler_t;

static enum priority priority = PRIORITY_NONE;
volatile bool on_off_soundsignal_tim;


static void driver_soundsignal_boardhw_set_timprescaler(prescaler_t value)
{
    __HAL_TIM_SET_PRESCALER(&htim3, value);
}


void driver_soundsignal_boardhw_start_soundsignal_tim(void)
{
    HAL_TIM_Base_Start(&htim3);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
}


void driver_soundsignal_boardhw_stop_soundsignal_tim(void)
{
	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
    HAL_TIM_Base_Stop(&htim3);
}


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



