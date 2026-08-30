#include <stdio.h>
#include "uWatchdog.h"


int main(void)
{

    struct uWatchdog wdg_1 = {0};
    struct uWatchdog wdg_2 = {0};

    uWatchdog_register(&wdg_1, "watchdog_1", 100);
    uWatchdog_register(&wdg_2, "watchdog_2", 1000);

    static uint8_t is_catched = 0;;
    struct uWatchdog * wdg_timeout = NULL;

    for(;;) {

        uWatchdog_increase_tick(1);

        uWatchdog_reload(&wdg_1);

        uWatchdog_loop(&wdg_timeout);

        if(wdg_timeout) {
            if(!is_catched)
                printf("A watchdog is expired %s!", wdg_timeout);
            is_catched = 1;
        }       
    }
    return 0;
}






