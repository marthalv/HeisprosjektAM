#include "eventmanager.h"

void eventmanager_stop_elevator (struct State* state)
{
    elev_set_motor_direction(0);
    state->direction == DIRN_STOP;
    // Kan legge til skifting av retning før stopp hvis det funker dårlig (ref. oppgavetekst)
}


// Sets the floor indicator lights based on which position the elevator is in
void eventmanager_floor_indicator_light (struct State* state)
{
    
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
    
}


// KAN DETTE GJØRES ENKLERE? SJEKK
void eventmanager_update_lights ()
{
    for (int floor = 0; floor < N_FLOORS; floor++)
    {
    if (elev_get_button_signal(BUTTON_CALL_UP, floor))
        elev_set_button_lamp(BUTTON_CALL_UP, floor, 1); // Skal vi ha denne funksjonaliteten i queue, eller burde vi ha den i lighthandler/eventmanager?
    
    if (elev_get_button_signal(BUTTON_CALL_DOWN, floor))
        elev_set_button_lamp(BUTTON_CALL_DOWN, floor, 1);
        
    if (elev_get_button_signal(BUTTON_COMMAND, floor))
        elev_set_button_lamp(BUTTON_COMMAND, floor, 1);
        
        
    else if (!elev_get_button_signal(BUTTON_CALL_UP, floor))
        elev_set_button_lamp(BUTTON_CALL_UP, floor, 0);
        
    else if (!elev_get_button_signal(BUTTON_CALL_DOWN, floor))
        elev_set_button_lamp(BUTTON_CALL_DOWN, floor, 0);
        
    else if (!elev_get_button_signal(BUTTON_COMMAND, floor))
        elev_set_button_lamp(BUTTON_COMMAND, floor, 0);
    }

}


/*
 //Kan vi bruke denne formen?
 void eventmanager_set_order(struct Order *order) {
	for (int i = 0, i < FLOORS, i++) {
 if (elev_get_button_signal(BUTTON_CALL_UP, i)) {
 order->button = BUTTON_CALL_UP;
 break;
 }
 if (elev_get_button_signal(BUTTON_CALL_DOWN, i)) {
 order->button = BUTTON_CALL_DOWN;
 break;
 }
 if (elev_get_button_signal(BUTTON_COMMAND, i)) {
 order->button = BUTTON_COMMAND;
 break;
 }
	}
	order->floor = i;
 }
 
 
 void eventmanager_open_door () { // Opens door
 timer_reset();
 // elev_set_door_open_lamp(1); gjøres i lys delen?
 state->is_door_open = 1;
 }
 */

/*
 //Kan bruke retur verdien fra funksjonen over, og skru det av nÂr den er i etasjen over
 //vil lyse da lyse selv om current_position er -1?
 //det var tanken bak funksjonen, men vet ikke om det fungerer
 //avhenger av hva elev_set_floor_indicator returnerer om vi trenger denne eller ikke
 /*
 void eventmanager_inside_elevator_light_off(int floor_light) {
	if ((state->current_position == floor_light + 1) && (state->current_position != -1)) {
 elev_set_button_lamp(BUTTON_COMMAND, floor_light, 0);
 return;
	}
 }
 
 
 void eventmanager_door_lamp(struct State *state)
 {
	switch (state->is_door_open) {
	case(1): elev_set_door_lamp(1); break;
	case(0): elev_set_door_lamp(0); break;
	}
 }
 */


/*
 void eventmanager_order_light(Order * order, State * state)
 {
	if (order->floor != state->current_position) {
 elev_set_button_lamp(order->button, order->floor, 1);
 return;
	}
	if (order->floor == state->current_position) {
 elev_set_button_lamp(order->button, order->floor, 0);
 return;
	}
 }
 */













