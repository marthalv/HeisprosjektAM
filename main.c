#include <stdio.h>
#include "queue.h"
#include "statemachine.h"

int main()
{
    if (!elev_init())
    {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }
    
    struct Queue order_list;
    struct State statemachine;

    queue_initialize(&order_list);
    statemachine_initialize(&statemachine);
    
    statemachine_run (&statemachine, &order_list);
}
