#include <stdio.h>
#include "u_ringbuf.h"

int main(void)
{
        static char write_byte = 'Y';
        static char write_buf[] = "Hello world";
        static char read_buf[128] = {0};

        static char buf[1024] = {0};
        struct u_ringbuf rb = {0};

        u_ringbuf_init(&rb, buf, sizeof(buf));

        u_ringbuf_write_byte(&rb, write_byte, U_RINGBUF_WRITE_OVERWRITE);
        u_ringbuf_read_byte(&rb, &read_buf[0]);
        printf("read byte = %c\r\n", read_buf[0]);

        u_ringbuf_write(&rb, write_buf, sizeof(write_buf), U_RINGBUF_WRITE_OVERWRITE);
        u_ringbuf_read(&rb, read_buf, sizeof(write_buf), U_RINGBUF_READ_ALL);
        printf("read buf = %s\r\n", read_buf);

        return 0;
}
