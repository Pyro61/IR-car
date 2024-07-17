#pragma once

#include <stdint.h>

void soundsignal_on_horn(void);
void soundsignal_on_turn(void);
void soundsignal_on_emergency(void);
void soundsignal_on_distsensorblock(void);

void soundsignal_off_horn(void);
void soundsignal_off_turn(void);
void soundsignal_off_emergency(void);
void soundsignal_off_distsensorblock(void);

void soundsignal_init(void);

