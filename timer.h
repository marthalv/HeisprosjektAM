#ifndef timer_h
#define timer_h

#include <stdio.h>
#include <stdbool.h>
#include <time.h>

time_t timer_start_timer();
int timer_time_is_up(time_t start_time);

#endif /* timer_h */
