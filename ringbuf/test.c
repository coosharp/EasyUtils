#include <stdio.h>
#include "uRingbuf.h"

int main(void)
{
    static char write_byte = 'Y';
    static char write_buf[] = "Hello world";
    static char read_buf[128] = {0};

    static char buf[1024] = {0};
    struct uRingbuf rb = {0};

    uRingbuf_init(&rb, buf, sizeof(buf));

    uRingbuf_write_byte(&rb, write_byte, URINGBUF_WRITE_OVERWRITE);
    uRingbuf_read_byte(&rb, &read_buf[0]);
    printf("read byte = %c\r\n", read_buf[0]);

    uRingbuf_write(&rb, write_buf, sizeof(write_buf), URINGBUF_WRITE_OVERWRITE);
    uRingbuf_read(&rb, read_buf, sizeof(write_buf), URINGBUF_READ_ALL);
    printf("read buf = %s\r\n", read_buf);

    return 0;
}