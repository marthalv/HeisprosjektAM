#ifndef __INCLUDE_TIMER_H__
#define __INCLUDE_TIMER_H__

#include <stdio.h>
#include <stdbool.h>
#include <time.h>

static clock_t timeout_time; //The actual time since program starts to run

static int timer_period = 3; //Time periode the elevator stands still

int timer_start_periode(); //Sets the time periode

int timer_time_is_up(); //Checks if periode is at end or not
						//returns 1 if at ned, 0 if not

#endif

