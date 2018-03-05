#ifndef __INCLUDE_STATEMACHINE_H__
#define __INCLUDE_STATEMACHINE_H__

#pragma once

#include <stdio.h>
#include "elev.h"
#include "timer.h"
#include "channels.h"
#include "queue.h"
#include "eventmanager.h"

typedef enum possible_states {IDLE, EXECUTE, NORMAL_STOP, EMERGENCY_STOP} current_state;

struct State
{
    int current_position; // The position the elevator is in right now, has values from 0-3, -1 if it is in between floors
    int ordered_floor; // Newest ordered floor
    elev_motor_direction_t direction; // The direction the elevator moves in right now
    current_state run_state; // The state the elevator is in right now

};


void statemachine_set_current_state(struct State* state);
void statemachine_initialize(struct State* state);
int statemachine_check_for_possible_stop_elevator(struct State* state, struct Queue* queue);


#endif
