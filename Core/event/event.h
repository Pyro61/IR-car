#pragma once

/* Typedefs */
typedef void (*callback_t)(void);

/* Function prototypes */
/* Subscribe functions */
void subscribe_1ms(callback_t callback);
void subscribe_10ms(callback_t callback);
void subscribe_300ms(callback_t callback);
void subscribe_500ms(callback_t callback);

/* Calling 1ms event function
 * Calling functions for other times are inside this function */
void call_subscribers_1ms(void);
