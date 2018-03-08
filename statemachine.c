#include "statemachine.h"

// Sets the state of the elevator
void statemachine_set_current_state (struct State* statemachine) {
    statemachine->current_position = elev_get_floor_sensor_signal(); // Sets current position
    
    if (statemachine->current_position != -1)
        statemachine->current_floor = statemachine->current_position; // Sets current floor
}


// Initializes statemachine
void statemachine_initialize(struct State* statemachine)
{
    // Ignores stop button and orders made while the elevator is between floors
    while (elev_get_floor_sensor_signal() == -1)
        elev_set_motor_direction(DIRN_UP);
    
    elev_set_motor_direction(DIRN_STOP);
    statemachine->current_direction = DIRN_STOP;
    statemachine->current_state = IDLE;
    
    statemachine_set_current_state(statemachine);
    
}

int statemachine_check_for_stop (struct State* statemachine, struct Queue* order_list)
{
    if (statemachine->current_position == -1)
        return 0;
    
    if (statemachine->current_floor == order_list->floor_queue[0] && statemachine->current_position == statemachine->current_floor)
        return 1;
    
    if ((statemachine->current_direction == DIRN_UP) && (order_list->up_queue[statemachine->current_position]))
        return 1;
    
    if ((statemachine->current_direction == DIRN_DOWN) && (order_list->down_queue[statemachine->current_position]))
        return 1;
    
    for (int floor = 0; floor < 4; floor++) {
        if (order_list->floor_queue[floor] == statemachine->current_floor)
            return 1;
    }
    
    return 0;
}

void statemachine_stop (struct State* statemachine, struct Queue* order_list) {
		int wait_time = 3;
		clock_t start_time = clock();
		clock_t timer = start_time; 
		
		while (timer < start_time + wait_time*CLOCKS_PER_SEC) {
			
           		queue_update_up_down_queues(order_list, statemachine);
           		queue_update_floor_queue(order_list, statemachine);

            		statemachine_set_current_state (statemachine);

       			eventmanager_floor_indicator_light (statemachine);
        		eventmanager_update_lights(order_list, statemachine);

			timer = clock();
		}
}

void statemachine_run (struct State* statemachine, struct Queue* order_list) {

	int i = 0;
	while(1)
    	{
		i++;

        	if (elev_get_stop_signal() == 1) {
            	statemachine->current_state = EMERGENCY_STOP;
        	}
        
        	else
        	{
           	 queue_update_up_down_queues(order_list, statemachine);
           	 queue_update_floor_queue(order_list, statemachine);
            	statemachine_set_current_state (statemachine);
        	}         
        
       		eventmanager_floor_indicator_light (statemachine);
        	eventmanager_update_lights(order_list, statemachine);
        
        	eventmanager_set_direction(order_list, statemachine);

		if (i % 12000 == 0) {
			for (int j = 0; j < N_FLOORS; j++) {
				printf("Etasje: ");
				printf("%d", j);
				printf("%s", "\n");

				printf("Queues: ");
				printf("%d %d %d", order_list->floor_queue[j], order_list->down_queue[j], order_list->up_queue[j]);
				printf("%s", "\n");
			}

		}
            
        	switch (statemachine->current_state)
        	{
                    
            	case IDLE:
            	{
               		if (statemachine->current_position == statemachine->current_floor)
                	{
                    	int should_stop = (elev_get_button_signal(BUTTON_CALL_DOWN, statemachine->current_floor) || elev_get_button_signal(BUTTON_CALL_UP, statemachine->current_floor) || elev_get_button_signal(BUTTON_COMMAND, statemachine->current_floor));
                                       
                    	if (should_stop) {
                        	order_list->up_queue[statemachine->current_floor] = 0;
                        	order_list->down_queue[statemachine->current_floor] = 0;
                                           
                        if (order_list->floor_queue[0] == statemachine->current_floor)
                            	queue_delete_from_floor_queue(order_list, 0);
                    
                    	statemachine->current_state = NORMAL_STOP;
                    	break;
                    	}
                }
                    

                int is_order = 0;
                for (int floor = 0; floor < N_FLOORS; floor++)
                {
                    if (order_list->up_queue[floor] || order_list->down_queue[floor])
                    {
                        is_order = 1;
                        queue_add_to_floor_queue(order_list, floor);
                    }
                }
                
                if (order_list->floor_queue[0] != -1)
                    is_order = 1;

                if (is_order)
                    statemachine->current_state = EXECUTE;
                    
                    
                break;
            }
                
            
            
            case EXECUTE:
                {
                    
                if (statemachine->current_position == statemachine->current_floor)
                {
                    if (order_list->floor_queue[0] > statemachine->current_floor && order_list->floor_queue[0] != -1)
                        statemachine->current_direction = DIRN_UP;
                    if (order_list->floor_queue[0] < statemachine->current_floor && order_list->floor_queue[0] != -1)
                        statemachine->current_direction = DIRN_DOWN;
                    }

                    
                if (statemachine_check_for_stop(statemachine, order_list))
                    {
                        if (statemachine->current_direction == DIRN_UP || order_list->floor_queue[0] == statemachine->current_floor)
                            order_list->up_queue[statemachine->current_floor] = 0;
                        if (statemachine->current_direction == DIRN_DOWN || order_list->floor_queue[0] == statemachine->current_floor)
                            order_list->down_queue[statemachine->current_floor] = 0;
                        
                        queue_delete_from_floor_queue(order_list, statemachine->current_floor);
                        statemachine->current_state = NORMAL_STOP;
                        break;
                    }
                    break;
                }
                
                
            case NORMAL_STOP:
            {
                //statemachine->current_direction = DIRN_STOP;
		elev_set_motor_direction(DIRN_STOP);
                elev_set_door_open_lamp(1);
                
		statemachine_stop (statemachine, order_list);


		
		if (order_list->floor_queue[0] != -1) {
			statemachine->current_state = EXECUTE;
			
		}
		

		elev_set_door_open_lamp(0);
		statemachine->current_state = IDLE;


                break;
            }
                
            case EMERGENCY_STOP:
                {
		    elev_set_motor_direction(DIRN_STOP);
                    //statemachine->current_direction = DIRN_STOP;

		    while (elev_get_stop_signal()) {
		    	queue_initialize(order_list);
			elev_set_stop_lamp(1);
                    	if (statemachine->current_position != -1) {
                        	elev_set_door_open_lamp(1);
                    	}
		   }
                    
                   elev_set_stop_lamp(0);
                   if (statemachine->current_position != -1) {
                   	statemachine->current_state = NORMAL_STOP;
                        break;
                   }
                        
                   statemachine->current_state = IDLE;
                   elev_set_door_open_lamp(0);
                   break;

                }
                
                default:
                {
                    printf("Nå er'e no feil her.");
                }
                    
                    
        }
    }
}

