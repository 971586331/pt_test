
#include "pt.h"
#include <stm32f1xx_hal.h>

struct timer { int start, interval; };

static int timer_expired(struct timer *t)
{ return (int)(HAL_GetTick() - t->start) >= (int)t->interval; }

static void timer_set(struct timer *t, int interval)
{ t->interval = interval; t->start = HAL_GetTick(); }

static struct timer input_timer;

int protothread1(struct pt *pt)
{
  /* A protothread function must begin with PT_BEGIN() which takes a
     pointer to a struct pt. */
  PT_BEGIN(pt);

  /* We loop forever here. */
  while(1) {

		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
		timer_set(&input_timer, 500);
		PT_WAIT_UNTIL(pt, timer_expired(&input_timer));
		
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
		timer_set(&input_timer, 100);
		PT_WAIT_UNTIL(pt, timer_expired(&input_timer));
  }

  /* All protothread functions must end with PT_END() which takes a
     pointer to a struct pt. */
  PT_END(pt);
}
