#include "statemachine.h"

// Sets the state of the elevator
void statemachine_set_current_state (struct State* statemachine) {
    statemachine->current_position = elev_get_floor_sensor_signal(); // Sets current position
    
    if (statemachine->current_position != -1)
        statemachine->current_floor = statemachine->current_position; // Sets current floor
}


// Initializes statemachine
void statemachine_initialize(struct State* statemachine)
{
    // Ignores stop button and orders made while the elevator is between floors
    while (elev_get_floor_sensor_signal() == -1)
        elev_set_motor_direction(DIRN_UP);
    
    elev_set_motor_direction(DIRN_STOP);
    statemachine->current_direction = DIRN_STOP;
    statemachine->current_state = IDLE;
    
    statemachine_set_current_state(statemachine);
    
}

int statemachine_check_for_stop (struct State* statemachine, struct Queue* order_list)
{
    if (statemachine->current_position == -1)
        return 0;
    
    if (statemachine->current_floor == order_list->floor_queue[0] && statemachine->current_position == statemachine->current_floor)
        return 1;
    
    if ((statemachine->current_direction == DIRN_UP) && (order_list->up_queue[statemachine->current_position]))
        return 1;
    
    if ((statemachine->current_direction == DIRN_DOWN) && (order_list->down_queue[statemachine->current_position]))
        return 1;
    
    for (int floor = 0; floor < 4; floor++) {
        if (order_list->floor_queue[floor] == statemachine->current_floor)
            return 1;
    }
    
    return 0;
}
