#include "lighthandler.h"

void lighthandler_floor_indicator_light (struct State* statemachine)
{
    elev_set_floor_indicator(statemachine->current_floor);
    
}


void lighthandler_update_lights(struct Queue* order_list, struct State* statemachine)
{
    for (int floor = 0; floor < N_FLOORS; floor++)
    {
        int up_light = 0;
        int down_light = 0;
        
        if (floor != 3)
            up_light = order_list->up_queue[floor];
        
        else
            up_light = 0;
        
        
        if (floor != 0)
            down_light = order_list->down_queue[floor];
        
        else
            up_light = 0;
        
        
        if (floor != 3)
            elev_set_button_lamp(BUTTON_CALL_UP, floor, up_light);
        
        
        if (floor != 0)
            elev_set_button_lamp(BUTTON_CALL_DOWN, floor, down_light);
        
        
        
        for (int i = 0; i < N_FLOORS; i++)
        {
            if ((elev_get_button_signal(BUTTON_COMMAND, i) == 1) && (statemachine->current_position != i))
                elev_set_button_lamp(BUTTON_COMMAND, i, 1);

            else if (order_list->floor_queue[i] == -1) {
            	elev_set_button_lamp(BUTTON_COMMAND, statemachine->current_floor, 0);
        }

        	if (statemachine->current_state == EMERGENCY_STOP) {
        		for (int j = 0; j < N_FLOORS; j++) {
        			elev_set_button_lamp(BUTTON_COMMAND, i, 0);
        		}


        	}
 
        }


    }
}



