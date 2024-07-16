/* Module header include */
#include "driver_distsensor.h"

/* Board hardware includes */
#include "tim.h"
#include "gpio.h"

/* Defines */
#define CM_CALC_DIVIVER		58.0f

/* Typedefs */
typedef distcm_t (*driver_distsensor_funptr)(void);

/* Static function definitions */
/* Init functions */
static void driver_distsensor_init_front(void)
{
	/* Start timer and channels
	 * CHANNELS 1 and 2 - measuring ECHO signal from sensor
	 * CHANNEL 3 - Trigger signal (10 us) */
	HAL_TIM_Base_Start_IT(&htim8);
	HAL_TIM_IC_Start(&htim8, TIM_CHANNEL_1);
	HAL_TIM_IC_Start(&htim8, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3);
}


static void driver_distsensor_init_back(void)
{
	/* Start timer and channels
	* CHANNELS 1 and 2 - measuring ECHO signal from sensor
	* CHANNEL 3 - Trigger signal (10 us) */
	HAL_TIM_Base_Start_IT(&htim1);
	HAL_TIM_IC_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_IC_Start(&htim1, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
}


/* Calculating distance from obstacles functions */
static distcm_t front_dist_calc(void)
{
	uint32_t start = HAL_TIM_ReadCapturedValue(&htim8, TIM_CHANNEL_1);
	uint32_t stop = HAL_TIM_ReadCapturedValue(&htim8, TIM_CHANNEL_2);
	return (stop - start) / CM_CALC_DIVIVER;
}


static distcm_t back_dist_calc(void)
{
	uint32_t start = HAL_TIM_ReadCapturedValue(&htim1, TIM_CHANNEL_1);
	uint32_t stop = HAL_TIM_ReadCapturedValue(&htim1, TIM_CHANNEL_2);
	return (stop - start) / CM_CALC_DIVIVER;
}

/* Variables */
/* Calculating distance from obstacles functions array */
static const driver_distsensor_funptr driver_distsensor_funptr_table [DISTSENSORS_QUANTITY] = {&front_dist_calc, &back_dist_calc};


/* Function definitions */
/* Init function */
void driver_distsensor_initall(void)
{
	driver_distsensor_init_front();
	driver_distsensor_init_back();
}


/* Calculating distance from obstacle on front/back sensor function */
distcm_t driver_distsensor_calc_dist(enum distsensor_id id)
{
	distcm_t dist = driver_distsensor_funptr_table[id]();

	return dist;
}
