#ifndef eventmanager_h
#define eventmanager_h

#include <stdio.h>
#include "statemachine.h"
#include "queue.h"

void eventmanager_floor_indicator_light (struct State* statemachine);
void eventmanager_set_direction(struct Queue* order_list, struct State* statemachine);
void eventmanager_update_lights(struct Queue* order_list, struct State* statemachine);

#endif /* eventmanager_h */
