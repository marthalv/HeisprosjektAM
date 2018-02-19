#include "eventmanager.h"


void eventmanager_initialize (struct Queue *queue) { // Erases all the orders from the queues and initializes
    for (int i = 0; i < FLOORS; i++) {
        queue->going_up_queue[i] = 0;
        queue->going_down_queue[i] = 0;
        queue->floor_target_queue[i] = 0;
    }
}

void eventmanager_create_event (struct Queue *queue) { // Checks if any buttons are pressed, places orders in the queue if true
    for (int i = 0; i < FLOORS; i++) {
        if (elev_get_button_signal(BUTTON_CALL_UP, i)) {
            queue->going_up_queue[i] = 1;
        }
        else if (elev_get_button_signal(BUTTON_CALL_DOWN, i)) {
            queue->going_down_queue[i] = 1;
        }
        else if (elev_get_button_signal(BUTTON_COMMAND, i)) {
            queue->floor_target_queue[i] = 1;
        }
    }
}

void eventmanager_open_door_3_sec () {
    timer_reset();
    elev_set_door_open_lamp(1);
    while (1) {
        if (timer_time_is_up() == 1) {
            elev_set_door_open_lamp(0);
            break;
        }
    }
}

void eventmanager_stop_elevator (int ordered_floor) {
    if (elev_get_floor_sensor_signal() == ordered_floor) {
        elev_set_motor_direction(DIRN_STOP);
        eventmanager_open_door_3_sec();
    }
}

void eventmanager_completed_event (struct Queue *queue, struct State *state, int ordered_floor) {
    if (state->direction == DIRN_UP) {
        queue->going_up_queue[ordered_floor] = 0;
    }
    else if (state->direction == DIRN_DOWN) {
        queue->going_down_queue[ordered_floor] = 0;
    }
    else if (state->direction == DIRN_STOP) {
        queue->floor_target_queue[ordered_floor] = 0;
    }
}

void eventmanager_handle_event (struct Queue *queue, struct State *state) {
    if (state->direction == DIRN_UP) {
            for (int i = 0; i < FLOORS; i++) {
                if (((state->current_floor) < i) && (queue->going_up_queue[i])) { // Usikker på logikk, sjekk på lab
                    eventmanager_stop_elevator(i);
                    eventmanager_completed_event(queue, state, i);
            }
        }
    }
}




