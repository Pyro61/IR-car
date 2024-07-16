#pragma once

#include <stdint.h>

typedef uint8_t light_mode_t;

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

//extern struct light light_frontright;
//extern struct light light_frontleft;
//extern struct light light_backright;
//extern struct light light_backleft;



void light_seton_normalfront(void); //z pilota
void light_setoff_normalfront(void); // z pilota
void light_seton_reversingback(void);
void light_setoff_reversingback(void);
void light_seton_stopback(void);
void light_setoff_stopback(void);
void light_seton_turnright(void); // z pilota
void light_setoff_turnright(void); // z pilota
void light_seton_turnleft(void); // z pilota
void light_setoff_turnleft(void); // z pilota
void light_seton_emergencyall(void); // z pilota
void light_setoff_emergencyall(void); // z pilota

void light_readset_all_if_changed_and_send_sets(void);

void light_initall(void);
void light_sending_complete(void);
