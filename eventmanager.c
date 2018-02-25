#include "eventmanager.h"

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

void eventmanager_stop_elevator () {
    elev_set_motor_direction(DIRN_STOP);
    // Kan legge til skifting av retning før stopp hvis det funker dårlig (ref. oppgavetekst)
}












