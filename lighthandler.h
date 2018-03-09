#ifndef lighthandler_h
#define lighthandler_h

#include <stdio.h>
#include "statemachine.h"
#include "queue.h"

// Updates the floor indicator light based on which floor the elevator was in last
void lighthandler_floor_indicator_light (struct State* statemachine);

// Updates all the lights in the floor panel and elevator panel based on orders in the queues
void lighthandler_update_lights(struct Queue* order_list, struct State* statemachine);

#endif /* lighthandler_h */
