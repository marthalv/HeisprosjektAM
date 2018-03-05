//
//  timer.c
//  statemachine
//
//  Created by Anastasia on 19.02.2018.
//  Copyright © 2018 Anastasia. All rights reserved.
//

#include "timer.h"


int timer_start_periode() { 
	timeout_time = clock() + (timer_period * CLOCKS_PER_SEC); 
	return timeout_time;
}; 

int timer_time_is_up() { 
	return (clock() >= timer_start_periode());
}; 
