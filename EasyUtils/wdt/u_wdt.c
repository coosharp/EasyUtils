/**
 * @file u_wdt.c
 *
 */
  
/*********************
 *      INCLUDES
 *********************/
#include "u_wdt.h"
/*********************
 *      MACROS
 *********************/

/* Check if WDG did expire */
#define WDG_IS_EXPIRED(_wdg_, _time_) (((_time_) - (_wdg_)->last_tick) > (_wdg_)->timeout)

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void _add_watchdog(struct u_wdt * wdg);
static void _remove_watchdog(struct u_wdt * wdg);
/**********************
 *  STATIC VARIABLES
 **********************/
static uint32_t ulTicks = 0;
static struct u_wdt * tWatchdogList = NULL;
/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 
void u_wdt_increase_tick(uint32_t tick_period)
{
        ulTicks += tick_period;
}

void u_wdt_register(struct u_wdt * wdg, const char * name, uint32_t timeout)
{
        struct u_wdt * wdg_node = tWatchdogList;
        while(wdg_node != NULL) {
                if(wdg_node == wdg)
                return;
                wdg_node = wdg_node->next;
        }


        uint32_t i = 0;
        for(i = 0; i < strlen(name); i++) {
                wdg->name[i] = name[i];
        }
        wdg->name[i] = 0;

        wdg->last_tick = ulTicks;
        wdg->timeout = timeout;
        _add_watchdog(wdg);
}

void u_wdt_logout(struct u_wdt * wdg)
{
        _remove_watchdog(wdg);
}

void u_wdt_reload(struct u_wdt * wdg)
{
        uint32_t now_tick = ulTicks;
        if(!WDG_IS_EXPIRED(wdg, now_tick))
                wdg->last_tick = now_tick;
}

void u_wdt_loop(struct u_wdt ** wdg_timeout)
{
        uint32_t now_tick = ulTicks;

        for(struct u_wdt * wdg_node = tWatchdogList; 
                wdg_node != NULL; 
                wdg_node = wdg_node->next)
        {
                if(WDG_IS_EXPIRED(wdg_node, now_tick)) {
                        *wdg_timeout = wdg_node;
                        break;
                }
        }
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
static void _add_watchdog(struct u_wdt * wdg)
{
        wdg->next = tWatchdogList;
        tWatchdogList = wdg;
}

static void _remove_watchdog(struct u_wdt * wdg)
{
        struct u_wdt ** pp = &tWatchdogList;

        while(*pp) {
                if(*pp == wdg) {
                        *pp = wdg->next;
                        break;
                }
                pp = &(*pp)->next;
        }
}

/******************************* (END OF FILE) *********************************/



 







