/**
 * @file u_wdt.h
 *
 */
  
#ifndef _U_WDT_H
#define _U_WDT_H


#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <stdint.h>
#include <string.h>
/*********************
 *    DECLARATIONS
 *********************/
struct u_wdt
{
    char name[32];
    uint32_t last_tick;
    uint32_t timeout;
    struct u_wdt * next;
};


void u_wdt_increase_tick(uint32_t tick_period);

void u_wdt_register(struct u_wdt * wdg, const char * name, uint32_t timeout);

void u_wdt_logout(struct u_wdt * wdg);

void u_wdt_reload(struct u_wdt * wdg);

void u_wdt_loop(struct u_wdt ** wdg_timeout);


/**********************
 *   STATIC FUNCTIONS
 **********************/
static inline const char * u_wdt_get_name(struct u_wdt * wdg)
{
    return wdg->name;
}

static inline uint32_t u_wdt_get_timeout(struct u_wdt * wdg)
{
    return wdg->timeout;
}


#ifdef __cplusplus
}
#endif

#endif /*_U_WDT_H*/


/******************************* (END OF FILE) *********************************/


