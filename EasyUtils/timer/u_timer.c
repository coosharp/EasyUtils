/**
 * @file u_timer.c
 *
 */
  
/*********************
 *      INCLUDES
 *********************/
#include "u_timer.h"
/*********************
 *      MACROS
 *********************/

/**********************
 *   GLOBAL VARIABLES
 **********************/ 

/**********************
 *  STATIC PROTOTYPES
 **********************/
static uint32_t _get_remaining_time(struct u_timer * timer, uint32_t current_tick);
static void _add_timer(struct u_timer * timer);
static void _remove_timer(struct u_timer * timer);
/**********************
 *  STATIC VARIABLES
 **********************/
static uint32_t ulTicks = 0;
static struct u_timer * tTimerList = NULL;
/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 
void u_timer_create(struct u_timer * timer, u_timer_cb_t callback, uint32_t period, int32_t repeat_count, void * user_data)
{
        timer->period = period;
        timer->last_run = ulTicks;
        timer->callback = callback;
        timer->user_data = user_data;
        timer->repeat_count = repeat_count;
        timer->paused = 0;
        timer->auto_delete = 1;

        _add_timer(timer);
}

void u_timer_destroy(struct u_timer * timer)
{
        _remove_timer(timer);
}

uint32_t u_timer_loop(void)
{
        uint32_t now_tick = ulTicks;
        struct u_timer * timer_node = tTimerList;

        while (timer_node != NULL) {
                if (!timer_node->paused && (now_tick - timer_node->last_run) >= timer_node->period) {
                
                        timer_node->last_run = now_tick;
                        
                        /* Timer period elapsed, call the timer callback */
                        if (timer_node->callback) {
                                timer_node->callback(timer_node);
                        }

                        /* Handle repeat count */
                        if (timer_node->repeat_count > 0) {

                                timer_node->repeat_count--;

                                if (timer_node->repeat_count == 0) {

                                        struct u_timer * to_delete = timer_node;
                                        timer_node = timer_node->next; /* Move to next before deletion */

                                        if (to_delete->auto_delete) {
                                                u_timer_destroy(to_delete);
                                        }
                                        continue; /* Skip the increment of timer_node */
                                }
                        }
                }
                timer_node = timer_node->next;
        }

        uint32_t time_until_next = U_TIMER_NO_TIMER_READY;
        timer_node = tTimerList;
        
        while(timer_node) {
                if(!timer_node->paused) {
                        uint32_t remaining_time = _get_remaining_time(timer_node, now_tick);
                        if(remaining_time < time_until_next)
                                time_until_next = remaining_time;
                }
                timer_node = timer_node->next;
        }

        return time_until_next;
}

void u_timer_update_timebase(uint32_t tick_period)
{
        ulTicks += tick_period;
}

void u_timer_pause(struct u_timer * timer)
{
        timer->paused = 1;
}

void u_timer_resume(struct u_timer * timer)
{
        timer->paused = 0;
}

void u_timer_ready(struct u_timer * timer)
{
        timer->last_run = ulTicks - timer->period;
}

void u_timer_reset(struct u_timer * timer)
{
        timer->last_run = ulTicks;
}

void u_timer_set_repeat_count(struct u_timer * timer, int32_t repeat_count)
{
        timer->repeat_count = repeat_count;
}

void u_timer_set_auto_delete(struct u_timer * timer, bool auto_delete)
{
        timer->auto_delete = auto_delete ? 1 : 0;
}

void u_timer_set_period(struct u_timer * timer, uint32_t period)
{
        timer->period = period;
}

void u_timer_set_user_data(struct u_timer * timer, void * user_data)
{
        timer->user_data = user_data;
}


/**********************
 *   STATIC FUNCTIONS
 **********************/
static uint32_t _get_remaining_time(struct u_timer * timer, uint32_t current_tick)
{
        if(timer->paused) {
                return U_TIMER_NO_TIMER_READY;
        }

        uint32_t elapsed = current_tick - timer->last_run;
        
        if(elapsed >= timer->period) {
                return 0;
        } 
        else {
                return timer->period - elapsed;
        }
}

static void _add_timer(struct u_timer * timer)
{
        timer->next = tTimerList;
        tTimerList = timer;
}

static void _remove_timer(struct u_timer * timer)
{
        struct u_timer ** pp = &tTimerList;

        while(*pp) {
                if(*pp == timer) {
                        *pp = timer->next;
                        break;
                }
                pp = &(*pp)->next;
        }
}

/******************************* (END OF FILE) *********************************/



 







