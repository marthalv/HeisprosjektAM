#include <stdio.h>
#include "elev.h"
#include "timer.h"
#include "eventmanager.h"
#include "channels.h"

/* typedef enum
{IDLE, MOVING, STOP, EMERGENCY_STOP} statemachine_movement_state;
 */

struct State {
    int current_floor;
    elev_motor_direction_t direction;
    //statemachine_movement_state movement_state;
};

