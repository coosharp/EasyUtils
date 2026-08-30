/**
 * @file uWatchdog.h
 *
 */
  
#ifndef _U_WATCHDOG_H
#define _U_WATCHDOG_H


#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <stdint.h>
#include <string.h>
/*********************
 *      MACROS
 *********************/

/*********************
 *    DECLARATIONS
 *********************/
struct uWatchdog
{
    char name[32];
    uint32_t last_tick;
    uint32_t timeout;
    struct uWatchdog * next;
};
/**********************
*  GLOBAL PROTOTYPES
 **********************/

void uWatchdog_increase_tick(uint32_t tick_period);

void uWatchdog_register(struct uWatchdog * wdg, const char * name, uint32_t timeout);

void uWatchdog_logout(struct uWatchdog * wdg);

void uWatchdog_reload(struct uWatchdog * wdg);

void uWatchdog_loop(struct uWatchdog ** wdg_timeout);

static inline const char * uWatchdog_get_name(struct uWatchdog * wdg)
{
    return wdg->name;
}

static inline uint32_t uWatchdog_get_timeout(struct uWatchdog * wdg)
{
    return wdg->timeout;
}


#ifdef __cplusplus
}
#endif

#endif /*_U_WATCHDOG_H*/


/******************************* (END OF FILE) *********************************/


