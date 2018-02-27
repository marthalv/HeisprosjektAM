#include <stdio.h>
#include "elev.h"
//#include "timer.h"
#include "channels.h"
#include "eventmanager.h"


struct State {
    int current_position;
    int ordered_floor; // Newest ordered floor
    //int is_door_open;
	// stopp_state?
	//enklere å håndtere situasjonen med en stop-state?
	//int is_stop_activ;
    elev_motor_direction_t direction;
};



void statemachine_set_current_state(struct State *state);
//void statemachin_set_ordered_floor(struct State *state);
//void statemachin_set_is_stop_activ(struct State *state);
//void statemachin_set_is_door_open(struct State *state);
void statemachine_initialize(struct State *state, struct Queue *queue);
int statemachine_check_for_possible_stop_elevator(struct Queue *queue, struct State *state);


/*
//print funksjoner for egen del
void statemachin_print_position(struct State *state);
void statemachine_print_ordered_floor(struct State *state);
void statemachin_print_dirn(struct State *state);
//Vet ikke helt om de under fungerer
void statemachin_print_door_state(struct State *state);
void statemachin_print_stop_state(struct State *state);
*/