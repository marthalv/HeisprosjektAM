#include <stdio.h>
#include <stdbool.h>
#include <time.h>

static clock_t timeout_time;

int timer_period = 3;

void timer_reset () {timeout_time = clock() + (timer_period * CLOCKS_PER_SEC);};

bool timer_time_is_up () {return (clock() >= timeout_time);};
