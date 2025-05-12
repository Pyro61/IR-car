#pragma once

/* Function prototypes */
/* Setting on/off light modes functions */

void light_seton_normalfront(void);
void light_setoff_normalfront(void);

void light_seton_reversingback(void);
void light_setoff_reversingback(void);

void light_seton_stopback(void);
void light_setoff_stopback(void);

void light_seton_turnright(void);
void light_setoff_turnright(void);

void light_seton_turnleft(void);
void light_setoff_turnleft(void);

void light_seton_emergencyall(void);
void light_setoff_emergencyall(void);

/* Reading light sets and send to hardware driver function */
void light_readset_all_if_changed_and_send_sets(void);

/* Sending completed callback */
void light_sending_completed_callback(void);

/* Init function */
void light_initall(void);

