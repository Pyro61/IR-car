#pragma once

/* Standard library includes */
#include <stdbool.h>
#include <stdint.h>

/* Typedefs */
typedef float distcm_t;

/* Function prototypes */
/* Setting assumed distance functions */
void distsensor_setassumed_dist_front(distcm_t assumed_dist);
void distsensor_setassumed_dist_back(distcm_t assumed_dist);

/* Calculating distance from obstacles functions */
void distsensor_calc_dist_front(void);
void distsensor_calc_dist_back(void);

/* Checking if obstacles are closer than assumed distance functions */
bool distsensor_is_obst_inrange_front(void);
bool distsensor_is_obst_inrange_back(void);

/* Init function */
void distsensor_initall(distcm_t assumed_dist_front, distcm_t assumed_dist_back);
