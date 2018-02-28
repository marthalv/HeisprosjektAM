#include "elev.h"
#include "timer.h"
#include "lighthandler.h"
#include "queue.h"
#include "statemachine.h"
#include "eventmanager.h"
#include "channels.h"
#include "io.h"
#include <stdio.h>


int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    printf("Press STOP button to stop elevator and exit program.\n");

    elev_set_motor_direction(DIRN_UP);
    struct State state_1;
    struct Queue queue_1;
    
    state_1.direction = DIRN_UP;

    queue_initialize(&queue_1); // Deletes all previous orders from the queues

    statemachine_initialize(&state_1); // Makes sure that the elevator comes in a defined state
    
   

    while (1) {
	
	if (statemachine_check_for_possible_stop_elevator(&state_1, &queue_1) == 1) {
		eventmanager_stop_elevator(&state_1);
		timer_reset();
	}

        statemachine_set_current_state(&state_1);
        eventcontroller_floor_indicator_light(&state_1);
        //statemachine_set_ordered_floor(&state_1);
	


        // Change direction when we reach top/bottom floor
        if (elev_get_floor_sensor_signal() == N_FLOORS - 1) {
            elev_set_motor_direction(DIRN_DOWN);
        } else if (elev_get_floor_sensor_signal() == 0) {
            elev_set_motor_direction(DIRN_UP);
        }

        // Stop elevator and exit program if the stop button is pressed
        if (elev_get_stop_signal()) {
		if (state->current_position != -1) {
			elev_set_door_open_lamp(1);
		}

	    elev_set_stop_lamp(1);
            // elev_set_motor_direction(DIRN_STOP);  // HA DENNE I SWITCH I statemachine_run
            state->run_state = EMERGENCY_STOP;
            break;
        }
	

	queue_add_to_up_and_down_queue(&queue_1);
	queue_add_to_floor_target_queue(&queue_1, &state_1);
	queue_delete_from_up_and_down_queue(&queue_1, &state_1);
	queue_delete_from_floor_target_queue(&queue_1, &state_1);
        

    }


    
    
    /*
     
     If-setning som stopper basert på om statemachine-funksjonen statemachine_... returnerer 1 eller 0. Setter i gang timer.
     
     */
    
    
    /*
     
     
     
     */
    return 0;
}
