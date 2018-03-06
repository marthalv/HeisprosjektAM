#ifndef __INCLUDE_STATEMACHINE_H__
#define __INCLUDE_STATEMACHINE_H__

#pragma once

#include <stdio.h>
#include "elev.h"
#include "timer.h"
#include "channels.h"
#include "queue.h"
#include "eventmanager.h"

typedef enum current_state {IDLE, EXECUTE, NORMAL_STOP, EMERGENCY_STOP} current_state; 

struct State
{
    int current_position; // The position the elevator is in right now, has values from 0-3, -1 if it is in between floors
    int last_floor; // The last floor the sensor detected. Has values from 0-3, if it is in between floors it has the last floor it was at.
    elev_motor_direction_t direction; // The direction the elevator moves in right now
    current_state run_state; // The state the elevator is in right now
    
};

void statemachine_set_current_state(struct State* state);
void statemachine_initialize(struct State* state);
int statemachine_check_for_stop(struct State* state, struct Queue* queue);
void statemachine_run (struct State* state, struct Queue* queue, int timer_start);



#endif
