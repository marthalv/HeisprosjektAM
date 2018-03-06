#include "statemachine.h"

void statemachine_run (struct State* state, struct Queue* queue, int timer_start)
{
    while (1) {
        
        // Checks if we want to exit the program
        scanf("%d", &exit);
        
        if (exit)
            elev_set_motor_direction(DIRN_STOP);
        break;
        
        
        if (elev_get_stop_signal() == 1) {
            state->run_state = EMERGENCY_STOP;
            break;
        }
        
        else {

            statemachine_set_current_state(state);

            eventmanager_floor_indicator_light(state);
            eventmanager_update_lights(queue, state);

            queue_add_to_queue(queue);
        }

        switch (state->run_state) {

            case (IDLE):
            {
                if (elev_get_stop_signal() == 1) {
                    state->run_state = EMERGENCY_STOP;
                    break;
				
                }

			
                for (int floor = 0; floor < N_FLOORS; floor++) {
                    if ((queue->floor_target_queue[floor] == 1) || (queue->going_up_queue[floor] == 1) || (queue->going_down_queue[floor] == 1)) {

                        if (floor == state->current_position) {
                            queue_delete_from_queue(queue, state);
                            state->run_state = NORMAL_STOP;
                            break;
						
                        }

                        state->run_state = EXECUTE;
                        break;
					
                    }
                }
            }

            case (EXECUTE):
            {
                
                if (statemachine_check_for_stop(state, queue) == 1) {
                    queue_delete_from_queue(queue, state);
                    state->run_state = NORMAL_STOP;
                    break;
                }
                
                int next_floor = -1;
                

                for (int floor = 0; floor < N_FLOORS; floor++) {
                    if ((queue->floor_target_queue[floor] == 1)) && (state->current_position != -1)) {
                            next_floor = floor;
                    }
                    
                    if (((queue->going_up_queue[floor] == 1) || (queue->going_down_queue[floor])) && !(queue_is_order_in_floor_queue(queue))) {
                        next_floor = floor;
                    }
                }
                

                
                if (next_floor != -1) {
                    for (int floor = 0; floor < N_FLOORS; floor++) {
                        if ((next_floor > state->current_position) && (queue->floor_target_queue[next_floor] == 1)) {
                            elev_set_motor_direction(DIRN_UP);
                        }
                        if ((next_floor < state->current_position) && queue->floor_target_queue[next_floor] == 1)) {
                            elev_set_motor_direction(DIRN_DOWN);
                        }
                    }
                }
                
                
                if (next_floor == -1) {
                    state->run_state = IDLE;
                    break;
                }
                
                /*
                 
                 Vi vil at følgende skal skje:
                 - Hvis vi har bestillinger i floor_target_queue, skal den utføre den nærmeste bestillingen først
                        - Alle bestillinger på veien til floor_target_queue[i] som er i samme retning skal utføres
                 - Hvis vi ikke har bestillinger i floor_target_queue, skal den utføre eventuelle bestillinger i going_up_queue og going_down_queue
                    - Hvis to stykker trykkes samtidig, skal den som er nærmest ekspederes først
                        - Hvis de er like nærme, skal den som er øverst ekspederes først
                 - Hvis vi kommer til en etasje det er bestilt til, skal vi gå i NORMAL_STOP
                 
                 
                 */
                
            }

            case (NORMAL_STOP):
            {
                elev_set_motor_direction(DIRN_STOP);
                elev_set_door_open_lamp(1);

                timer_start += timer_start_timer();

                if (timer_time_is_up (timer_start) == 1) {
                    elev_set_door_open_lamp(0);
                    state->run_state = IDLE;
                    break;
                }
						

            }

            case (EMERGENCY_STOP):
            {

                elev_set_motor_direction(DIRN_STOP);
                elev_set_stop_lamp(1);


                while (elev_get_stop_signal() == 1) {
                    queue_initialize(queue);

                    if (state->current_position != -1) {
                        elev_set_door_open_lamp(1);
                    }
                }

                elev_set_stop_lamp(0);

                if (state->current_position != -1) {
                    state->run_state = NORMAL_STOP;
                    break;
                }

                state->run_state = IDLE;
                break;

                }
        }
    }
}


// Sets the state of the elevator
void statemachine_set_current_state (struct State* state) {
	state->current_position = elev_get_floor_sensor_signal(); // Sets current position

	if (state->current_position != -1) 
		state->last_floor = state->current_position; // Sets last floor
}





// Makes sure that the elevator comes in a defined state after startup
void statemachine_initialize(struct State* state)
{
    
    // Ignores stop button and orders made while the elevator is between floors
    while (elev_get_floor_sensor_signal() == -1)
    {
        elev_set_motor_direction(DIRN_UP);
    }

    elev_set_motor_direction(DIRN_STOP);
    state->direction = DIRN_STOP;
    state->run_state = IDLE;
    statemachine_set_current_state(state);

}



int statemachine_check_for_stop (struct State* state, struct Queue* queue)
{
    if (state->current_position == -1)
        return 0;

    if (queue->floor_target_queue[state->current_position] == 1)
       return 1;
   
    if ((state->direction == DIRN_UP) && (queue->going_up_queue[state->current_position]))
       	 return 1;
    
    if ((state->direction == DIRN_DOWN) && (queue->going_down_queue[state->current_position]))
        return 1;
    
    
    int is_order = 0; 

    for (int floor = 0; floor < N_FLOORS; floor++) {
        if (queue->floor_target_queue[floor] == 1) {
		is_order = 1;
		break;
        }
    }

    if (is_order == 0) && (queue->going_up_queue[state->current_position] == 1))
	return 1;

    if (is_order == 0) && (queue->going_down_queue[state->current_position] == 1))
	return 1;

}



