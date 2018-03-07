#include <stdio.h>
#include "queue.h"
#include "eventmanager.h"
#include "statemachine.h"
#include "timer.h"

int main() {
    
    if (!elev_init())
    {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }
    
    int timer_start = 0;
    struct Queue order_list;
    struct State statemachine;
    
    queue_initialize(&order_list);
    statemachine_initialize(&statemachine);
    
    while(1)
    {
        if (elev_get_stop_signal())
            statemachine.current_state = EMERGENCY_STOP;
        
        else
        {
            queue_update_up_down_queues(&order_list, &statemachine);
            queue_update_floor_queue(&order_list, &statemachine);
            statemachine_set_current_state (&statemachine);
        }
        
        eventmanager_floor_indicator_light (&statemachine);
        eventmanager_update_lights(&order_list, &statemachine);
        
        eventmanager_set_direction(&order_list, &statemachine);
            
        switch (statemachine.current_state)
        {
                    
            case IDLE:
            {
                if (statemachine.current_position == statemachine.current_floor)
                {
                    int should_stop = (elev_get_button_signal(BUTTON_CALL_DOWN, statemachine.current_floor) || elev_get_button_signal(BUTTON_CALL_UP, statemachine.current_floor) || elev_get_button_signal(BUTTON_COMMAND, statemachine.current_floor));
                                       
                    if (should_stop) {
                        order_list.up_queue[statemachine.current_floor] = 0;
                        order_list.down_queue[statemachine.current_floor] = 0;
                                           
                        if (order_list.floor_queue[0] == statemachine.current_floor)
                            queue_delete_from_floor_queue(&order_list, 0);
                    
                    statemachine.current_state = NORMAL_STOP;
                    break;
                    }
                }
                    

                int is_order = 0;
                for (int floor = 0; floor < N_FLOORS; floor++)
                {
                    if (order_list.up_queue[floor] || order_list.down_queue[floor])
                    {
                        is_order = 1;
                        queue_add_to_floor_queue(&order_list, floor);
                    }
                }
                
                if (order_list.floor_queue[0] != -1)
                    is_order = 1;
                if (is_order)
                    statemachine.current_state = EXECUTE;
                    
                    
                break;
            }
                
            
            
            case EXECUTE:
                {
                    
                if (statemachine.current_position == statemachine.current_floor)
                {
                    if (order_list.floor_queue[0] > statemachine.current_floor && order_list.floor_queue[0] != -1)
                        statemachine.current_direction = DIRN_UP;
                    if (order_list.floor_queue[0] < statemachine.current_floor && order_list.floor_queue[0] != -1)
                        statemachine.current_direction = DIRN_DOWN;
                    }

                    
                if (statemachine_check_for_stop(&statemachine, &order_list))
                    {
                        if (statemachine.current_direction == DIRN_UP || order_list.floor_queue[0] == statemachine.current_floor)
                            order_list.up_queue[statemachine.current_floor] = 0;
                        if (statemachine.current_direction == DIRN_DOWN || order_list.floor_queue[0] == statemachine.current_floor)
                            order_list.down_queue[statemachine.current_floor] = 0;
                        
                        queue_delete_from_floor_queue(&order_list, statemachine.current_floor);
                        statemachine.current_state = NORMAL_STOP;
                        break;
                    }
                    break;
                }
                
                
            case NORMAL_STOP:
            {
                statemachine.current_direction = DIRN_STOP;
                elev_set_door_open_lamp(1);
                    
                timer_start += timer_start_timer();
                    
                if (timer_time_is_up(timer_start)) {
                    elev_set_door_open_lamp(0);
                    statemachine.current_state = IDLE;
                    break;
                }

                break;
            }
                
            case EMERGENCY_STOP:
                {
                    statemachine.current_direction = DIRN_STOP;
                    queue_initialize(&order_list);
                    
                    if (statemachine.current_position != -1) {
                        elev_set_door_open_lamp(1);
                    }
                    
                    elev_set_stop_lamp(1);
                    
                    if (!(elev_get_stop_signal())) {
                        elev_set_stop_lamp(0);
                        
                        if (statemachine.current_position != -1) {
                            statemachine.current_state = NORMAL_STOP;
                            break;
                        }
                        
                        statemachine.current_state = IDLE;
                        elev_set_door_open_lamp(0);
                        break;
                    }
                    break;
                }
                
                default:
                {
                    printf("Nå er'e no feil her.");
                }
                    
                    
        }
    }
}
