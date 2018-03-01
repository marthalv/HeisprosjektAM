//
//  timer.c
//  statemachine
//
//  Created by Anastasia on 19.02.2018.
//  Copyright © 2018 Anastasia. All rights reserved.
//

#include "timer.h"


void timer_start_periode() { 
	timeout_time = clock() + (timer_period * CLOCKS_PER_SEC); 
}; 

int timer_time_is_up() { 
	if (clock() >= timeout_time) {
		return 1;
	}
	return 0;
	
}; 
