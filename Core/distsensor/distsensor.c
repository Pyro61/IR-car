/* Module header include */
#include "distsensor.h"

/* Driver includes */
#include "driver_distsensor.h"

/* Variables */
/* Structures */
struct distsensor distsensor_front;
struct distsensor distsensor_back;

/* Static function definitions */
static void distsensor_init(struct distsensor *distsensor)
{
    distsensor -> current_dist = 0.0f;
    distsensor -> assumed_dist = 0.0f;
    distsensor -> is_obst_inrange = false;
}


static void distsensor_setassumed_dist(struct distsensor *distsensor, distcm_t dist)
{
    distsensor -> assumed_dist = dist;
}


static void distsensor_update_dist(struct distsensor *distsensor, distcm_t dist)
{
    distsensor -> current_dist = dist;
}


static bool distsensor_obst_inrange_flagcheck(struct distsensor *distsensor)
{
	if ((distsensor -> current_dist) <= (distsensor -> assumed_dist))
	{
	    distsensor -> is_obst_inrange = true;
	}

	else
	{
	    distsensor -> is_obst_inrange = false;
	}

    return distsensor -> is_obst_inrange;
}


/* Function definitions */
/* Setting assumed distance from obstacles functions */
void distsensor_setassumed_dist_front(distcm_t assumed_dist)
{
    distsensor_setassumed_dist(&distsensor_front, assumed_dist);
}


void distsensor_setassumed_dist_back(distcm_t assumed_dist)
{
    distsensor_setassumed_dist(&distsensor_back, assumed_dist);
}


/* Calculating distance from obstacles functions */
void distsensor_calc_dist_front(void)
{
	distcm_t actual_dist = driver_distsensor_calc_dist(DISTSENSOR_FRONT);
    distsensor_update_dist(&distsensor_front, actual_dist);
}


void distsensor_calc_dist_back(void)
{
	distcm_t actual_dist = driver_distsensor_calc_dist(DISTSENSOR_BACK);
    distsensor_update_dist(&distsensor_back, actual_dist);
}


/* Checking if obstacles are in assumed range functions */
bool distsensor_is_obst_inrange_front(void)
{
    return distsensor_obst_inrange_flagcheck(&distsensor_front);
}


bool distsensor_is_obst_inrange_back(void)
{
    return distsensor_obst_inrange_flagcheck(&distsensor_back);
}


/* Init function */
void distsensor_initall(distcm_t assumed_dist_front, distcm_t assumed_dist_back)
{
    distsensor_init(&distsensor_front);
    distsensor_init(&distsensor_back);

    distsensor_setassumed_dist_front(assumed_dist_front);
    distsensor_setassumed_dist_back(assumed_dist_back);

    driver_distsensor_initall();
}
