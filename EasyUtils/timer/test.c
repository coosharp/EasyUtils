#include <stdio.h>
#include "u_timer.h"

static void timer_cb(u_timer_t * timer)
{
        static uint32_t count = 0;

        count += 1;

        printf("timer callback, period=%u, user_data=%p\n",
                timer->period,
                timer->user_data);

        printf("timer callback count: %u\n", count);
}

int main(void)
{
        struct u_timer timer = {0};
        uint32_t i;

        u_timer_create(&timer, timer_cb, 10, 20, (void *)0x1234);

        for (i = 0; i < 1000; i++) {
                u_timer_update_timebase(1);
                u_timer_loop();
        }

        u_timer_destroy(&timer);

        return 0;
}
