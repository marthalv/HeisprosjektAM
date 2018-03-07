//
//  eventmanager.c
//  heisprosjekt
//
//  Created by Anastasia on 07/03/2018.
//  Copyright © 2018 Anastasia. All rights reserved.
//

#include "eventmanager.h"
void eventmanager_floor_indicator_light (struct State* statemachine)
{
    elev_set_floor_indicator(statemachine->current_floor);
    
}

void eventmanager_set_direction(struct Queue* order_list, struct State* statemachine)
{
    if (statemachine->current_state == NORMAL_STOP || statemachine->current_state == EXECUTE)
        elev_set_motor_direction(statemachine->current_direction);
    
    else
        return;
}


void eventmanager_update_lights(struct Queue* order_list, struct State* statemachine)
{
    for (int floor = 0; floor < N_FLOORS; floor++)
    {
        //Light on
        if (elev_get_button_signal(BUTTON_CALL_UP, floor) == 1) {
            elev_set_button_lamp(BUTTON_CALL_UP, floor, 1);
        }
        
        if (elev_get_button_signal(BUTTON_CALL_DOWN, floor) == 1) {
            elev_set_button_lamp(BUTTON_CALL_DOWN, floor, 1);
        }
        
        if (elev_get_button_signal(BUTTON_COMMAND, floor) == 1) {
            elev_set_button_lamp(BUTTON_COMMAND, floor, 1);
        }
        
        
        //Light off
        if (order_list->up_queue[floor] == 0) {
            elev_set_button_lamp(BUTTON_CALL_UP, floor, 0);
        }
        
        if (order_list->down_queue[floor] == 0) {
            elev_set_button_lamp(BUTTON_CALL_DOWN, floor, 0);
        }
        
        if (order_list->floor_queue[floor] == 0) {
            elev_set_button_lamp(BUTTON_COMMAND, floor, 0);
        }
    }
}
