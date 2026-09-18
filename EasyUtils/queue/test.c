#include <stdio.h>
#include <stdint.h>
#include "u_queue.h"

int main(void)
{
        uint32_t buffer[4] = {0};
        u_queue_t q;
        uint32_t item = 0;

        u_queue_init(&q, (uint8_t *)buffer, sizeof(buffer[0]), 4);

        printf("empty=%d, full=%d, count=%u\n",
                u_queue_is_empty(&q),
                u_queue_is_full(&q),
                u_queue_get_count(&q));

        for (int i = 0; i < 4; i++) {
                item = i + 10;
                if (!u_queue_send_back(&q, &item)) {
                        printf("send_back failed at i=%d\n", i);
                        break;
                }
        }

        printf("after send count=%u\n", u_queue_get_count(&q));

        for (int i = 0; i < 4; i++) {
                if (u_queue_receive_front(&q, &item)) {
                        printf("receive_front item=%u\n", item);
                }
        }

        printf("final empty=%d, full=%d, count=%u\n",
                u_queue_is_empty(&q),
                u_queue_is_full(&q),
                u_queue_get_count(&q));

        return 0;
}
