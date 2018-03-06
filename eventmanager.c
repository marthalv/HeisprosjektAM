#include "eventmanager.h"

void eventmanager_set_direction (struct State* state)
{
    if (state->direction == DIRN_STOP)
    	elev_set_motor_direction(DIRN_STOP);

    if (state->direction == DIRN_UP)
	elev_set_motor_direction(DIRN_UP);

    if (state->direction == DIRN_DOWN)
	elev_set_motor_direction(DIRN_DOWN);

}


// Sets the floor indicator lights based on which position the elevator is in
void eventmanager_floor_indicator_light (struct State* state)
{
    
  if (state->current_position != -1)
        elev_set_floor_indicator(state->current_position);
    
}


// KAN DETTE GJØRES ENKLERE? SJEKK
void eventmanager_update_lights (struct Queue *queue, struct State *state)
{
    for (int floor = 0; floor < N_FLOORS; floor++)
    {

    //Light on
    	if (elev_get_button_signal(BUTTON_CALL_UP, floor) == 1) {
		elev_set_button_lamp(BUTTON_CALL_UP, floor, 1); 
    	}
    	if (elev_get_button_signal(BUTTON_CALL_DOWN, floor) == 1) {
		elev_set_button_lamp(BUTTON_CALL_DOWN, floor, 1);
    	}    
   	if (elev_get_button_signal(BUTTON_COMMAND, floor) == 1) {
		elev_set_button_lamp(BUTTON_COMMAND, floor, 1);
    	}

   //Light off
    	if (queue->going_up_queue[floor] == 0) {
		elev_set_button_lamp(BUTTON_CALL_UP, floor, 0);
    	}
    
    	if (queue->going_down_queue[floor] == 0) {
		elev_set_button_lamp(BUTTON_CALL_DOWN, floor, 0);
    	}
    
    	if (queue->floor_target_queue[floor] == 0) {
		elev_set_button_lamp(BUTTON_COMMAND, floor, 0);
    	}
    }
}
    

 

 
 
















