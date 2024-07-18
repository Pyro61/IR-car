#include "light.h"
#include "driver_light.h"
#include "event.h"
#include <stdbool.h>

/* Standard library include */
#include <stdint.h>

/* Typedefs */
typedef uint8_t light_mode_t;

/* Structure declarations */
struct light
{
    light_mode_t normal:1;
    light_mode_t reversing:1;
    light_mode_t stop:1;
    light_mode_t turn:1;
    light_mode_t emergency:1;
    light_mode_t turn_activate:1;
    light_mode_t emergency_activate:1;
};

/* Variables */
static bool are_lights_sets_changed = true;

/* Structures */
static struct light light_frontright;
static struct light light_frontleft;
static struct light light_backright;
static struct light light_backleft;

/* Static function definitions */
/* Init function */
static void light_init(struct light *light)
{
    light -> normal = 0;
    light -> reversing = 0;
    light -> stop = 0;
    light -> turn = 0;
    light -> emergency = 0;
    light -> turn_activate = 0;
    light -> emergency_activate = 0;
}


/* Setting functions */
static void light_setnormal(struct light *light, bool set)
{
    light -> normal = set;
}


static void light_setreversing(struct light *light, bool set)
{
    light -> reversing = set;
}


static void light_setstop(struct light *light, bool set)
{
    light -> stop = set;
}


static void light_setturn(struct light *light, bool set)
{
    light -> turn_activate = set;
}


static void light_setemergency(struct light *light, bool set)
{
    light -> emergency_activate = set;
}


/* Change turn light set if activated function */
static void light_turnchange(struct light *light)
{
	if (1 == (light -> turn_activate))
	{
		light -> turn = !(light -> turn);

		are_lights_sets_changed	= true;
	}

	/* Turn off turn light in case it was on after deactivating emergency change */
	else
	{
		light -> turn = 0;

		are_lights_sets_changed	= true;
	}
}


/* Change emergency light set if activated function */
static void light_emergencychange(struct light *light)
{
	if (1 == (light -> emergency_activate))
	{
		light -> emergency = !(light -> emergency);

		are_lights_sets_changed	= true;
	}

	/* Turn off emergency light in case it was on after deactivating emergency change */
	else
	{
		light -> emergency = 0;

		are_lights_sets_changed	= true;
	}
}


/* Change right turn lights sets function */
static void light_turnchange_right(void)
{
	light_turnchange(&light_frontright);
	light_turnchange(&light_backright);
}


/* Change left turn lights sets function */
static void light_turnchange_left(void)
{
	light_turnchange(&light_frontleft);
	light_turnchange(&light_backleft);
}


/* Change emergency lights sets function */
static void light_emergencychange_all(void)
{
	light_emergencychange(&light_frontright);
	light_emergencychange(&light_frontleft);
	light_emergencychange(&light_backright);
	light_emergencychange(&light_backleft);
}


/* Reading set from one light and send to hardware driver function */
static void light_readset(struct light *light, enum light_id id)
{
	uint8_t set = 0;

	set = (light -> normal) << 0;
	set = set | (light -> reversing) << 1;
	set = set | (light -> stop) << 2;
	set = set | (light -> turn) << 3;
	set = set | (light -> emergency) << 4;

	driver_light_setlight(set, id);
}

/* Function definitions */
/* Setting functions */
void light_seton_normalfront(void)
{
    light_setnormal(&light_frontright, 1);
    light_setnormal(&light_frontleft, 1);

    are_lights_sets_changed	= true;
}


void light_setoff_normalfront(void)
{
    light_setnormal(&light_frontright, 0);
    light_setnormal(&light_frontleft, 0);

    are_lights_sets_changed	= true;
}


void light_seton_reversingback(void)
{
    light_setreversing(&light_backright, 1);
    light_setreversing(&light_backleft, 1);

    are_lights_sets_changed	= true;
}


void light_setoff_reversingback(void)
{
    light_setreversing(&light_backright, 0);
    light_setreversing(&light_backleft, 0);

    are_lights_sets_changed	= true;
}


void light_seton_stopback(void)
{
    light_setstop(&light_backright, 1);
    light_setstop(&light_backleft, 1);

    are_lights_sets_changed	= true;
}


void light_setoff_stopback(void)
{
    light_setstop(&light_backright, 0);
    light_setstop(&light_backleft, 0);

    are_lights_sets_changed	= true;
}


void light_seton_turnright(void)
{
    light_setturn(&light_frontright, 1);
    light_setturn(&light_backright, 1);

    are_lights_sets_changed	= true;
}


void light_setoff_turnright(void)
{
    light_setturn(&light_frontright, 0);
    light_setturn(&light_backright, 0);

    are_lights_sets_changed	= true;
}


void light_seton_turnleft(void)
{
    light_setturn(&light_frontleft, 1);
    light_setturn(&light_backleft, 1);

    are_lights_sets_changed	= true;
}


void light_setoff_turnleft(void)
{
    light_setturn(&light_frontleft, 0);
    light_setturn(&light_backleft, 0);

    are_lights_sets_changed	= true;
}


void light_seton_emergencyall(void)
{
    light_setemergency(&light_frontright, 1);
    light_setemergency(&light_frontleft, 1);
    light_setemergency(&light_backright, 1);
    light_setemergency(&light_backleft, 1);

    are_lights_sets_changed	= true;
}


void light_setoff_emergencyall(void)
{
    light_setemergency(&light_frontright, 0);
    light_setemergency(&light_frontleft, 0);
    light_setemergency(&light_backright, 0);
    light_setemergency(&light_backleft, 0);

    are_lights_sets_changed	= true;
}


/* Reading light sets and send to hardware driver function */
void light_readset_all_if_changed_and_send_sets(void)
{
	if (false == are_lights_sets_changed)
	{
		return;
	}

	light_readset(&light_frontright, LIGHT_FRONTRIGHT);
	light_readset(&light_frontleft, LIGHT_FRONTLEFT);
	light_readset(&light_backright, LIGHT_BACKRIGHT);
	light_readset(&light_backleft, LIGHT_BACKLEFT);

	driver_light_send_sets();
}


/* Sending completed callback function */
void light_sending_completed_callback(void)
{
	driver_light_sending_completed();
	are_lights_sets_changed = false;
}


/* Init function */
/* Every 500ms turn lights are changed if activated */
/* Every 300ms emergency lights are changed if activated */
void light_initall(void)
{
    light_init(&light_frontright);
    light_init(&light_frontleft);
    light_init(&light_backright);
    light_init(&light_backleft);

    subscribe_500ms(&light_turnchange_right);
    subscribe_500ms(&light_turnchange_left);
    subscribe_300ms(&light_emergencychange_all);

    driver_light_init();
}
