#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef uint8_t priority_t;

#define DELAY_MULTIPLIER                   10
#define DELAY_PRESCALER_CALC(delay)        ((delay * DELAY_MULTIPLIER) - 1)

extern priority_t priority;
extern volatile bool on_off_soundsignal_tim;


void driver_soundsignal_on_horn(void);
void driver_soundsignal_on_turn(void);
void driver_soundsignal_on_emergencylights(void);
void driver_soundsignal_on_distsensorblock(void);
void driver_soundsignal_on_lowbattery(void);

void driver_soundsignal_off_horn(void);
void driver_soundsignal_off_turn(void);
void driver_soundsignal_off_emergencylights(void);
void driver_soundsignal_off_distsensorblock(void);
void driver_soundsignal_off_lowbattery(void);

void driver_soundsignal_boardhw_start_soundsignal_tim(void);
void driver_soundsignal_boardhw_stop_soundsignal_tim(void);
