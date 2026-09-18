/**
 * @file u_ringbuf.c
 *
 */
  
/*********************
 *      INCLUDES
 *********************/
#include "u_ringbuf.h"
/*********************
 *      MACROS
 *********************/
#define U_RINGBUF_MIN(x, y) ((x) < (y) ? (x) : (y))
#define U_RINGBUF_MAX(x, y) ((x) > (y) ? (x) : (y))
/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 
void u_ringbuf_init(struct u_ringbuf * rb, char * buf, size_t buf_size)
{
        if(buf_size & (buf_size - 1)) {
                return;
        }

        rb->buf         = buf;
        rb->mask        = buf_size - 1;
        rb->read_idx    = 0;
        rb->write_idx   = 0;
}   

void u_ringbuf_deinit(struct u_ringbuf * rb)
{
        rb->read_idx = 0;
        rb->write_idx = 0;
}

size_t u_ringbuf_get_free(struct u_ringbuf * rb)
{
        size_t buf_size = rb->mask + 1;
        size_t used_size = u_ringbuf_get_used(rb);
        return buf_size - used_size;
}

bool u_ringbuf_write_byte(struct u_ringbuf * rb, char src, u_ringbuf_write_mode_t mode)
{
        bool is_full = u_ringbuf_is_full(rb);

        if(is_full) {
                if(mode == U_RINGBUF_WRITE_OVERWRITE) {
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

size_t u_ringbuf_write(struct u_ringbuf * rb, const char * src, size_t len, u_ringbuf_write_mode_t mode)
{
        size_t buf_size = rb->mask + 1;
        size_t free_space = u_ringbuf_get_free(rb);
        size_t write_len = 0;

        switch (mode) 
        {
                case U_RINGBUF_WRITE_OVERWRITE:
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

                case U_RINGBUF_WRITE_TRY:
                        if(len > free_space) return 0;
                        write_len = len;
                break;

                case U_RINGBUF_WRITE_FILL_PART:
                        write_len = (len > free_space) ? free_space : len;
                break;
        }

        size_t first_part = U_RINGBUF_MIN(write_len, buf_size - rb->write_idx);

        memcpy(&rb->buf[rb->write_idx], src, first_part);
        if(write_len > first_part)
        memcpy(&rb->buf[0], src + first_part, write_len - first_part);

        rb->write_idx = (rb->write_idx + write_len) & rb->mask;

        return write_len;
}

bool u_ringbuf_read_byte(struct u_ringbuf * rb, char * dst)
{
        bool is_empty = u_ringbuf_is_empty(rb);

        if(is_empty) return false;

        *dst = rb->buf[rb->read_idx];
        rb->read_idx = ((rb->read_idx + 1) & rb->mask);

        return true;
}

size_t u_ringbuf_read(struct u_ringbuf * rb, char * dst, size_t len, u_ringbuf_read_mode_t mode)
{
        size_t buf_size = rb->mask + 1;
        size_t used_size = u_ringbuf_get_used(rb);
        size_t read_len = 0;

        switch (mode)
        {
                case U_RINGBUF_READ_ALL:
                        if (len > used_size) return 0;
                        read_len = len;
                        break;

                case U_RINGBUF_READ_PART:
                default:
                        read_len = (len > used_size) ? used_size : len;
                        break;
        }

        size_t first_part = U_RINGBUF_MIN(read_len, buf_size - rb->read_idx);

        memcpy(dst, &rb->buf[rb->read_idx], first_part);
        if (read_len > first_part) 
                memcpy(dst + first_part, &rb->buf[0], read_len - first_part);
        
        rb->read_idx = (rb->read_idx + read_len) & rb->mask;

        return read_len;
}

size_t u_ringbuf_peek(struct u_ringbuf * rb, size_t skip_cnt, char * dst, size_t len)
{
        size_t buf_size = rb->mask + 1;
        size_t used_size = u_ringbuf_get_used(rb);

        if (skip_cnt >= used_size) return 0;

        size_t r_ptr = (rb->read_idx + skip_cnt) & rb->mask;

        size_t available = used_size - skip_cnt;
        size_t peek_len = (len > available) ? available : len;

        if (peek_len == 0) return 0;

        size_t first_part = U_RINGBUF_MIN(peek_len, buf_size - r_ptr);

        memcpy(dst, &rb->buf[r_ptr], first_part);
        if (peek_len > first_part) 
                memcpy(dst + first_part, &rb->buf[0], peek_len - first_part);
        
        return peek_len;
}

size_t u_ringbuf_mark_read(struct u_ringbuf * rb, size_t len)
{
        size_t used_size = u_ringbuf_get_used(rb);
        size_t mark_len = (len > used_size) ? used_size : len;

        rb->read_idx = (rb->read_idx + mark_len) & rb->mask;

        return mark_len;
}

size_t u_ringbuf_mark_write(struct u_ringbuf * rb, size_t len)
{
        size_t free_size = u_ringbuf_get_free(rb);
        size_t mark_len = (len > free_size) ? free_size : len;

        rb->write_idx = (rb->write_idx + mark_len) & rb->mask;

        return mark_len;
}







/******************************* (END OF FILE) *********************************/



 







