#ifndef timer_h
#define timer_h

#include <stdio.h>
#include <stdbool.h>
#include <time.h>


struct Timer {
	int time_out;
};

void timer_delay(struct Timer* timer, int delay);
int timer_time_is_up(struct Timer* timer);


#endif /* timer_h */
