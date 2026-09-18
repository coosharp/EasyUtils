/**
 * @file u_ringbuf.h
 *
 */
  
#ifndef _U_RINGBUF_H
#define _U_RINGBUF_H


#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
/*********************
 *    DECLARATIONS
 *********************/
struct u_ringbuf
{
        char * buf;
        size_t mask;
        size_t read_idx;
        size_t write_idx;
};


typedef enum u_ringbuf_read_mode
{
        U_RINGBUF_READ_ALL,
        U_RINGBUF_READ_PART
} u_ringbuf_read_mode_t;


typedef enum u_ringbuf_write_mode
{
        U_RINGBUF_WRITE_OVERWRITE,
        U_RINGBUF_WRITE_TRY,
        U_RINGBUF_WRITE_FILL_PART
} u_ringbuf_write_mode_t;


void    u_ringbuf_init          (struct u_ringbuf * rb, char * buf, size_t buf_size);
void    u_ringbuf_deinit        (struct u_ringbuf * rb);
size_t  u_ringbuf_get_free      (struct u_ringbuf * rb);
bool    u_ringbuf_write_byte    (struct u_ringbuf * rb, char src, u_ringbuf_write_mode_t mode);
size_t  u_ringbuf_write         (struct u_ringbuf * rb, const char * src, size_t len, u_ringbuf_write_mode_t mode);
bool    u_ringbuf_read_byte     (struct u_ringbuf * rb, char * dst);
size_t  u_ringbuf_read          (struct u_ringbuf * rb, char * dst, size_t len, u_ringbuf_read_mode_t mode);
size_t  u_ringbuf_peek          (struct u_ringbuf * rb, size_t skip_cnt, char * dst, size_t len);
size_t  u_ringbuf_mark_read     (struct u_ringbuf * rb, size_t len);
size_t  u_ringbuf_mark_write    (struct u_ringbuf * rb, size_t len);


/**********************
 *   STATIC FUNCTIONS
 **********************/
static inline bool u_ringbuf_is_empty(struct u_ringbuf * rb)
{
        return (rb->read_idx == rb->write_idx);
}

static inline bool u_ringbuf_is_full(struct u_ringbuf * rb)
{
        return ((rb->write_idx - rb->read_idx) & (rb->mask)) == rb->mask;
}

static inline size_t u_ringbuf_get_used(struct u_ringbuf * rb)
{
        return (rb->write_idx - rb->read_idx) & rb->mask;
}

 

#ifdef __cplusplus
}
#endif

#endif /*_U_RINGBUF_H*/


/******************************* (END OF FILE) *********************************/


