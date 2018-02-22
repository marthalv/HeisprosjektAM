#include <stdio.h>
#include "elev.h"
#include "timer.h"
#include "eventmanager.h"
#include "channels.h"


struct State {
    int current_position;
    int ordered_floor; // Newest ordered floor
    bool is_door_open;
    elev_motor_direction_t direction;
};
