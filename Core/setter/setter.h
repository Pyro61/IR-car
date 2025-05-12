#pragma once

/* Standard library include */
#include <stdint.h>

/* Function prototypes */
/* Functions assigned to remote's buttons */
void stop(void);
void accelerate_forward_to_max_if_can_drive(void);
void accelerate_backwards_to_max_if_can_drive(void);
void turn_right(void);
void turn_left(void);
void change_light_normal(void);
void change_light_turnright(void);
void change_light_turnleft(void);
void change_light_emergency(void);
void horn(void);

/* Function called in main while (1) loop */
void check_distance_from_obstacles_and_eventually_stop_motors();


