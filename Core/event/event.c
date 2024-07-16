/* Module header include */
#include "event.h"

/* Standard library includes */
#include <stdio.h>
#include <stdint.h>

/* Defines */
#define MAX_SUBSCRIBERS		8

/* Variables */
/* Arrays for subscribed functions */
static callback_t subscribers1ms[MAX_SUBSCRIBERS];
static callback_t subscribers10ms[MAX_SUBSCRIBERS];
static callback_t subscribers300ms[MAX_SUBSCRIBERS];
static callback_t subscribers500ms[MAX_SUBSCRIBERS];

/* Counters for times other than 1ms */
static volatile uint16_t counter10ms = 0;
static volatile uint16_t counter300ms = 0;
static volatile uint16_t counter500ms = 0;


/* Function definitions */
/* Subscribe functions */
void subscribe_1ms(callback_t callback)
{
	uint8_t i;
	for (i = 0; i < MAX_SUBSCRIBERS; i++)
	{
		if (NULL == subscribers1ms[i])
		{
			subscribers1ms[i] = callback;
			break;
		}

		else
		{
			/* Do nothing */
		}
	}
}


void subscribe_10ms(callback_t callback)
{
	uint8_t i;
	for (i = 0; i < MAX_SUBSCRIBERS; i++)
	{
		if (NULL == subscribers10ms[i])
		{
			subscribers10ms[i] = callback;
			break;
		}

		else
		{
			/* Do nothing */
		}
	}
}


void subscribe_300ms(callback_t callback)
{
	uint8_t i;
	for (i = 0; i < MAX_SUBSCRIBERS; i++)
	{
		if (NULL == subscribers300ms[i])
		{
			subscribers300ms[i] = callback;
			break;
		}

		else
		{
			/* Do nothing */
		}
	}
}


void subscribe_500ms(callback_t callback)
{
	uint8_t i;
	for (i = 0; i < MAX_SUBSCRIBERS; i++)
	{
		if (NULL == subscribers500ms[i])
		{
			subscribers500ms[i] = callback;
			break;
		}

		else
		{
			/* Do nothing */
		}
	}
}


/* Calling functions */
static void call_subscribers_10ms(void)
{
	uint8_t i;
	for (i = 0; i < MAX_SUBSCRIBERS; i++)
	{
		if (NULL != subscribers10ms[i])
		{
			subscribers10ms[i]();
		}

		else
		{
			/* Do nothing */
		}
	}
}


static void call_subscribers_300ms(void)
{
	uint8_t i;
	for (i = 0; i < MAX_SUBSCRIBERS; i++)
	{
		if (NULL != subscribers300ms[i])
		{
			subscribers300ms[i]();
		}

		else
		{
			/* Do nothing */
		}
	}
}


static void call_subscribers_500ms(void)
{
	uint8_t i;
	for (i = 0; i < MAX_SUBSCRIBERS; i++)
	{
		if (NULL != subscribers500ms[i])
		{
			subscribers500ms[i]();
		}

		else
		{
			/* Do nothing */
		}
	}
}


/* Checking the times greater than 1ms functions */
static void check_10ms(void)
{
	if (counter10ms >= 10)
	{
		call_subscribers_10ms();
		counter10ms = 0;
	}
}


static void check_300ms(void)
{
	if (counter300ms >= 300)
	{
		call_subscribers_300ms();
		counter300ms = 0;
	}
}


static void check_500ms(void)
{
	if (counter500ms >= 500)
	{
		call_subscribers_500ms();
		counter500ms = 0;
	}
}


/* Calling 1ms event function */
void call_subscribers_1ms(void)
{
	uint8_t i;
	for (i = 0; i < MAX_SUBSCRIBERS; i++)
	{
		if (NULL != subscribers1ms[i])
		{
			subscribers1ms[i]();
		}

		else
		{
			/* Do nothing */
		}
	}

	counter10ms++;
	counter300ms++;
	counter500ms++;
	check_10ms();
	check_300ms();
	check_500ms();
}
