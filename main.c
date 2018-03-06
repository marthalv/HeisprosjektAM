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


    struct State state_1;
    struct Queue queue_1;

    queue_initialize(&queue_1); // Deletes all previous orders from the queues

    statemachine_initialize(&state_1); // Makes sure that the elevator comes in a defined state
    
    int i = 0; 
    int time_now = 0;
    int exit = 0;
    printf("Press 1 to stop the elevator and exit the program");
    printf("%s", "\n");

    while (1)
    {
	i++;


	statemachine_run(&state_1, &queue_1, time_now); 
	
		

	scanf("%d", &exit);

	if (exit) 
		elev_set_motor_direction(DIRN_STOP);
		break;
    }


    return 0;
}


        
	
/*


	if (queue_1.floor_target_queue[0] != -1) { // DETTE FUNKER IKKE. PRØV Å FINNE UT HVA SOM ER FEIL

		if (queue_1.floor_target_queue[0] > state_1.current_position)
			elev_set_motor_direction(DIRN_STOP);
			elev_set_motor_direction(DIRN_UP);



		if (queue_1.floor_target_queue[0] < state_1.current_position)

			elev_set_motor_direction(DIRN_STOP);

			elev_set_motor_direction(DIRN_DOWN);



	}	

*/

/*
	if (statemachine_check_for_stop(&state_1, &queue_1) == 1)

        {

		elev_set_motor_direction(DIRN_UP);
		elev_set_motor_direction(DIRN_STOP);

		

		queue_delete_from_queue(&queue_1, &state_1);
		//time_now += timer_start_timer();
		

		
	}
*/

/*
	if (i % 100 == 0) {
		for (int j = 0; j < N_FLOORS; j++) {
			printf( "%d %s", j, "\n");
			printf( "%d %d %d %s", queue_1.floor_target_queue[j], queue_1.going_up_queue[j], queue_1.going_down_queue[j], "\n");
		}
	}



	// Change direction when we reach top/bottom floor
        if (elev_get_floor_sensor_signal() == N_FLOORS - 1)
            elev_set_motor_direction(DIRN_DOWN);
        
        else if (elev_get_floor_sensor_signal() == 0)
            elev_set_motor_direction(DIRN_UP);

*/ 
