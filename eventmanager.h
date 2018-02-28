#ifndef __INCLUDE_EVENTMANAGER_H__
#define __INCLUDE_EVENTMANAGER_H__

#pragma once

#include <stdio.h>
#include "queue.h"
#include "elev.h"
#include "statemachine.h"
#include "timer.h"


void eventmanager_stop_elevator (struct State* state);
void eventmanager_floor_indicator_light(struct State* state);

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
//Headerfil hvor man kan bestemme lysene etc.


//Lys etter heisens posisjon på/av
//void eventmanager_inside_elevator_light_off(int floor_light);


//Dørlys på/av, bruker statemachin is_door_open
//void eventmanager_door_lamp(struct State* state);

//Stoplys på/av, avhenger av statemachin is_stop_activ
//void eventmanager_stop_lamp(struct State* state);

//Setter bestillinglys på/av
//void eventmanager_order_light(struct Order* order, struct State* state);



#endif
