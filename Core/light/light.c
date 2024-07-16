#include "light.h"
#include "driver_light.h"
#include "event.h"
#include <stdbool.h>

struct light light_frontright;
struct light light_frontleft;
struct light light_backright;
struct light light_backleft;

bool are_lights_sets_changed = true;

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


static void light_turnchange(struct light *light)
{
	if (1 == (light -> turn_activate))
	{
		light -> turn = !(light -> turn);

		are_lights_sets_changed	= true;
	}

	else
	{
		light -> turn = 0;

		are_lights_sets_changed	= true;
	}
}


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


static void light_turnchange_right(void)
{
	light_turnchange(&light_frontright);
	light_turnchange(&light_backright);
}


static void light_turnchange_left(void)
{
	light_turnchange(&light_frontleft);
	light_turnchange(&light_backleft);
}


static void light_emergencychange_all(void)
{
	light_emergencychange(&light_frontright);
	light_emergencychange(&light_frontleft);
	light_emergencychange(&light_backright);
	light_emergencychange(&light_backleft);
}


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


void light_sending_complete(void)
{
	driver_light_sending_complete();
	are_lights_sets_changed = false;
}
