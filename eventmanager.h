#ifndef __INCLUDE_EVENTMANAGER_H__
#define __INCLUDE_EVENTMANAGER_H__

#pragma once

#include <stdio.h>
#include "queue.h"
#include "elev.h"
#include "statemachine.h"
#include "timer.h"


void eventmanager_stop_elevator (struct State* state);
void eventmanager_floor_indicator_light(struct State* state);
void eventmanager_update_lights (struct Queue *queue, struct State *state);



#endif
