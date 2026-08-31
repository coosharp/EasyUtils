/**
 * @file uRingbuf.c
 *
 */
  
/*********************
 *      INCLUDES
 *********************/
#include "uRingbuf.h"
/*********************
 *      MACROS
 *********************/
#define URINGBUF_MIN(x, y) ((x) < (y) ? (x) : (y))
#define URINGBUF_MAX(x, y) ((x) > (y) ? (x) : (y))
/**********************
 *   GLOBAL VARIABLES
 **********************/ 

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 
void uRingbuf_init(struct uRingbuf * rb, char * buf, size_t buf_size)
{
    if(buf_size & (buf_size - 1)) {
        return;
    }

    rb->buf         = buf;
    rb->mask        = buf_size - 1;
    rb->read_idx    = 0;
    rb->write_idx   = 0;
}   

void uRingbuf_deinit(struct uRingbuf * rb)
{
    rb->read_idx = 0;
    rb->write_idx = 0;
}

bool uRingbuf_write_byte(struct uRingbuf * rb, char src, uRingbuf_write_mode_t mode)
{
    bool is_full = uRingbuf_is_full(rb);

    if(is_full) {
        if(mode == URINGBUF_WRITE_OVERWRITE) {
            rb->read_idx = ((rb->read_idx + 1) & rb->mask);
        }
        else {
            return false;
        }
    }

    rb->buf[rb->write_idx] = src;
    rb->write_idx = ((rb->write_idx + 1) & rb->mask);

    return true;
}

size_t uRingbuf_write(struct uRingbuf * rb, const char * src, size_t len, uRingbuf_write_mode_t mode)
{
    size_t buf_size = rb->mask + 1;
    size_t free_space = uRingbuf_get_free(rb);
    size_t write_len = 0;

    switch (mode) 
    {
        case URINGBUF_WRITE_OVERWRITE:
        default:
            write_len = len;
            if(write_len > buf_size) {
                src += (write_len - buf_size);
                write_len = buf_size;
            }
            if(write_len > free_space) {
                size_t overwrite_count = write_len - free_space;
                rb->read_idx = (rb->read_idx + overwrite_count) & rb->mask;
            }
            break;

        case URINGBUF_WRITE_TRY:
            if(len > free_space) return 0;
            write_len = len;
            break;

        case URINGBUF_WRITE_FILL_PART:
            write_len = (len > free_space) ? free_space : len;
            break;
    }

    size_t first_part = URINGBUF_MIN(write_len, buf_size - rb->write_idx);

    memcpy(&rb->buf[rb->write_idx], src, first_part);
    if(write_len > first_part)
        memcpy(&rb->buf[0], src + first_part, write_len - first_part);

    rb->write_idx = (rb->write_idx + write_len) & rb->mask;

    return write_len;
}

bool uRingbuf_read_byte(struct uRingbuf * rb, char * dst)
{
    bool is_empty = uRingbuf_is_empty(rb);

    if(is_empty) return false;

    *dst = rb->buf[rb->read_idx];
    rb->read_idx = ((rb->read_idx + 1) & rb->mask);

    return true;
}

size_t uRingbuf_read(struct uRingbuf * rb, char * dst, size_t len, uRingbuf_read_mode_t mode)
{
    size_t buf_size = rb->mask + 1;
    size_t used_size = uRingbuf_get_used(rb);
    size_t read_len = 0;

    switch (mode)
    {
        case URINGBUF_READ_ALL:
            if (len > used_size) return 0;
            read_len = len;
            break;

        case URINGBUF_READ_PART:
        default:
            read_len = (len > used_size) ? used_size : len;
            break;
    }

    size_t first_part = URINGBUF_MIN(read_len, buf_size - rb->read_idx);

    memcpy(dst, &rb->buf[rb->read_idx], first_part);
    if (read_len > first_part) 
        memcpy(dst + first_part, &rb->buf[0], read_len - first_part);
    
    rb->read_idx = (rb->read_idx + read_len) & rb->mask;

    return read_len;
}

size_t uRingbuf_peek(struct uRingbuf * rb, size_t skip_cnt, char * dst, size_t len)
{
    size_t buf_size = rb->mask + 1;
    size_t used_size = uRingbuf_get_used(rb);

    if (skip_cnt >= used_size) return 0;

    size_t r_ptr = (rb->read_idx + skip_cnt) & rb->mask;

    size_t available = used_size - skip_cnt;
    size_t peek_len = (len > available) ? available : len;

    if (peek_len == 0) return 0;

    size_t first_part = URINGBUF_MIN(peek_len, buf_size - r_ptr);

    memcpy(dst, &rb->buf[r_ptr], first_part);
    if (peek_len > first_part) {
        memcpy(dst + first_part, &rb->buf[0], peek_len - first_part);
    }
    return peek_len;
}

size_t uRingbuf_mark_read(struct uRingbuf * rb, size_t len)
{
    size_t used_size = uRingbuf_get_used(rb);
    size_t mark_len = (len > used_size) ? used_size : len;

    rb->read_idx = (rb->read_idx + mark_len) & rb->mask;

    return mark_len;
}

size_t uRingbuf_mark_write(struct uRingbuf * rb, size_t len)
{
    size_t free_size = uRingbuf_get_free(rb);
    size_t mark_len = (len > free_size) ? free_size : len;

    rb->write_idx = (rb->write_idx + mark_len) & rb->mask;

    return mark_len;
}

bool uRingbuf_find(struct uRingbuf * rb, const char * needle, size_t len, size_t start_offset, size_t * found_idx)
{
    *found_idx = 0;

    size_t used_size = uRingbuf_get_used(rb);

    if (used_size < (len + start_offset)) return 0;

    size_t max_x = used_size - len;
    size_t r_ptr_base = rb->read_idx;
    bool found = false;

    for (size_t skip_x = start_offset; !found && skip_x <= max_x; ++skip_x) {
        found = true;
        size_t r_ptr = (r_ptr_base + skip_x) & rb->mask;
        for (size_t idx = 0; idx < len; ++idx) {
            if (rb->buf[r_ptr] != needle[idx]) {
                found = false;
                break;
            }
            r_ptr = (r_ptr + 1) & rb->mask;
        }
        if (found) {
            *found_idx = skip_x;
        }
    }
    return found;
}

size_t uRingbuf_get_free(struct uRingbuf * rb)
{
    size_t buf_size = rb->mask + 1;
    size_t used_size = uRingbuf_get_used(rb);
    return buf_size - used_size;
}
/**********************
 *   STATIC FUNCTIONS
 **********************/



/******************************* (END OF FILE) *********************************/



 







