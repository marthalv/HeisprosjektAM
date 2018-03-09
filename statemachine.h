#ifndef statemachine_h
#define statemachine_h

#include <stdio.h>
#include "elev.h"
#include "queue.h"
#include "eventmanager.h"
#include <time.h>

typedef enum states {IDLE, EXECUTE, NORMAL_STOP, EMERGENCY_STOP} machine_state; // The different states the elevator can be in

struct State
{
    int current_floor; // Takes values between 0-3
    int current_position; // -1 if between floors, 0-3 if at a floor
    machine_state current_state; // Describes the current state the elevator is in
    elev_motor_direction_t current_direction; // The current direction the elevator drives
};

// Sets current position
void statemachine_set_current_position (struct State* statemachine);

// Sets current floor
void statemachine_set_current_floor (struct State* statemachine);

// Makes sure the elevator comes in a defined state at startup
void statemachine_initialize(struct State* statemachine);

// Checks if stop conditions are fulfilled based on orders in the queues and the current direction the elevator moves in
int statemachine_check_for_stop (struct State* statemachine, struct Queue* order_list);

// Starts the timer and updates queues and lights while the elevator is in NORMAL_STOP-state and the door is open
void statemachine_stop (struct State* statemachine, struct Queue* order_list, int wait_time);

// Statemachine. The elevator moves between four different states based on what buttons are pressed
void statemachine_run (struct State* statemachine, struct Queue* order_list);

#endif /* statemachine_h */
