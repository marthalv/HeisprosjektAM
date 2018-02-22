#include "eventmanager.h"



void eventmanager_open_door () { // Opens door
    timer_reset();
    elev_set_door_open_lamp(1);
    state->is_door_open = 1;
}

void eventmanager_stop_elevator () {
    elev_set_motor_direction(DIRN_STOP);
    // Kan legge til skifting av retning før stopp hvis det funker dårlig (ref. oppgavetekst)
}











