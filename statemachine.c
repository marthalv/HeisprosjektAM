#include "statemachine.h"




void statemachine_set_current_state (struct State* state) {
    state->current_position = elev_get_floor_sensor_signal();
    // Burde vi legge til set_ordered_floor osv. i set_current_state? Evt. endre navn på denne funksjonen
	
}



void statemachine_set_ordered_floor(struct State* state) {
	for (int i = 0; i < N_FLOORS; i++){
	   if (elev_get_button_signal(BUTTON_COMMAND, i) == 1) {
		state->ordered_floor = i;
	 }
	}
}

/*
void statemachine_set_is_stop_active(struct State* state) {
	switch (elev_get_stop_signal()) {
        case(1): 
        state->is_stop_active = 1; break;
 
        case(0): 
        state->is_stop_active = 0; break;
	}
}

/*void statemachine_set_is_door_open(struct State* state)
{
	//.....
}
*/


void statemachine_initialize(struct State* state) { // Makes sure that the elevator comes in a defined
                                                                        // state after startup
    while (elev_get_floor_sensor_signal() == -1) { // Ignores stop button and orders made while the elevator is between floors
        elev_set_motor_direction(-1);
    }
    
    elev_set_motor_direction(1);
    elev_set_motor_direction(0);

    statemachine_set_current_state(state);
    state->ordered_floor = -1;
}

int statemachine_check_for_possible_stop_elevator (struct State* state, struct Queue* queue) { // FINN ET ANNET NAVN PÅ FUNKSJONEN
    if (state->current_position == -1)
        return 0;
    
    if (state->direction == DIRN_UP && queue->going_up_queue[state->current_position])
        return 1;
    
    if (state->direction == DIRN_DOWN && queue->going_down_queue[state->current_position])
        return 1;
    
    for (int i = 0; i < N_FLOORS; i++) {
        if ((queue->floor_target_queue[i] == state->current_position) && (state->current_position != -1)) {
            queue->floor_target_queue[i] = -1; // Kan være i en annen funksjon, se an
            return 1;
        }
    }
    return 0;
}

/*
void statemachine_print_position(struct State* state)
{
	printf("Current position: ", state->current_position, "/n");
	return;
}

void statemachine_print_ordered_floor(struct State* state)
{
	printf("Next ordered floor: ", state->ordered_floor, "/n");
	return;
}

void statemachine_print_dirn(struct State* state)
{
	if (state->direction == DIRN_UP) {
		printf("Direction: up");
		return;
	}
	if (state->direction == DIRN_DOWN) {
		printf("Direction: down");
		return;
	}
	if (state->direction == DIRN_STOP) {
		printf("Direction: no movement");
		return;
	}
}

void statemachine_print_door_state(struct State* state)
{
	if (state->is_door_open == 1) {
		printf("Door is open");
	}
	return;
}

void statemachin_print_stop_state(struct State* state)
{
	if (state->is_stop_active == 1) {
		printf("Emergency stop is active")
	}
	return;
}
*/
