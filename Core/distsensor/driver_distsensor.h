#pragma once

/* Defines */
#define DISTSENSORS_QUANTITY	2

/* Typedefs */
typedef float distcm_t;

/* Enum declarations */
enum distsensor_id
{
	DISTSENSOR_FRONT	= 0,
	DISTSENSOR_BACK		= 1
};

/* Function prototypes */
/* Init function */
void driver_distsensor_initall(void);

/* Calculating distance from obstacle on front/back sensor function */
distcm_t driver_distsensor_calc_dist(enum distsensor_id id);
