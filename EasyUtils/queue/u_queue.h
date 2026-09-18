/**
 * @file u_queue.h
 *
 */
  
#ifndef _U_QUEUE_H
#define _U_QUEUE_H


#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
/*********************
 *      MACROS
 *********************/
#define U_QUEUE_MEMCPY(dest, src, size)        memcpy(dest, src, size)
#define U_QUEUE_MEMSET(dest, value, size)      memset(dest, value, size)
/*********************
 *    DECLARATIONS
 *********************/
typedef struct u_queue u_queue_t;

struct u_queue
{
        uint8_t * buffer;
        uint16_t item_size;
        uint16_t capacity;
        uint16_t head;
        uint16_t tail;
        uint16_t count;
};

void u_queue_init         (u_queue_t * q, uint8_t * buffer, uint16_t item_size, uint16_t capacity);
bool u_queue_send_front   (u_queue_t * q, const void * item);
bool u_queue_send_back    (u_queue_t * q, const void * item);
bool u_queue_receive_front(u_queue_t * q, void * item);
bool u_queue_receive_back (u_queue_t * q, void * item);
void u_queue_reset        (u_queue_t * q);

/**********************
 *   STATIC FUNCTIONS
 **********************/
static inline bool u_queue_is_full(u_queue_t * q)
{
        return (q->count == q->capacity);
}

static inline bool u_queue_is_empty(u_queue_t * q)
{
        return (q->count == 0);
}

static inline uint16_t u_queue_get_count(u_queue_t * q)
{
        return q->count;
}

#ifdef __cplusplus
}
#endif

#endif /*_U_QUEUE_H*/


/******************************* (END OF FILE) *********************************/




