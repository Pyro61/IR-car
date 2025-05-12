/* Module include */
#include "soundsignal.h"

/* Driver include */
#include "driver_soundsignal.h"

/* Other module include */
#include "event.h"

/* Enum declarations */
enum state
{
	OFF	= 0,
	ON	= 1
};

/* Varaibles */
enum state turn_state = OFF;
enum state emergency_state = OFF;

enum state turn_activate = OFF;
enum state emergency_activate = OFF;

/* Static function definitions */
/* Turning on/off turn sound signal 500ms if activated */
static void soundsignal_change_turn(void)
{
	if (ON == emergency_activate)
	{
		return;
	}

	if (OFF == turn_activate)
	{
		driver_soundsignal_off_turn();
		turn_state = OFF;

		return;
	}

	if (OFF == turn_state)
	{
		driver_soundsignal_on_turn();
		turn_state = ON;
	}

	else
	{
		driver_soundsignal_off_turn();
		turn_state = OFF;
	}
}


/* Changing on/off emergency signal every 300ms if activated */
static void soundsignal_change_emergency(void)
{
	if (OFF == emergency_activate)
	{
		driver_soundsignal_off_emergency();
		emergency_state = OFF;

		return;
	}

	if (OFF == emergency_state)
	{
		driver_soundsignal_on_emergency();
		emergency_state = ON;
	}

	else
	{
		driver_soundsignal_off_emergency();
		emergency_state = OFF;
	}
}


/* Function definitions */
/* Turning on functions */
void soundsignal_on_horn(void)
{
    driver_soundsignal_on_horn();
}


void soundsignal_on_turn(void)
{
    turn_activate = ON;
}


void soundsignal_on_emergency(void)
{
    emergency_activate = ON;
}


void soundsignal_on_distsensorblock(void)
{
    driver_soundsignal_on_distsensorblock();
}


/* Turning off functions */
void soundsignal_off_horn(void)
{
    driver_soundsignal_off_horn();
}


void soundsignal_off_turn(void)
{
    turn_activate = OFF;
}


void soundsignal_off_emergency(void)
{
	emergency_activate = OFF;
}


void soundsignal_off_distsensorblock(void)
{
    driver_soundsignal_off_distsensorblock();
}


/* Init function */
void soundsignal_init(void)
{
	subscribe_500ms(&soundsignal_change_turn);
	subscribe_300ms(&soundsignal_change_emergency);
}
