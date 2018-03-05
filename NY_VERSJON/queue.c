#include "queue.h"

// Erases all the orders from the queues
void queue_initialize (struct Queue* queue)
{
    for (int floor = 0; floor < N_FLOORS; floor++)
    {
        queue->going_up_queue[floor] = 0;
        queue->going_down_queue[floor] = 0;
        queue->floor_target_queue[floor] = -1; // -1 means no order in this position
    }
    
}

// Checks if any buttons are pressed, places orders in the queue if true
void queue_add_to_queue (struct Queue* queue, struct State* state)
{
    for (int floor = 0; floor < N_FLOORS; floor++)
    {
        if (!((state->run_state == NORMAL_STOP) && (state->current_position == floor))) // Sjekker at vi ikke har stoppet på etasjen som det bestilles til
        {
            if (elev_get_button_signal(BUTTON_CALL_UP, floor))
                queue->going_up_queue[floor] = 1;
                //elev_set_button_lamp(BUTTON_CALL_UP, i, 1);
            
            if (elev_get_button_signal(BUTTON_CALL_DOWN, floor))
                queue->going_down_queue[floor] = 1;
                //elev_set_button_lamp(BUTTON_CALL_DOWN, i, 1);
            
            if (queue->floor_target_queue[floor] == state->ordered_floor)
                return;
            
            if (queue->floor_target_queue[floor] == -1)
            {
                queue->floor_target_queue[floor] = state->ordered_floor;
                // elev_set_button_lamp(BUTTON_COMMAND, state->ordered_floor, 1);
                return;
            }
        }
    }
}


// Deletes order when elevator arrives at floor
void queue_delete_from_queue (struct Queue* queue, struct State* state)
{
    // Deletes from going_up_queue and going_down_queue
    if (state->current_position != -1)
    {
        queue->going_up_queue[state->current_position] = 0;
        // elev_set_button_lamp(BUTTON_CALL_UP, state->current_position, 0);
        
        queue->going_down_queue[state->current_position] = 0;
        // elev_set_button_lamp(BUTTON_CALL_DOWN, state->current_position,0);
    }
    
    // Deletes from floor_target_queue
    for (int i = 0; i < N_FLOORS - 1; i++) {
        if (queue->floor_target_queue[i] == state->current_position) {
            queue->floor_target_queue[N_FLOORS - 1] = -1;
            
            for (int j = i; j < N_FLOORS - 1; j++) {
                if (queue->floor_target_queue[j+1] == -1) {
                    queue->floor_target_queue[j] = -1;
                    
                    break;
                }
                queue->floor_target_queue[j] = queue->floor_target_queue[j+1];
            }
        }
    }
}


// Adds orders that are made inside the elevator
/*void queue_add_to_floor_target_queue (struct Queue* queue, struct State* state)
 {
 for (int i = 0; i < N_FLOORS; i++)
 {
 if (queue->floor_target_queue[i] == state->ordered_floor)
 return;
 
 if (queue->floor_target_queue[i] == -1) {
 queue->floor_target_queue[i] = state->ordered_floor;
 // elev_set_button_lamp(BUTTON_COMMAND, state->ordered_floor, 1);
 return;
 
	}
 }
}

// Må få denne til å funke. Sjekk koder på github
void queue_delete_from_floor_target_queue (struct Queue* queue, struct State* state) // lys nr 1 slukkes ikke om ingen andre lys er påtrykt
{ 
    for (int i = 0; i < N_FLOORS - 1; i++) {
        if (queue->floor_target_queue[i] == state->current_position) {
            queue->floor_target_queue[3] = -1;
            
            for (int j = i; j < N_FLOORS - 1; j++) {
                if (queue->floor_target_queue[j+1] == -1) {
                    queue->floor_target_queue[j] = -1;
                    
                    break;
                }
                queue->floor_target_queue[j] = queue->floor_target_queue[j+1];
            }
        }
    }
}
*/


