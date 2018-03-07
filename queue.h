#ifndef queue_h
#define queue_h

#include <stdio.h>
#include "elev.h"
#include "statemachine.h"

struct Queue {
    int floor_queue[N_FLOORS];
    int up_queue[N_FLOORS];
    int down_queue[N_FLOORS];
};

void queue_initialize(struct Queue* order_list);
void queue_update_up_down_queues(struct Queue* order_list, struct State* statemachine);
void queue_add_to_floor_queue(struct Queue* order_list, int floor);
void queue_update_floor_queue(struct Queue* order_list, struct State* statemachine);
void queue_delete_from_floor_queue(struct Queue* order_list, int floor);

#endif /* queue_h */
