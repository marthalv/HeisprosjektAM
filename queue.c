#include "queue.h"

void queue_initialize (struct Queue *queue) { // Erases all the orders from the queues and initializes
    for (int i = 0; i < FLOORS; i++) {
        queue->going_up_queue[i] = 0;
        queue->going_down_queue[i] = 0;
        queue->floor_target_queue[i] = -1; // -1 means no order in this position
    }
}

void queue_add_to_up_and_down_queue (struct Queue *queue) { // Checks if any buttons are pressed, places orders in the queue if true
    for (int i = 0; i < FLOORS; i++) {
        if (elev_get_button_signal(BUTTON_CALL_UP, i)) {
            queue->going_up_queue[i] = 1;
        }
        else if (elev_get_button_signal(BUTTON_CALL_DOWN, i)) {
            queue->going_down_queue[i] = 1;
        }
    }
}

void queue_add_to_floor_target_queue (struct Queue *queue, struct State *state) {
    for (int i = 0; i < FLOORS; i++) {
        if (queue->floor_target_queue[i] == state->ordered_floor) {
            return;
        }
        if (queue->floor_target_queue[i] == -1) {
            queue->floor_taget_queue[i] = state->ordered_floor;
            return; // To save time by not iterating through the rest of the queue
        }
    }
}

void queue_delete_from_up_and_down_queue (struct Queue *queue, struct State *state) { // Legg inn funksjonalitet som gjør at ved stopp i en etasje, slettes alle bestillinger tilknyttet 
    if (state->direction == DIRN_UP) {
        queue->going_up_queue[state->ordered_floor] = 0;
    }
    else if (state->direction == DIRN_DOWN) {
        queue->going_down_queue[state->ordered_floor] = 0;
    }
}

void queue_delete_from_floor_target_queue (struct Queue *queue) {
    for (int i = 0; i < FLOORS-1; i++) {
        if (queue->floor_target_queue[i] == -1) {
            queue->floor_target_queue[i] = queue->floor_target_queue[i+1];
            queue->floor_target_queue[i+1] = -1;
        }
    }
}
