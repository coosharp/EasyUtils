/**
 * @file uWatchdog.c
 *
 */
  
/*********************
 *      INCLUDES
 *********************/
#include "uWatchdog.h"
/*********************
 *      MACROS
 *********************/

/* Check if WDG did expire */
#define WDG_IS_EXPIRED(_wdg_, _time_) (((_time_) - (_wdg_)->last_tick) > (_wdg_)->timeout)

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void _add_watchdog(struct uWatchdog * wdg);
static void _remove_watchdog(struct uWatchdog * wdg);
/**********************
 *  STATIC VARIABLES
 **********************/
static uint32_t ulTicks = 0;
static struct uWatchdog * tWatchdogList = NULL;
/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 
void uWatchdog_increase_tick(uint32_t tick_period)
{
    ulTicks += tick_period;
}


void uWatchdog_register(struct uWatchdog * wdg, const char * name, uint32_t timeout)
{
    struct uWatchdog * wdg_node = tWatchdogList;
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

void uWatchdog_logout(struct uWatchdog * wdg)
{
    _remove_watchdog(wdg);
}

void uWatchdog_reload(struct uWatchdog * wdg)
{
    uint32_t now_tick = ulTicks;
    if(!WDG_IS_EXPIRED(wdg, now_tick))
        wdg->last_tick = now_tick;
}

void uWatchdog_loop(struct uWatchdog ** wdg_timeout)
{
    uint32_t now_tick = ulTicks;
     
    for(struct uWatchdog * wdg_node = tWatchdogList; 
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
static void _add_watchdog(struct uWatchdog * wdg)
{
    wdg->next = tWatchdogList;
    tWatchdogList = wdg;
}

static void _remove_watchdog(struct uWatchdog * wdg)
{
    struct uWatchdog ** pp = &tWatchdogList;

    while(*pp) {
        if(*pp == wdg) {
            *pp = wdg->next;
            break;
        }
        pp = &(*pp)->next;
    }
}

/******************************* (END OF FILE) *********************************/



 







