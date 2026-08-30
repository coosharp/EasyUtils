#include <stdio.h>
#include "uMessage.h"


static void message1_cb(struct uMessage * message)
{
    uint32_t id = uMessage_get_id(message);

    printf("Message 1 ID = %d\r\n", id);
}

static void message2_cb(struct uMessage * message)
{
    uint32_t id = uMessage_get_id(message);

    printf("Message 2 ID = %d\r\n", id);
}

static void message3_cb(struct uMessage * message)
{
    uint32_t id = uMessage_get_id(message);

    printf("Message 3 ID = %d\r\n", id);
}

int main(void)
{
    struct uMessage message_1 = {0};
    struct uMessage message_2 = {0};
    struct uMessage message_3 = {0};

    uMessage_subscribe(&message_1, UMESSAGE_THEME_CHANGED, message1_cb, NULL);
    uMessage_subscribe(&message_2, UMESSAGE_WIFI_CONNECTED, message1_cb, NULL);
    uMessage_subscribe(&message_3, UMESSAGE_POWER_ON, message1_cb, NULL);

    uMessage_publish(UMESSAGE_THEME_CHANGED);
    uMessage_publish(UMESSAGE_WIFI_CONNECTED);
    uMessage_publish(UMESSAGE_POWER_ON);

    return 0;
}