#include "lighthandler.h"

//Setter lysene i samsvar med statemachins current position
//i en while i main, vil etasje 1 lyse til etasje 2 registreres? Usikker på det. 
//forstår ikke helt hva som menes i elev.h på denne. 

void eventcontroller_floor_indicator_light(struct State *state)
{
	switch (state->current_position) {
	
	case(0): elev_set_floor_indicator(0); break; //1st floor
	case(1): elev_set_floor_indicator(1); break;//2st floor
	case(2): elev_set_floor_indicator(2); break;//3st floor
	case(3): elev_set_floor_indicator(3); break;//4st floor
	
	case(-1): return; //Gjør ingenting om heisen er mellom to etasjer.
	//må vi ha default

	}
}

//Kan bruke retur verdien fra funksjonen over, og skru det av når den er i etasjen over
//vil lyse da lyse selv om current_position er -1? 
//det var tanken bak funksjonen, men vet ikke om det fungerer
//avhenger av hva elev_set_floor_indicator returnerer om vi trenger denne eller ikke
/*
void eventcontroller_inside_elevator_light_off(int floor_light) {
	if ((state->current_position == floor_light + 1) && (state->current_position != -1)) {
		elev_set_button_lamp(BUTTON_COMMAND, floor_light, 0);
		return;		
	}
}
*/

void eventcontroller_door_lamp(struct State *state)
{
	switch (state->is_door_open) {
	case(1): elev_set_door_lamp(1); break;
	case(0): elev_set_door_lamp(0); break;
	}
}

void eventcontroller_stop_lamp(struct State *state)
{
	switch (state->is_stop_activ) {
	case(1): elev_set_stop_lamp(1); break;
	case(0): elev_set_stop_lamp(0); break;
	}
}

void eventcontroller_order_light(Order * order, State * state)
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





