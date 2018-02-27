#include "elev.h"
#include "eventmanager.h"
#include "lighthandler.h"
#include "queue.h"
#include "statemachine.h"
#include "timer.h"
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

	

    while (1) {

		eventcontroller_floor_indicator_light();


        // Change direction when we reach top/bottom floor
        if (elev_get_floor_sensor_signal() == N_FLOORS - 1) {
            elev_set_motor_direction(DIRN_DOWN);
        } else if (elev_get_floor_sensor_signal() == 0) {
            elev_set_motor_direction(DIRN_UP);
        }

        // Stop elevator and exit program if the stop button is pressed
        if (elev_get_stop_signal()) {
            elev_set_motor_direction(DIRN_STOP);
            break;
        }
    }

    
    
    /*
     
     If-setning som stopper basert på om statemachine-funksjonen statemachine_... returnerer 1 eller 0. Setter i gang timer.
     
     */
    
    
    /*
     
     
     
     */
    return 0;
}
