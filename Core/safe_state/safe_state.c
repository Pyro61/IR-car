#include "safe_state.h"
#include "main.h"

void safe_state(void)
{
	__disable_irq();
    while (1)
    {}
}
