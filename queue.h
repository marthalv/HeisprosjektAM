#include <stdio.h>
#include "elev.h"
#include "statemachine.h"
//#include "timer.h"
#include "eventmanager.h"

struct Queue {
int going_up_queue[FLOORS];
int going_down_queue[FLOORS];
int floor_target_queue[FLOORS];
};

void queue_add_to_up_and_down_queue (struct Queue *queue);
void queue_add_to_floor_target_queue (struct Queue *queue, struct State *state);
