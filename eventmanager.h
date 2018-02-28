#ifndef __INCLUDE_EVENTMANAGER_H__
#define __INCLUDE_EVENTMANAGER_H__
#include <stdio.h>
#include "queue.h"
#include "elev.h"
#include "statemachine.h"
//#include "timer.h"


//struct for order, lettere å sette lysene, analysere bestilling? 
//så kan vi bare bruker order i queue?
/*
struct Order {
	int floor;
	elev_button_type_t button;
};

*/

//void eventmanager_set_order(struct Order *order);

//void eventmanager_initialize (struct Queue *queue);

void eventmanager_stop_elevator (struct State *state);

#endif
