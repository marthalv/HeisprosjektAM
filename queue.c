#include "queue.h"

#include <stdio.h>


void queue_initialize(struct Queue* order_list)
{
    for (int floor = 0; floor < N_FLOORS; floor++) {
        order_list->up_queue[floor] = 0;
        order_list->down_queue[floor] = 0;
        order_list->floor_queue[floor] = -1;
    }
}


void queue_update_up_down_queues(struct Queue* order_list, struct State* statemachine)
{
    for (int floor = 0; floor < N_FLOORS; floor++)
    {
        int button_up = elev_get_button_signal(BUTTON_CALL_UP, floor);
        int button_down = button_down = elev_get_button_signal(BUTTON_CALL_DOWN, floor);
        
        if (!(statemachine->current_state == NORMAL_STOP &&  statemachine->current_position == floor))
        {
            order_list->down_queue[floor] = button_up || order_list->down_queue[floor];
            order_list->up_queue[floor] = button_down || order_list->up_queue[floor];
        }
    }
}


void queue_add_to_floor_queue(struct Queue* order_list, int floor)
{
    for (int i = 0; i < N_FLOORS; i++) {
        if (order_list->floor_queue[i] == floor)
            return;
    }
    
    for (int j = 0; j < N_FLOORS; j++) {
        if (order_list->floor_queue[j] == -1)
        {
            order_list->floor_queue[j] = floor;
            return;
        }
    }
}

void queue_update_floor_queue(struct Queue* order_list, struct State* statemachine)
{
    for (int floor = 0; floor < 4; floor++)
    {
        if (elev_get_button_signal(BUTTON_COMMAND, floor) && statemachine->current_position != floor)
            queue_add_to_floor_queue(order_list, floor);
    }
}


void queue_delete_from_floor_queue(struct Queue* order_list, int floor) {
    for (int j = 0; j < N_FLOORS-1; j++)
    {
        if (order_list->floor_queue[j] == floor)
        {
            order_list->floor_queue[3] = -1;
            for (int i = j; j < 3; j++)
            {
                if (order_list->floor_queue[i+1] == -1)
                {
                    order_list->floor_queue[i] = -1;
                    break;
                }
                order_list->floor_queue[i] = order_list->floor_queue[i+1];
            }
            break;
        }
    }
}




