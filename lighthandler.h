#pragma once
#include "eventmanager.h"
#include "io.h"
#include "queue.h"
#include "statemachine.h"
#include "timer.h"
#include "elev.h"
#include "channels.h"


//Headerfil hvor man kan bestemme lysene etc. 
//endre alle navn, men kanskje de kan v�re i en annen header?


//Lys etter heisens posisjon p�/av
void eventcontroller_floor_indicator_light();
//void eventcontroller_inside_elevator_light_off(int floor_light);


/*
//D�rlys p�/av, bruker statemachin is_door_open
void eventcontroller_door_lamp(struct State *state);

//Stoplys p�/av, avhenger av statemachin is_stop_activ
void eventcontroller_stop_lamp(struct State *state);

//Setter bestillinglys p�/av
void eventcontroller_order_light(struct Order *order, struct State *state);
*/



