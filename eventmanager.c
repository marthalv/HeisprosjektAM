#include "eventmanager.h"

void eventmanager_floor_indicator_light (struct State* statemachine)
{
    elev_set_floor_indicator(statemachine->current_floor);
    
}

void eventmanager_set_direction(struct Queue* order_list, struct State* statemachine)
{
    if (!(statemachine->current_state == NORMAL_STOP || statemachine->current_state == EXECUTE))
	return;
    elev_set_motor_direction(statemachine->current_direction);
  
}


void eventmanager_update_lights(struct Queue* order_list, struct State* statemachine)
{
    for (int floor = 0; floor < N_FLOORS; floor++)
    {
        int up_light = 0;
        int down_light = 0;
	
        if (floor != 3) {
            up_light = order_list->up_queue[floor];
        }
        else {
            up_light = 0;
        }

        if (floor != 0) {
            down_light = order_list->down_queue[floor];
        }
        else {
            up_light = 0;
        }

        if (floor != 3) {
            elev_set_button_lamp(BUTTON_CALL_UP, floor, up_light);
        }
	
        if (floor != 0) {
            elev_set_button_lamp(BUTTON_CALL_DOWN, floor, down_light);
        }

        elev_set_button_lamp(BUTTON_COMMAND, floor, 0);

        for (int i = 0; i < N_FLOORS; i++) {
            if (order_list->floor_queue[i] == floor && statemachine->current_position != floor) {
			elev_set_button_lamp(BUTTON_COMMAND, floor, 1);
            }
        }
	}
}


