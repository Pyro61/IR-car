#pragma once

/* Standard library includes */
#include <stdbool.h>
#include <stdint.h>

/* Typedefs */
typedef float distcm_t;

/* Structure declarations */
struct distsensor
{
    distcm_t assumed_dist;
    distcm_t current_dist;
    bool is_obst_inrange;
};

/* Function prototypes */
void distsensor_initall(distcm_t assumed_dist_front, distcm_t assumed_dist_back);

void distsensor_setassumed_dist_front(distcm_t assumed_dist);
void distsensor_setassumed_dist_back(distcm_t assumed_dist);

void distsensor_calc_dist_front(void);
void distsensor_calc_dist_back(void);

bool distsensor_is_obst_inrange_front(void);
bool distsensor_is_obst_inrange_back(void);

