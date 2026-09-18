#include <stdio.h>
#include "u_wdt.h"


int main(void)
{
        struct u_wdt wdg_1 = {0};
        struct u_wdt wdg_2 = {0};

        u_wdt_register(&wdg_1, "watchdog_1", 100);
        u_wdt_register(&wdg_2, "watchdog_2", 1000);

        static uint8_t is_catched = 0;;
        struct u_wdt * wdg_timeout = NULL;

        for(;;) {

            u_wdt_increase_tick(1);

            u_wdt_reload(&wdg_1);

            u_wdt_loop(&wdg_timeout);

            if(wdg_timeout) {
                if(!is_catched)
                    printf("A watchdog is expired %s!", wdg_timeout);
                is_catched = 1;
            }       
        }
        return 0;
}






