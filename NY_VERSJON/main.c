#include "elev.h"
#include "timer.h"
#include "queue.h"
#include "statemachine.h"
#include "eventmanager.h"
#include "channels.h"
#include "io.h"
#include <stdio.h>


int main()
{
    // Initialize hardware
    if (!elev_init())
    {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    printf("Press STOP button to stop elevator and exit program.\n");

    elev_set_motor_direction(DIRN_UP);
    struct State state_1;
    struct Queue queue_1;

    queue_initialize(&queue_1); // Deletes all previous orders from the queues

    statemachine_initialize(&state_1); // Makes sure that the elevator comes in a defined state
    
   

    while (1)
    {
        statemachine_set_current_state(&state_1);
        eventmanager_floor_indicator_light(&state_1);
        eventmanager_update_lights(&queue_1, &state_1);
        queue_add_to_queue(&queue_1, &state_1);
        
        if (statemachine_check_for_possible_stop_elevator(&state_1, &queue_1) == 1)
        {
            elev_set_motor_direction(DIRN_UP);
            elev_set_motor_direction(DIRN_STOP);
            queue_delete_from_queue(&queue_1, &state_1);

            if (state_1.current_position != -1)
                elev_set_button_lamp(BUTTON_COMMAND, state_1.current_position, 0);

		//timer_start_periode();
		//if (timer_time_is_up() != 0) 
		//	elev_set_motor_direction(DIRN_UP);

        }


        if (queue_1.floor_target_queue[0] != -1) { // DETTE FUNKER IKKE. PRØV Å FINNE UT HVA SOM ER FEIL

            if (queue_1.floor_target_queue[0] > state_1.current_position)
                elev_set_motor_direction(DIRN_STOP);
                elev_set_motor_direction(DIRN_UP);

            if (queue_1.floor_target_queue[0] < state_1.current_position)
                elev_set_motor_direction(DIRN_STOP);
            elev_set_motor_direction(DIRN_DOWN);

        }

	

        // Change direction when we reach top/bottom floor
        if (elev_get_floor_sensor_signal() == N_FLOORS - 1)
            elev_set_motor_direction(DIRN_DOWN);
        
        else if (elev_get_floor_sensor_signal() == 0)
            elev_set_motor_direction(DIRN_UP);



        // Stop elevator and exit program if the stop button is pressed
        // VI HAR DENNE FUNKSJONALITETEN I STATEMACHINE_RUN
        if (elev_get_stop_signal()) {
            //state->run_state = EMERGENCY_STOP;
            if (state_1.current_position != -1)
                elev_set_door_open_lamp(1);
             elev_set_stop_lamp(1);
             elev_set_motor_direction(DIRN_STOP);
             queue_initialize(&queue_1); // Deletes all orders while the run_state is EMERGENCY_STOP
            break;
        }
        
/*
        if (!elev_get_stop_signal())
        {
            elev_set_stop_lamp(0);
            elev_set_door_open_lamp(0);
            //state->run_state = IDLE;
        }
        // MÅ VI HA FUNKSJONALITET TIL Å STARTE DEN IGJEN ETTER EMERGENCY_STOP?
*/
    }

    return 0;
}
