#pragma once

/* Standard library includes */
#include <stdint.h>
#include <stdbool.h>

/* Typedefs */
typedef int16_t motorspeed_t;

/* Enum declarations */
enum motor_direction
{
    MOTOR_DIRECTION_STOP        = 0,
    MOTOR_DIRECTION_FORWARD     = 1,
    MOTOR_DIRECTION_BACKWARDS   = 2
};

/* Structures declarations */
struct motor
{
    motorspeed_t speed;
    enum motor_direction direction;
    const uint8_t motor_id;
};

//extern struct motor motor_frontright;
//extern struct motor motor_frontleft;
//extern struct motor motor_backright;
//extern struct motor motor_backleft;

/* Function prototypes */
/* Stopping all motors function */
void motor_stopall(void);

/* Driving straight functions */
void motor_accelerate_forward_to_max(void);
void motor_accelerate_backwards_to_max(void);

/* Turn functions */
void motor_turn_right(void);
void motor_turn_left(void);

/* Init function */
void motor_initall(void);
