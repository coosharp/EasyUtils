/**
 * @file u_timer.h
 *
 */
  
#ifndef _U_TIMER_H
#define _U_TIMER_H


#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <stdint.h>
#include <stdbool.h>
/*********************
 *      MACROS
 *********************/
#define U_TIMER_REPEAT_INFINITE     (-1)
#define U_TIMER_NO_TIMER_READY      (0xFFFFFFFF)
/*********************
 *    DECLARATIONS
 *********************/
typedef struct u_timer u_timer_t;
typedef void (* u_timer_cb_t)(u_timer_t * timer);

struct u_timer
{
        struct u_timer * next;

        uint32_t period;           /**< How often the timer should run */

        uint32_t last_run;         /**< Last time the timer ran */

        u_timer_cb_t callback;      /**< Timer function */

        void * user_data;          /**< Custom user data */

        int32_t repeat_count;      /**< 1: One time;  -1 : infinity;  n>0: residual times */

        uint32_t paused : 1;

        uint32_t auto_delete : 1;
};

void            u_timer_create          (struct u_timer * timer, u_timer_cb_t callback, uint32_t period, int32_t repeat_count, void * user_data);
void            u_timer_destroy         (struct u_timer * timer);
uint32_t        u_timer_loop            (void);
void            u_timer_update_timebase (uint32_t tick_period);
void            u_timer_pause           (struct u_timer * timer);
void            u_timer_resume          (struct u_timer * timer);
void            u_timer_ready           (struct u_timer * timer);
void            u_timer_reset           (struct u_timer * timer);
void            u_timer_set_repeat_count(struct u_timer * timer, int32_t repeat_count);
void            u_timer_set_auto_delete (struct u_timer * timer, bool auto_delete);
void            u_timer_set_period      (struct u_timer * timer, uint32_t period);
void            u_timer_set_user_data   (struct u_timer * timer, void * user_data);

/**********************
 *   STATIC FUNCTIONS
 **********************/
static inline void * u_timer_get_user_data(struct u_timer * timer)
{
        return timer->user_data;
}

static inline bool u_timer_is_paused(struct u_timer * timer)
{
        return timer->paused != 0;
}

static inline uint32_t u_timer_get_period(struct u_timer * timer)
{
        return timer->period;
}

#ifdef __cplusplus
}
#endif

#endif /*_U_TIMER_H*/


/******************************* (END OF FILE) *********************************/


