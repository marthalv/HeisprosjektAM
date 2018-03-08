#ifndef statemachine_h
#define statemachine_h

#include <stdio.h>
#include "elev.h"
#include "queue.h"
#include "eventmanager.h"
#include <time.h>

typedef enum machine_states {IDLE, EXECUTE, NORMAL_STOP, EMERGENCY_STOP} machine_state;

struct State {
    int current_floor; // Takes values between 0-3
    int current_position; // -1 if between floors, 0-3 if at a floor
    machine_state current_state; // Describes the current state the elevator is in
    elev_motor_direction_t current_direction; // The current direction the elevator drives
};

void statemachine_set_current_state (struct State* statemachine);
void statemachine_initialize(struct State* statemachine);
int statemachine_check_for_stop (struct State* statemachine, struct Queue* order_list);
void statemachine_stop (struct State* statemachine, struct Queue* order_list, int wait_time);

#endif /* statemachine_h */
