#include <stdio.h>
#include "queue.h"
#include "elev.h"
#include "statemachine.h"
#include "timer.h"


static int FLOORS = 4;
void eventmanager_initialize (struct Queue *queue);
