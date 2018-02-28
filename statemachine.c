#include "statemachine.h"

void statemachine_run (struct State* state, struct Queue* queue)
{
    
	if (elev_get_stop_signal()) // If the stop button is pressed
    {
        state->run_state = EMERGENCY_STOP;
        break;
    }

	else
    {
		queue_add_to_up_and_down_queue(queue);
		queue_add_to_floor_target_queue (queue, state);
		statemachine_set_current_state (state);
	}


	switch (state->run_state) {
		case (IDLE):
            
            if (queue->floor_target_queue[0] != -1)
                state->run_state = EXECUTE;
            
            if (state->current_position != 0)
            {
                // Sjekke om noen skal ned
            }
            
            if (state->current_position != (N_FLOORS - 1))
            {
                // Sjekke om noen skal opp
            }
            
            
            for (int floor = 0; floor < N_FLOORS; floor++)
            {
                if (queue->floor_target_queue[floor] != -1)
                    
            }
            
            
            /*
             
             Skal sjekke om det er noen bestillinger (iterere gjennom queuene)
             Når bestilling mottas: state->run_state = EXECUTE
             
             */

		case (EXECUTE):
            /*
             
             Utfører bestillinger etter prioritert liste:
             - Første element i floor_target_queue utføres først
             - Skal stoppe i etasjer der det er bestillinger i samme retning som heisen kjører til første element i floor_target_queue
             - Slette bestillinger fra going_up_queue og going_down_queue når de er utført
                - Også når heisen ikke skal i samme retning, men stopper i en etasje der det er bestilt heis i "feil" retning
             - Slette bestillinger fra floor_target_queue
             
             Når bestilling er utført, gå over i STOP state
             
             */

		case (STOP):
            /*
             
             Sette door_open_lamp til 1
             Stoppe i 3 sekunder (sett på timer)
             
             If-setning som setter run_state til:
                EXECUTE hvis det er flere bestillinger igjen
                IDLE hvis det ikke er flere bestillinger igjen
             
             */

		case (EMERGENCY_STOP):
            
			if (state->current_position != -1) // If it is at a floor, the door opens
				elev_set_door_open_lamp(1);
            
            elev_set_stop_lamp(1);
            elev_set_motor_direction(DIRN_STOP);
			queue_initialize(queue); // Deletes all orders while the run_state is EMERGENCY_STOP
	
			if (!elev_get_stop_signal())
            {
				elev_set_stop_lamp(0);
				elev_set_door_open_lamp(0); // Spør studass om krav til åpning av dør; skal den lukkes med en gang noen slipper stoppknappen? Eller vente?
				state->run_state = IDLE;
			}
	}
} 


// Sets the state of the elevator
void statemachine_set_current_state (struct State* state) {
	state->current_position = elev_get_floor_sensor_signal(); // Sets current position 
/*
	if (state->current_position == N_FLOORS - 1) { // ENDRE PÅ DENNE FUNKSJONEN (BASERT PÅ KØEN)
		state->direction = DIRN_DOWN;
	}
	
	if (state->current_position == 0) {
		state->direction = DIRN_UP; 
	}
*/
	for (int i = 0; i < N_FLOORS; i++) { // Sets ordered floor
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


// Makes sure that the elevator comes in a defined state after startup
void statemachine_initialize(struct State* state)
{
    
    // Ignores stop button and orders made while the elevator is between floors
    while (elev_get_floor_sensor_signal() == -1)
    {
        elev_set_motor_direction(1);
    }

    //elev_set_motor_direction(-1);
    elev_set_motor_direction(0);

    statemachine_set_current_state(state);
    state->ordered_floor = -1;
    
}


// FINN ET ANNET NAVN PÅ FUNKSJONEN
int statemachine_check_for_possible_stop_elevator (struct State* state, struct Queue* queue)
{
    if (state->current_position == -1)
        return 0;
    
    if ((state->direction == DIRN_UP) && (queue->going_up_queue[state->current_position]))
        return 1;
    
    if ((state->direction == DIRN_DOWN) && (queue->going_down_queue[state->current_position]))
        return 1;
    
    for (int i = 0; i < N_FLOORS; i++)
    {
        if ((queue->floor_target_queue[i] == state->current_position) && (state->current_position != -1))
        {
            queue->floor_target_queue[i] = -1; // Kan være i en annen funksjon, se an
            return 1;
        }
    }
    //return 0;
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
