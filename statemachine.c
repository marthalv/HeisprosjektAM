#include "statemachine.h"
void statemachine_set_current_state (struct State *state) {
    state->current_floor = elev_get_floor_sensor_signal();
}

void statemachine_initialize(struct State *state) { // Makes sure that the elevator comes in a defined state after startup
    // IGNORER STOPPKNAPP! Legg til funksjonalitet som ignorerer stoppknapp senere
    eventmanager_initialize(&queue);
    while (elev_get_floor_sensor_signal() == -1) {
        elev_set_motor_direction(-1);
        eventmanager_initialize(&queue);
    }
    elev_set_motor_direction(1);
    elev_set_motor_direction(0);
    
    timer_reset();
    elev_set_door_open_lamp(1);
    while (1) { // Bruk funksjon fra eventmanager.c
        if (timer_time_is_up() == 1) {
            elev_set_door_open_lamp(0);
            break;
        }
    }
    statemachine_set_current_state(state);
}




