#ifndef __INCLUDE_QUEUE_H__
#define __INCLUDE_QUEUE_H__

#include <stdio.h>
#include "elev.h"
#include "statemachine.h"

//#include "timer.h"

struct Queue {
int going_up_queue[N_FLOORS];
int going_down_queue[N_FLOORS];
int floor_target_queue[N_FLOORS];
};

void queue_initialize (struct Queue* queue);
void queue_add_to_up_and_down_queue (struct Queue* queue);
void queue_add_to_floor_target_queue (struct Queue* queue, struct State* state);
void queue_delete_from_up_and_down_queue (struct Queue* queue, struct State* state);
void queue_delete_from_floor_target_queue (struct Queue *queue, struct State *state);



#endif
