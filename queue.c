#include "queue.h"

void queue_initialize (struct Queue* queue) { // Erases all the orders from the queues
    for (int i = 0; i < N_FLOORS; i++) {
        queue->going_up_queue[i] = 0;
        queue->going_down_queue[i] = 0;
        queue->floor_target_queue[i] = -1; // -1 means no order in this position
    }
}

void queue_add_to_up_and_down_queue (struct Queue* queue) { // Checks if any buttons are pressed, places orders in the queue if true. Also sets the lamps
    for (int i = 0; i < N_FLOORS; i++) {
        if (elev_get_button_signal(BUTTON_CALL_UP, i)) {
            queue->going_up_queue[i] = 1;
            elev_set_button_lamp(BUTTON_CALL_UP, i, 1); // Skal vi ha denne funksjonaliteten i queue, eller burde vi ha den i lighthandler/eventmanager?
        }
        
        if (elev_get_button_signal(BUTTON_CALL_DOWN, i)) {
            queue->going_down_queue[i] = 1;
            elev_set_button_lamp(BUTTON_CALL_DOWN, i, 1);
        }
    }
}

void queue_add_to_floor_target_queue (struct Queue* queue, struct State* state) { // Adds orders that are made inside the elevator
    for (int i = 0; i < N_FLOORS; i++) {
        if (queue->floor_target_queue[i] == state->ordered_floor) {
            return;
        }
        
        if (queue->floor_target_queue[i] == -1) {
            queue->floor_target_queue[i] = state->ordered_floor;
            elev_set_button_lamp(BUTTON_COMMAND, state->ordered_floor, 1);
            return;
        }
    }
}

void queue_delete_from_up_and_down_queue (struct Queue* queue, struct State* state) { // Deletes order when elevator arrives at floor
    if (state->current_position != -1) {
        queue->going_up_queue[state->current_position] = 0;
        elev_set_button_lamp(BUTTON_CALL_UP, state->current_position, 0);
        
        queue->going_down_queue[state->current_position] = 0;
        elev_set_button_lamp(BUTTON_CALL_DOWN, state->current_position,0);
    }
}

void queue_delete_from_floor_target_queue (struct Queue *queue, struct State *state) // lys nr 1 slukkes ikke om ingen andre lys er påtrykt
{ 
    
    if (state->current_position != -1) {
        for (int i = 0; i < N_FLOORS; i++) {
		if (queue->floor_target_queue[i] == state->current_position) {
			//queue->floor_target_queue[i] = -1;
        		elev_set_button_lamp(BUTTON_COMMAND, state->current_position, 0);
		}
	   }
	}

    for (int i = 0; i < N_FLOORS-1; i++) {
        if (queue->floor_target_queue[i] == -1) {
            queue->floor_target_queue[i] = queue->floor_target_queue[i+1];
            queue->floor_target_queue[i+1] = -1;
        }
    }

}




