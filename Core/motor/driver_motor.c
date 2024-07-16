/* Module header include */
#include "driver_motor.h"

/* Other module includes */
#include "safe_state.h"

/* Standard library includes */
#include <stdint.h>
#include <math.h>

/* Defines */
#define PWM_DIVIDER									1000
#define PWM_MAX_PULSE                               100
#define PWM_PULSE_CALC(speed)                       ((speed * PWM_MAX_PULSE) / PWM_DIVIDER)
#define MOTORS_QUANTITY                             4

/* Macros */
#define BOARDHW_GPIO_PORT(id)                     	(motor_boardhw_table[id] -> motor_gpio_port)
#define BOARDHW_GPIO_PIN(id)                      	(motor_boardhw_table[id] -> motor_gpio_pin)
#define BOARDHW_PWMTIM(id)                          (motor_boardhw_table[id] -> motor_pwm_tim)
#define BOARDHW_PWMCH(id)                           (motor_boardhw_table[id] -> motor_pwm_tim_channel)

/* Enum declarations */
enum motor_boardhw_direction
{
	STOP = 0,
	FORWARD = 0,
	BACKWARDS = 1
};

/* Variables */
static uint8_t stop_cnt = 0;
static uint8_t motor_cnt = 0;

/* Structurs */
static const struct motor_boardhw motor_boardhw_frontright = {MOTOR_GPIO_RIGHT_GPIO_Port, MOTOR_GPIO_RIGHT_Pin, &htim2, TIM_CHANNEL_2};
static const struct motor_boardhw motor_boardhw_frontleft = {MOTOR_GPIO_LEFT_GPIO_Port, MOTOR_GPIO_LEFT_Pin, &htim2, TIM_CHANNEL_1};
static const struct motor_boardhw motor_boardhw_backright = {MOTOR_GPIO_RIGHT_GPIO_Port, MOTOR_GPIO_RIGHT_Pin, &htim2, TIM_CHANNEL_2};
static const struct motor_boardhw motor_boardhw_backleft = {MOTOR_GPIO_LEFT_GPIO_Port, MOTOR_GPIO_LEFT_Pin, &htim2, TIM_CHANNEL_1};

/* Arrays */
static const struct motor_boardhw *motor_boardhw_table[] =
{
    &motor_boardhw_frontright,
    &motor_boardhw_frontleft,
    &motor_boardhw_backright,
    &motor_boardhw_backleft
};


/* Static functions definitions */
/* Stop timers function */
static void driver_motor_boardhw_stoptim(void)
{
    uint8_t i;
    for (i = 0; i < MOTORS_QUANTITY; i++)
    {
        HAL_TIM_Base_Stop(BOARDHW_PWMTIM(i));
    }

}


/* Setting GPIO Pins depending on the driving direction function */
static void driver_motor_boardhw_setdirection(const struct motor *motor)
{
    if (MOTOR_DIRECTION_STOP == (motor -> direction))
    {
        HAL_TIM_PWM_Stop(BOARDHW_PWMTIM(motor -> motor_id), BOARDHW_PWMCH(motor -> motor_id));
        HAL_GPIO_WritePin(BOARDHW_GPIO_PORT(motor -> motor_id), BOARDHW_GPIO_PIN(motor -> motor_id), STOP);
        stop_cnt++;
    }

    else if (MOTOR_DIRECTION_FORWARD == (motor -> direction))
    {
    	HAL_GPIO_WritePin(BOARDHW_GPIO_PORT(motor -> motor_id), BOARDHW_GPIO_PIN(motor -> motor_id), FORWARD);
    }

    else if (MOTOR_DIRECTION_BACKWARDS == (motor -> direction))
    {
    	HAL_GPIO_WritePin(BOARDHW_GPIO_PORT(motor -> motor_id), BOARDHW_GPIO_PIN(motor -> motor_id), BACKWARDS);
    }

    else
    {
        safe_state();
    }
}


/* Setting motor speed function */
static void driver_motor_boardhw_setpwm(const struct motor *motor)
{
    uint16_t pwm_pulse  = PWM_PULSE_CALC(motor -> speed);

    /* Set the motor pwm value */
    __HAL_TIM_SET_COMPARE(BOARDHW_PWMTIM(motor -> motor_id), BOARDHW_PWMCH(motor -> motor_id), pwm_pulse);

    /* Check if the motors are in idle state
     * If yes, set on the timer and pwm */
    if (HAL_TIM_STATE_READY == HAL_TIM_Base_GetState(BOARDHW_PWMTIM(motor -> motor_id)))
    {
        HAL_TIM_Base_Start(BOARDHW_PWMTIM(motor -> motor_id));
    }

    if (HAL_TIM_CHANNEL_STATE_READY == HAL_TIM_GetChannelState(BOARDHW_PWMTIM(motor -> motor_id), BOARDHW_PWMCH(motor -> motor_id)))
    {
        HAL_TIM_PWM_Start(BOARDHW_PWMTIM(motor -> motor_id), BOARDHW_PWMCH(motor -> motor_id));
    }
}


/* Checking if all motors have been set to stop function
 * If yes, stop the timer and reset the stop counter */
static void driver_motor_boardhw_checkstoptim(const struct motor *motor)
{
     if (MOTORS_QUANTITY <= stop_cnt)
    {
        driver_motor_boardhw_stoptim();
        stop_cnt = 0;
    }
}


/* Function definitions */
/* Setting board hardware function */
void driver_motor_setboardhw(const struct motor *motor)
{
    motor_cnt++;

    driver_motor_boardhw_setdirection(motor);
    driver_motor_boardhw_setpwm(motor);
    driver_motor_boardhw_checkstoptim(motor);

    /* Check if all motors have been set
     * If yes, reset the counters */
    if (MOTORS_QUANTITY <= motor_cnt)
    {
        motor_cnt = 0;
        stop_cnt = 0;
    }
}


/* Setting motors controller's mode function */
void driver_motor_select_mode(enum motors_controller_mode mode)
{
	HAL_GPIO_WritePin(MOTOR_GPIO_MODE_GPIO_Port, MOTOR_GPIO_MODE_Pin, mode);
}
