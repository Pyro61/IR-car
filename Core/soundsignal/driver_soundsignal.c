#include "driver_soundsignal.h"
#include "tim.h"

typedef uint32_t prescaler_t;
typedef uint8_t priority_t;

#define PRIORITY_LOWBATTERY                 5
#define PRIORITY_HORN                       4
#define PRIORITY_DISTSENSORBLOCK            3
#define PRIORITY_EMERGENCYLIGHT             2
#define PRIORITY_TURN                       1


static TIM_HandleTypeDef *soundsignal_tim = &htim3;
static TIM_HandleTypeDef *delay_tim = &htim6;

priority_t priority = 0;
volatile bool on_off_soundsignal_tim = false;


static void driver_soundsignal_boardhw_set_timprescaler(TIM_HandleTypeDef *tim, prescaler_t value)
{
    __HAL_TIM_SET_PRESCALER(tim, value);
}


void driver_soundsignal_boardhw_start_soundsignal_tim(void)
{
    HAL_TIM_Base_Start(soundsignal_tim);
    HAL_TIM_PWM_Start(soundsignal_tim, TIM_CHANNEL_1);
}


void driver_soundsignal_boardhw_stop_soundsignal_tim(void)
{
    HAL_TIM_Base_Stop(soundsignal_tim);
    HAL_TIM_PWM_Stop(soundsignal_tim, TIM_CHANNEL_1);
}


static void driver_soundsignal_boardhw_start_delay_tim(void)
{
    HAL_TIM_Base_Start_IT(delay_tim);
}


static void driver_soundsignal_boardhw_stop_delay_tim(void)
{
    HAL_TIM_Base_Stop_IT(delay_tim);
}


void driver_soundsignal_on_horn(void)
{
    if (PRIORITY_HORN >= priority)
    {
        priority = PRIORITY_HORN;
        driver_soundsignal_boardhw_set_timprescaler(soundsignal_tim, 5000 - 1);
        driver_soundsignal_boardhw_start_soundsignal_tim();
    }
}


void driver_soundsignal_on_turn(void)
{
    if(PRIORITY_TURN >= priority)
    {
        priority = PRIORITY_TURN;
        driver_soundsignal_boardhw_set_timprescaler(soundsignal_tim, 1700 - 1);
        driver_soundsignal_boardhw_set_timprescaler(delay_tim, DELAY_PRESCALER_CALC(200));
        driver_soundsignal_boardhw_start_soundsignal_tim();
        driver_soundsignal_boardhw_start_delay_tim();
    }
}


void driver_soundsignal_on_emergencylights(void)
{
    if(PRIORITY_EMERGENCYLIGHT >= priority)
    {
        priority = PRIORITY_EMERGENCYLIGHT;
        driver_soundsignal_boardhw_set_timprescaler(soundsignal_tim, 1700 - 1);
        driver_soundsignal_boardhw_set_timprescaler(delay_tim, DELAY_PRESCALER_CALC(200));
        driver_soundsignal_boardhw_start_soundsignal_tim();
        driver_soundsignal_boardhw_start_delay_tim();
    }
}


void driver_soundsignal_on_distsensorblock(void)
{
    if(PRIORITY_DISTSENSORBLOCK >= priority)
    {
        priority = PRIORITY_DISTSENSORBLOCK;
        driver_soundsignal_boardhw_set_timprescaler(soundsignal_tim, 400 - 1);
        driver_soundsignal_boardhw_start_soundsignal_tim();
    }
}


void driver_soundsignal_on_lowbattery(void)
{
    if(PRIORITY_LOWBATTERY >= priority)
    {
        priority = PRIORITY_LOWBATTERY;
        driver_soundsignal_boardhw_set_timprescaler(soundsignal_tim, 2400 - 1);
        driver_soundsignal_boardhw_set_timprescaler(delay_tim, DELAY_PRESCALER_CALC(1000));
        driver_soundsignal_boardhw_start_soundsignal_tim();
        driver_soundsignal_boardhw_start_delay_tim();
    }
}


void driver_soundsignal_off_horn(void)
{
    driver_soundsignal_boardhw_stop_soundsignal_tim();
    priority = 0;
}


void driver_soundsignal_off_turn(void)
{
    driver_soundsignal_boardhw_stop_soundsignal_tim();
    driver_soundsignal_boardhw_stop_delay_tim();
    priority = 0;
}


void driver_soundsignal_off_emergencylights(void)
{
    driver_soundsignal_boardhw_stop_soundsignal_tim();
    driver_soundsignal_boardhw_stop_delay_tim();
    priority = 0;
}


void driver_soundsignal_off_distsensorblock(void)
{
    driver_soundsignal_boardhw_stop_soundsignal_tim();
    priority = 0;
}


void driver_soundsignal_off_lowbattery(void)
{
    driver_soundsignal_boardhw_stop_soundsignal_tim();
    driver_soundsignal_boardhw_stop_delay_tim();
    priority = 0;
}

