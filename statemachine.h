#ifndef __INCLUDE_STATEMACHINE_H__
#define __INCLUDE_STATEMACHINE_H__

#pragma once

#include <stdio.h>
#include "elev.h"
#include "timer.h"
#include "channels.h"
#include "queue.h"

enum current_state {IDLE, EXECUTE, NORMAL_STOP, EMERGENCY_STOP}; // Sp�r studass om konvensjon for ENUM-navngiving

struct State
{
    int current_position; // The position the elevator is in right now, has values from 0-3, -1 if it is in between floors
    int ordered_floor; // Newest ordered floor
    elev_motor_direction_t direction; // The direction the elevator moves in right now
    current_state run_state; // The state the elevator is in right now
    
    //int is_door_open;
    //int is_stop_active;
};


void statemachine_set_current_state(struct State* state);
void statemachine_initialize(struct State* state);
int statemachine_check_for_possible_stop_elevator(struct State* state, struct Queue* queue);

//void statemachine_set_ordered_floor(struct State* state);
//void statemachine_set_is_stop_active(struct State* state);
//void statemachine_set_is_door_open(struct State* state);


// PR�V � TESTE DISSE MANDAG 5. MARS
/*
//print funksjoner for egen del
void statemachine_print_position(struct State *state);
void statemachine_print_ordered_floor(struct State *state);
void statemachine_print_dirn(struct State *state);
 
//Vet ikke helt om de under fungerer
void statemachine_print_door_state(struct State *state);
void statemachine_print_stop_state(struct State *state);
*/

#endif
