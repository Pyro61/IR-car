#pragma once

/* Function prototypes */
/* Turning on functions */
void soundsignal_on_horn(void);
void soundsignal_on_turn(void);
void soundsignal_on_emergency(void);
void soundsignal_on_distsensorblock(void);

/* Turning off functions */
void soundsignal_off_horn(void);
void soundsignal_off_turn(void);
void soundsignal_off_emergency(void);
void soundsignal_off_distsensorblock(void);

/* Init function */
void soundsignal_init(void);

