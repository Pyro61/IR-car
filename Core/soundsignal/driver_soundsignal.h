#pragma once

#include "stdbool.h"

extern volatile bool on_off_soundsignal_tim;


void driver_soundsignal_on_horn(void);
void driver_soundsignal_on_turn(void);
void driver_soundsignal_on_emergency(void);
void driver_soundsignal_on_distsensorblock(void);

void driver_soundsignal_off_horn(void);
void driver_soundsignal_off_turn(void);
void driver_soundsignal_off_emergency(void);
void driver_soundsignal_off_distsensorblock(void);

void driver_soundsignal_boardhw_start_soundsignal_tim(void);
void driver_soundsignal_boardhw_stop_soundsignal_tim(void);
