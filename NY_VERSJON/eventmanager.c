#include "eventmanager.h"

void eventmanager_set_direction (struct State* state)
{
    if (state->direction == DIRN_STOP)
    	elev_set_motor_direction(DIRN_STOP);

    if (state->direction == DIRN_UP)
        elev_set_motor_direction(DIRN_UP);

    if (state->direction == DIRN_DOWN)
        elev_set_motor_direction(DIRN_DOWN);

    // Kan legge til skifting av retning før stopp hvis det funker dårlig (ref. oppgavetekst)
}


// Sets the floor indicator lights based on which position the elevator is in
void eventmanager_floor_indicator_light (struct State* state)
{
    // FUNKER DETTE HER ISTEDENFOR SWITCH??
    if (state->current_position != -1)
        elev_set_floor_indicator(state->current_position);
    /*
    switch (state->current_position)
    {
        case(0): //1st floor
            elev_set_floor_indicator(0);
            break;
            
        case(1): //2nd floor
            elev_set_floor_indicator(1);
            break;
            
        case(2): //3rd floor
            elev_set_floor_indicator(2);
            break;
            
        case(3): //4th floor
            elev_set_floor_indicator(3);
            break;
            
        case(-1):
            return; // Does nothing while in between floors
            
    }
    */
    
}


// KAN DETTE GJØRES ENKLERE? SJEKK
void eventmanager_update_lights (struct Queue* queue, struct State* state)
{
    for (int floor = 0; floor < N_FLOORS; floor++)
    {
        // Sets up and down lights
        //SJEKK OM DETTE FUNGERER
        elev_set_button_lamp(BUTTON_CALL_UP, floor, queue->going_up_queue[floor]);
        elev_set_button_lamp(BUTTON_CALL_DOWN, floor, queue->going_down_queue[floor]);
        
        // Sets all floor lights to zero
        elev_set_button_lamp(BUTTON_COMMAND, floor, 0);
        
        // Sets floor light to 1 if there is a order for that floor and current_position is not that floor
        for (int i = 0; i < N_FLOORS; i++) {
            if (queue->floor_target_queue[i] == floor && state->current_position != floor)
                elev_set_button_lamp(BUTTON_COMMAND, floor, 1);
        }
        
        
    /*
    if (elev_get_button_signal(BUTTON_CALL_UP, floor) == 1) {
        elev_set_button_lamp(BUTTON_CALL_UP, floor, 1); // Skal vi ha denne funksjonaliteten i queue, eller burde vi ha den i lighthandler/eventmanager?
    }
    if (elev_get_button_signal(BUTTON_CALL_DOWN, floor) == 1) {
        elev_set_button_lamp(BUTTON_CALL_DOWN, floor, 1);
    }    
    if (elev_get_button_signal(BUTTON_COMMAND, floor) == 1) {
        elev_set_button_lamp(BUTTON_COMMAND, floor, 1);
    }

    //if (queue->floor_target_queue[floor] == state->current_position) {
	//elev_set_button_lamp(BUTTON_COMMAND, floor, 0);
    //} 
	}
   
    if ((queue->going_up_queue[state->current_position] == 0) && (state->current_position != -1)) {
	elev_set_button_lamp(BUTTON_CALL_UP, state->current_position, 0);
    }
    
    if ((queue->going_down_queue[state->current_position] == 0) && (state->current_position != -1)) {
	elev_set_button_lamp(BUTTON_CALL_DOWN, state->current_position, 0);
     */
        
    }
}
    

 

 
 
















