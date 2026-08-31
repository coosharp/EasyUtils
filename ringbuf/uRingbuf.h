/**
 * @file uRingbuf.h
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
 *      MACROS
 *********************/

/*********************
 *    DECLARATIONS
 *********************/
struct uRingbuf
{
    char * buf;
    size_t mask;
    size_t read_idx;
    size_t write_idx;
};


typedef enum uRingbuf_read_mode
{
    URINGBUF_READ_ALL,
    URINGBUF_READ_PART
} uRingbuf_read_mode_t;


typedef enum uRingbuf_write_mode
{
    URINGBUF_WRITE_OVERWRITE,
    URINGBUF_WRITE_TRY,
    URINGBUF_WRITE_FILL_PART
} uRingbuf_write_mode_t;

/**********************
*  GLOBAL PROTOTYPES
 **********************/

void uRingbuf_init(struct uRingbuf * rb, char * buf, size_t buf_size);

void uRingbuf_deinit(struct uRingbuf * rb);

bool uRingbuf_write_byte(struct uRingbuf * rb, char src, uRingbuf_write_mode_t mode);

size_t uRingbuf_write(struct uRingbuf * rb, const char * src, size_t len, uRingbuf_write_mode_t mode);

bool uRingbuf_read_byte(struct uRingbuf * rb, char * dst);

size_t uRingbuf_read(struct uRingbuf * rb, char * dst, size_t len, uRingbuf_read_mode_t mode);

size_t uRingbuf_peek(struct uRingbuf * rb, size_t skip_cnt, char * dst, size_t len);

size_t uRingbuf_mark_read(struct uRingbuf * rb, size_t len);

size_t uRingbuf_mark_write(struct uRingbuf * rb, size_t len);

bool uRingbuf_find(struct uRingbuf * rb, const char * needle, size_t len, size_t start_offset, size_t * found_idx);

size_t uRingbuf_get_free(struct uRingbuf * rb);

static inline bool uRingbuf_is_empty(struct uRingbuf * rb)
{
    return (rb->read_idx == rb->write_idx);
}

static inline bool uRingbuf_is_full(struct uRingbuf * rb)
{
    return ((rb->write_idx - rb->read_idx) & (rb->mask)) == rb->mask;
}

static inline size_t uRingbuf_get_used(struct uRingbuf * rb)
{
    return (rb->write_idx - rb->read_idx) & rb->mask;
}

 

#ifdef __cplusplus
}
#endif

#endif /*_U_RINGBUF_H*/


/******************************* (END OF FILE) *********************************/


