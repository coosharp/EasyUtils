/**
 * @file u_queue.c
 *
 */
  
/*********************
 *      INCLUDES
 *********************/
#include "u_queue.h"
/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 
void u_queue_init(u_queue_t * q, uint8_t * buffer, uint16_t item_size, uint16_t capacity)
{
        q->buffer = buffer;
        q->item_size = item_size;
        q->capacity = capacity;
        q->head = 0;
        q->tail = 0;
        q->count = 0;
}

bool u_queue_send_front(u_queue_t * q, const void * item)
{
        if(q->count == q->capacity) {
                return false; 
        }

        q->head = (q->head == 0) ? (q->capacity - 1) : (q->head - 1);
        U_QUEUE_MEMCPY(&q->buffer[q->head * q->item_size], item, q->item_size);
        q->count++;

        return true;
}

bool u_queue_send_back(u_queue_t * q, const void * item)
{
        if(q->count == q->capacity) {
                return false; 
        }

        U_QUEUE_MEMCPY(&q->buffer[q->tail * q->item_size], item, q->item_size);
        q->tail = (q->tail + 1) % q->capacity;
        q->count++;

        return true;
}

bool u_queue_receive_front(u_queue_t * q,  void * item)
{
        if(q->count == 0) {
                return false; 
        }

        U_QUEUE_MEMCPY(item, &q->buffer[q->head * q->item_size], q->item_size);
        q->head = (q->head + 1) % q->capacity;
        q->count--;

        return true;
}

bool u_queue_receive_back(u_queue_t * q,  void * item)
{
        if(q->count == 0) {
                return false; 
        }

        q->tail = (q->tail == 0) ? (q->capacity - 1) : (q->tail - 1);
        U_QUEUE_MEMCPY(item, &q->buffer[q->tail * q->item_size], q->item_size);
        q->count--;

        return true;
}

void u_queue_reset(u_queue_t * q)
{
        q->head = 0;
        q->tail = 0;
        q->count = 0;
}



/******************************* (END OF FILE) *********************************/


