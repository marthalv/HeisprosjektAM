#include "queue.h"

#include <stdio.h>


void queue_initialize(struct Queue* order_list)
{
    for (int floor = 0; floor < N_FLOORS; floor++)
    {
        order_list->up_queue[floor] = 0;
        order_list->down_queue[floor] = 0;
        order_list->floor_queue[floor] = -1;
    }
}


void queue_update_up_down_queues(struct Queue* order_list, struct State* statemachine)
{
    for (int floor = 0; floor < N_FLOORS; floor++)
    {
        if (statemachine->current_state == NORMAL_STOP && statemachine->current_position == floor) // Does not make a new order if we are already at that floor in NORMAL_STOP-state
            return;
        
        order_list->down_queue[floor] = elev_get_button_signal(BUTTON_CALL_DOWN, floor) || order_list->down_queue[floor];
        order_list->up_queue[floor] = elev_get_button_signal(BUTTON_CALL_UP, floor) || order_list->up_queue[floor];

    }
}


void queue_add_to_floor_queue(struct Queue* order_list, int floor)
{
    for (int i = 0; i < N_FLOORS; i++)
    {
        if (order_list->floor_queue[i] == floor) // If the requested floor is already in the queue, we don't execute the next for-loop
            return;
    }
    
    for (int q = 0; q < N_FLOORS; q++)
    {
        if (order_list->floor_queue[q] == -1) // If there is no order in index q, the requested floor is placed in index q
        {
            order_list->floor_queue[q] = floor;
            return;
        }
    }
}

void queue_update_floor_queue(struct Queue* order_list, struct State* statemachine)
{
    for (int floor = 0; floor < N_FLOORS; floor++)
    {
        if (elev_get_button_signal(BUTTON_COMMAND, floor) && (statemachine->current_position != floor))
            queue_add_to_floor_queue(order_list, floor);
    }
}



void queue_delete_from_floor_queue(struct Queue* order_list, int floor)
{
    int floor_found; // Floor_found equals 0 or 1
    int floor_index; // Floor_index indicates the index the floor to be deleted is in
    
    for (int i = 0; i < N_FLOORS; i++)
    {
        if (order_list->floor_queue[i] == floor)
        {
            floor_found = 1;
            floor_index = i;
            break;
        }
    }
    
    if (floor_found == 1)
    {
        for (int q = floor_index; q < (N_FLOORS - 1); q++)
        {
            order_list->floor_queue[q] = order_list->floor_queue[q + 1]; // Moves the orders forward in the queue
        }
    }
    
    order_list->floor_queue[N_FLOORS - 1] = -1; // Sets the last element in the queue to -1
}





