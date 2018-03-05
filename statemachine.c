#include "statemachine.h"

void statemachine_run (struct State* state, struct Queue* queue)
{
    
	if (elev_get_stop_signal()) // If the stop button is pressed
        state->run_state = EMERGENCY_STOP;
        //break; kan kun brukes i en loop

    queue_add_to_queue(queue, state);
    statemachine_set_current_state(state);
    
    eventmanager_floor_indicator_light(state);
    eventmanager_update_lights(queue, state);
    eventmanager_set_direction(state);
    


	switch (state->run_state) {
		case (IDLE):
        {
            
            if (queue->floor_target_queue[0] != -1)
            {
                state->run_state = EXECUTE;
                break;
            }
            
            for (int floor = 0; floor < N_FLOORS; floor++)
            {
                if (queue->going_up_queue[floor] || queue->going_down_queue[floor])
                    state->run_state = EXECUTE;
            }
            
            if (statemachine_check_for_stop(state, queue) == 1)
            {
                state->direction = DIRN_STOP;
                queue_delete_from_queue(queue, state);
                break;
                
                if (state->current_position != -1)
                    elev_set_button_lamp(BUTTON_COMMAND, state->current_position, 0);
            }

        }
            
		case (EXECUTE):
        {
            /*
             
             Utfører bestillinger etter prioritert liste:
             - Første element i floor_target_queue utføres først
             - Skal stoppe i etasjer der det er bestillinger i samme retning som heisen kjører til første element i floor_target_queue
             - Slette bestillinger fra going_up_queue og going_down_queue når de er utført
                - Også når heisen ikke skal i samme retning, men stopper i en etasje der det er bestilt heis i "feil" retning
             - Slette bestillinger fra floor_target_queue
             
             Når bestilling er utført, gå over i STOP state
             
             */
        }
            
		case (NORMAL_STOP):
        {
            
			if (state->current_position == queue->floor_target_queue[0]) { //Deletes from the queue if position is at position given by index 0 in queue
				queue_delete_from_queue(queue, state);
			}

			state->direction = DIRN_STOP; //Sets state direction to stop
		    //Bør denne være her? 
			timer_start_periode(); //The time periode is started
			elev_set_door_open_lamp(1); //Activates lights

			if (timer_time_is_up() == 1) { //Cheks if the time periode is up

				elev_set_door_open_lamp(0); //Deactivates door lamp
				if (queue->floor_target_queue[0] != -1) {
					state->run_state == EXECUTE; //If more orders still in queue, returns to EXECUTE state
				}
				state->run_state == IDLE; //No more orderes, returns to IDLE state //If more orders still in queue, returns to EXECUTE state
			}
			break;

            /*
             Sette door_open_lamp til 1
             Stoppe i 3 sekunder (sett på timer)
             
             If-setning som setter run_state til:
                EXECUTE hvis det er flere bestillinger igjen
                IDLE hvis det ikke er flere bestillinger igjen
             
             */
        }

		case (EMERGENCY_STOP):
        {
            
			if (state->current_position != -1) // If it is at a floor, the door opens
				elev_set_door_open_lamp(1);
            
            elev_set_stop_lamp(1);
            elev_set_motor_direction(DIRN_STOP);
			queue_initialize(queue); // Deletes all orders while the run_state is EMERGENCY_STOP
	
			if (!elev_get_stop_signal())
            {
				elev_set_stop_lamp(0);
				elev_set_door_open_lamp(0);
				state->run_state = IDLE;
			}
        }
	}
}


// Sets the state of the elevator
void statemachine_set_current_state (struct State* state) {
	state->current_position = elev_get_floor_sensor_signal(); // Sets current position
    
	for (int i = 0; i < N_FLOORS; i++) { // Sets newest ordered floor
		if (elev_get_button_signal(BUTTON_COMMAND, i) == 1)
			state->ordered_floor = i;
	}	
}


// Makes sure that the elevator comes in a defined state after startup
void statemachine_initialize(struct State* state)
{
    
    // Ignores stop button and orders made while the elevator is between floors
    while (elev_get_floor_sensor_signal() == -1)
        elev_set_motor_direction(1);

    elev_set_motor_direction(0);

    statemachine_set_current_state(state);
    state->ordered_floor = -1;
    state->direction = DIRN_STOP;
    state->run_state = IDLE;
    
}


// FINN ET ANNET NAVN PÅ FUNKSJONEN
int statemachine_check_for_stop (struct State* state, struct Queue* queue)
{
    if (state->current_position == -1)
        return 0;
    
    if ((state->direction == DIRN_UP) && (queue->going_up_queue[state->current_position]))
        return 1;
    
    if ((state->direction == DIRN_DOWN) && (queue->going_down_queue[state->current_position]))
        return 1;
    
    for (int floor = 0; floor < N_FLOORS; floor++)
    {
        if ((queue->floor_target_queue[floor] == state->current_position) && (state->current_position != -1))
            return 1;
    }
    return 0;
}

