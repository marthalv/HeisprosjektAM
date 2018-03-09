#ifndef queue_h
#define queue_h

#include <stdio.h>
#include "elev.h"
#include "statemachine.h"

struct Queue {
    int floor_queue[N_FLOORS]; // The indexes takes values between 0-3, making a prioritized queue based on which order was made first. -1 means no order
    int up_queue[N_FLOORS]; // The index corresponds to the ordered floor. 0 means no order in this floor, 1 means there is an order in this floor
    int down_queue[N_FLOORS]; // The index corresponds to the ordered floor. 0 means no order in this floor, 1 means there is an order in this floor
};

// Deletes all orders in all the queues
void queue_initialize(struct Queue* order_list);

// Updates the up and down queues with orders from the floor panel
void queue_update_up_down_queues(struct Queue* order_list, struct State* statemachine);

// Adds floor to back of the floor queue, making a prioritized list based on which button was pressed first
void queue_add_to_floor_queue(struct Queue* order_list, int floor);

// Updates the floor queue with orders from the elevator panel
void queue_update_floor_queue(struct Queue* order_list, struct State* statemachine);

// Moves the orders forward in the queue, deleting floor from the queue
void queue_delete_from_floor_queue(struct Queue* order_list, int floor);

#endif /* queue_h */
