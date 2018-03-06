//
//  timer.c
//  statemachine
//
//  Created by Anastasia on 19.02.2018.
//  Copyright © 2018 Anastasia. All rights reserved.
//

#include "timer.h"



int timer_start_timer() {
	int time_now = time(NULL);
	return time_now;
}

int timer_time_is_up (int start_time) {
	if (time(NULL) > start_time + 3) 
		return 1;
	return 0;
}

