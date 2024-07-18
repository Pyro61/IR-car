/* Module header include */
#include "ws2812b.h"

/* Board hardware includes */
#include "spi.h"
#include "tim.h"

/* Standard library includes */
#include <string.h>

/* Defines */
/* 0 and 1 bit codes */
#define ZERO						0x06
#define ONE							0x1E

/* Transmitted bits buffer size defines */
#define BITS_IN_LED					24
#define RESET_SIZE					60
#define ONE_LIGHT_SIZE 				(LEDS_IN_LIGHT * BITS_IN_LED)
#define BUF_SIZE					((LIGHTS_AMOUNT * ONE_LIGHT_SIZE) + RESET_SIZE)

/* Macros */
/* Calculating position in buffer to write bit macro */
#define BUF_POSITION(light,led)		(RESET_SIZE + (light * ONE_LIGHT_SIZE) + (led * BITS_IN_LED))

/* Checking last bit of x and writing 0/1 bit code macro */
#define CHECKBIT(x)					(x && 0x01) ? ONE : ZERO

/* Variables */
static uint8_t buf[BUF_SIZE] = {0};

static bool is_buf_during_sending = false;

/* Function definitions */
/* Writing into buffer function */
void ws2812b_code(uint8_t r, uint8_t g, uint8_t b, uint8_t light, uint8_t led)
{
	if (light < 0 || light > (LIGHTS_AMOUNT - 1)|| led < 0 || led > (LEDS_IN_LIGHT - 1))
	{
		return;
	}
	uint8_t i;
	uint32_t rgb = 0;
	rgb = (g << 24) | (r << 16) | (b << 8);

	for (i = 0; i < BITS_IN_LED; i++)
	{
		uint32_t tmp = rgb >> 31;
		buf[BUF_POSITION(light, led) + i] = CHECKBIT(tmp);
		rgb <<= 1;
	}
}


/* Checking transmit possibility function */
bool ws2812b_is_transmit_possible(void)
{
	return is_buf_during_sending;
}


/* Sending buffer to LEDs function */
void ws2812b_send(void)
{
	is_buf_during_sending = true;
	HAL_SPI_Transmit_DMA(&hspi2, buf, sizeof(buf));
}


/* End of SPI transmit function */
void ws2812b_end_of_transmit(void)
{
	/* Setting coding bytes to ZERO (for LEDs) */
	memset(&buf[RESET_SIZE], ZERO, sizeof(buf) - (RESET_SIZE));

	is_buf_during_sending = false;
}


/* Initializing the lamps with blank color function */
void ws2812b_init(void)
{
	/* Setting coding bytes to ZERO (for LEDs) */
	memset(&buf[RESET_SIZE], ZERO, sizeof(buf) - (RESET_SIZE));

	ws2812b_send();
}
