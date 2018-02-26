#include "statemachine.h"


void statemachine_set_current_state (struct State *state) {
    state->current_position = elev_get_floor_sensor_signal(); // KANSKJE VI IKKE TRENGER DENNE FUNKSJONEN? Oppdatere statei andre funksjoner
	
}

//Hva returnerer elev_get_button_signal()?
void statemachin_set_ordered_floor(struct State *state) {
	//state->ordered_floor = 
}

void statemachin_set_is_stop_activ(struct State *state) {
	switch (elev_get_stop_signal()) {
	case(1): state->is_stop_activ = 1; break;
	case(0): state->is_stop_activ = 0; break;
	}
}

/*void statemachin_set_is_door_open(State * state)
{
	//.....
}
*/


void statemachine_initialize(struct State *state, struct Queue *queue) { // Makes sure that the elevator comes in a defined
                                                                        // state after startup
    while (elev_get_floor_sensor_signal() == -1) { // Ignores stop button and orders made while the elevator is between floors
        elev_set_motor_direction(-1);
    }
    
    elev_set_motor_direction(1);
    elev_set_motor_direction(0);

    // Spør studass om døra må åpnes etter initialisering (ref. punkt 13 på evalueringskriteriene)

    statemachine_set_current_state(state);
}

int statemachine_check_for_possible_stop_elevator (struct Queue *queue, struct State *state) { // FINN ET ANNET NAVN PÅ FUNKSJONEN
    
    if (state->current_position == -1)
        return 0;
    
    if (state->direction == DIRN_UP && queue->going_up_queue[state->current_position])
        return 1;
    
    if (state->direction == DIRN_DOWN && queue->going_down_queue[state->current_position])
        return 1;
    
    for (int i = 0; i < FLOORS; i++) {
        if ((queue->floor_target_queue[i] == state->current_position) && (state->current_position != -1)) {
            queue->floor_target_queue[i] = -1; // Kan være i en annen funksjon, se an
            return 1;
        }
    }
    return 0;
}

void statemachin_print_position(State * state)
{
	printf("Current position: ", state->current_position, "/n");
	return;
}

void statemachine_print_ordered_floor(State * state)
{
	printf("Next ordered floor: ", state->ordered_floor, "/n");
	return;
}

void statemachin_print_dirn(State * state)
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

void statemachin_print_door_state(State * state)
{
	if (state->is_door_open == true) {
		printf("Door is open");
	}
	return;
}

void statemachin_print_stop_state(State * state)
{
	if (state->is_stop_activ == true) {
		printf("Emergency stop is activ")
	}
	return;
}


