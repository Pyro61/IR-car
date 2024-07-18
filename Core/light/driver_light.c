/* Module header include */
#include "driver_light.h"

/*  HW submodule include */
#include "ws2812b/ws2812b.h"

/* Standard library include */
#include <stdio.h>

/* Defines */
/* Light modes bit codes */
#define NORMAL_CODE				0x01
#define REVERSING_CODE			0x02
#define STOP_CODE				0x04
#define TURN_CODE				0x08
#define EMERGENCY_CODE			0x10

/* LEDs codes */
#define LED1					0
#define LED2					1
#define LED3					2
#define LED4					3
#define LED5					4
#define LED6					5
#define LED7					6

/* Light modes RGB codes */
#define BLANK_COLOR				0,0,0
#define NORMAL_COLOR			20,20,20
#define REVERSING_COLOR			90,10,0
#define STOP_COLOR				255,0,0
#define TURN_COLOR				120,40,0
#define EMERGENCY_COLOR			120,40,0

/* Amount of light modes */
#define LIGHT_MODES				5

/* Typedefs */
typedef void (*driver_lightset_funptr)(void);

/* Static function definitions */
/* LEDs coding functions
 * Before "_" :
 * fr - front right lamp
 * fl - front left lamp
 * br - back right lamp
 * bl - back left lamp
 * After  "_" :
 * Light modes */
static void fr_normal(void)
{
	ws2812b_code(NORMAL_COLOR, LIGHT_FRONTRIGHT, LED2);
	ws2812b_code(NORMAL_COLOR, LIGHT_FRONTRIGHT, LED3);
	ws2812b_code(NORMAL_COLOR, LIGHT_FRONTRIGHT, LED4);
	ws2812b_code(NORMAL_COLOR, LIGHT_FRONTRIGHT, LED5);
	ws2812b_code(NORMAL_COLOR, LIGHT_FRONTRIGHT, LED7);
}


static void fr_turn(void)
{
	ws2812b_code(TURN_COLOR, LIGHT_FRONTRIGHT, LED1);
	ws2812b_code(TURN_COLOR, LIGHT_FRONTRIGHT, LED6);
}


static void fr_emergency(void)
{
	ws2812b_code(EMERGENCY_COLOR, LIGHT_FRONTRIGHT, LED1);
	ws2812b_code(EMERGENCY_COLOR, LIGHT_FRONTRIGHT, LED6);
}


static void fl_normal(void)
{
	ws2812b_code(NORMAL_COLOR, LIGHT_FRONTLEFT, LED1);
	ws2812b_code(NORMAL_COLOR, LIGHT_FRONTLEFT, LED2);
	ws2812b_code(NORMAL_COLOR, LIGHT_FRONTLEFT, LED5);
	ws2812b_code(NORMAL_COLOR, LIGHT_FRONTLEFT, LED6);
	ws2812b_code(NORMAL_COLOR, LIGHT_FRONTLEFT, LED7);
}


static void fl_turn(void)
{
	ws2812b_code(TURN_COLOR, LIGHT_FRONTLEFT, LED3);
	ws2812b_code(TURN_COLOR, LIGHT_FRONTLEFT, LED4);
}


static void fl_emergency(void)
{
	ws2812b_code(EMERGENCY_COLOR, LIGHT_FRONTLEFT, LED3);
	ws2812b_code(EMERGENCY_COLOR, LIGHT_FRONTLEFT, LED4);
}


static void bl_reversing(void)
{
	ws2812b_code(REVERSING_COLOR, LIGHT_BACKLEFT, LED2);
	ws2812b_code(REVERSING_COLOR, LIGHT_BACKLEFT, LED3);
}


static void bl_stop(void)
{
	ws2812b_code(STOP_COLOR, LIGHT_BACKLEFT, LED4);
	ws2812b_code(STOP_COLOR, LIGHT_BACKLEFT, LED5);
	ws2812b_code(STOP_COLOR, LIGHT_BACKLEFT, LED7);
}


static void bl_turn(void)
{
	ws2812b_code(TURN_COLOR, LIGHT_BACKLEFT, LED1);
	ws2812b_code(TURN_COLOR, LIGHT_BACKLEFT, LED6);
}


static void bl_emergency(void)
{
	ws2812b_code(EMERGENCY_COLOR, LIGHT_BACKLEFT, LED1);
	ws2812b_code(EMERGENCY_COLOR, LIGHT_BACKLEFT, LED6);
}


static void br_reversing(void)
{
	ws2812b_code(REVERSING_COLOR, LIGHT_BACKRIGHT, LED1);
	ws2812b_code(REVERSING_COLOR, LIGHT_BACKRIGHT, LED2);
}


static void br_stop(void)
{
	ws2812b_code(STOP_COLOR, LIGHT_BACKRIGHT, LED5);
	ws2812b_code(STOP_COLOR, LIGHT_BACKRIGHT, LED6);
	ws2812b_code(STOP_COLOR, LIGHT_BACKRIGHT, LED7);
}


static void br_turn(void)
{
	ws2812b_code(TURN_COLOR, LIGHT_BACKRIGHT, LED3);
	ws2812b_code(TURN_COLOR, LIGHT_BACKRIGHT, LED4);
}


static void br_emergency(void)
{
	ws2812b_code(EMERGENCY_COLOR, LIGHT_BACKRIGHT, LED3);
	ws2812b_code(EMERGENCY_COLOR, LIGHT_BACKRIGHT, LED4);
}


/* Matrix with LEDs coding functions */
static const driver_lightset_funptr driver_lightset_funptr_table[4][5] = {{fr_normal, NULL, NULL, fr_turn, fr_emergency},
																		 {fl_normal, NULL, NULL, fl_turn, fl_emergency},
																		 {NULL, bl_reversing, bl_stop, bl_turn, bl_emergency},
																		 {NULL, br_reversing, br_stop, br_turn, br_emergency}};

/* Function definitions */
/* Reading set from lamp and sets the LEDs function */
void driver_light_setlight(uint8_t set, enum light_id id)
{
	/* Wait for the transmit end - for not overwriting the buffer */
	while(ws2812b_is_transmit_possible()){};

	int i;
	for(i = 0; i < LIGHT_MODES; i++)
	{
		uint8_t tmp = set >> i;
		if (0 != (tmp & 0x01))
		{
			driver_lightset_funptr_table[id][i]();
		}
	}
}


/* Sending light codes function */
void driver_light_send_sets(void)
{
	ws2812b_send();
}


/* End of sending function */
void driver_light_sending_completed(void)
{
	ws2812b_end_of_transmit();
}


/* Init function */
void driver_light_init(void)
{
	ws2812b_init();
}
