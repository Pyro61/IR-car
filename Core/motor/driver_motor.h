#pragma once

/* Other module includes */
#include "motor.h"

/* Board hardware includes */
#include "gpio.h"
#include "tim.h"

/* Enum declarations */
enum motors_controller_mode
{
	IN_IN_MODE 		  = 0,
	PHASE_ENABLE_MODE = 1
};

/* Structures declarations */
struct motor_boardhw
{
    GPIO_TypeDef *motor_gpio_port;
    uint16_t motor_gpio_pin;
    TIM_HandleTypeDef *motor_pwm_tim;
    uint32_t motor_pwm_tim_channel;
};

/* Function prototypes */
/* Setting board hardware function */
void driver_motor_setboardhw(const struct motor *motor);

/* Setting motors controller's mode function */
void driver_motor_select_mode(enum motors_controller_mode mode);
