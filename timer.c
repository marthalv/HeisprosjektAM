#include "timer.h"

time_t timer_start_timer() {
    time_t time_now = time(NULL);
    return time_now;
}

int timer_time_is_up(time_t start_time) {
    if (time(NULL) > (start_time + 3)) {
        return 1;
    }
        return 0;
}
