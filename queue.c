#include "queue.h"

// Erases all the orders from the queues
void queue_initialize (struct Queue* queue)
{
    for (int i = 0; i < N_FLOORS; i++)
    {
        queue->going_up_queue[i] = 0;
        queue->going_down_queue[i] = 0;
        queue->floor_target_queue[i] = 0; 
    }
    
}

// Checks if any buttons are pressed, places orders in the queue if true.
void queue_add_to_queue (struct Queue* queue)
{
    for (int i = 0; i < N_FLOORS; i++)
    {
        if (elev_get_button_signal(BUTTON_CALL_UP, i))
        {
            queue->going_up_queue[i] = 1;
           
        }
        
        if (elev_get_button_signal(BUTTON_CALL_DOWN, i))
        {
            queue->going_down_queue[i] = 1;
           
        }

	if (elev_get_button_signal(BUTTON_COMMAND, i))
        {
            queue->floor_target_queue[i] = 1;
            
        }
    }
    
}


// Deletes order when elevator arrives at floor
void queue_delete_from_queue (struct Queue* queue, struct State* state)
{
    
    if (state->current_position != -1)
    {
        queue->going_up_queue[state->current_position] = 0;

        queue->going_down_queue[state->current_position] = 0;
      
	queue->floor_target_queue[state->current_position] = 0;

    }
    
}



