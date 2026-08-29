#include <stdio.h>
#include "uMessage.h"


static void message_cb(struct uMessage * message)
{
    uint32_t id = uMessage_get_id(message);

    printf("Message ID = %d", id);
}

int main(void)
{
    struct uMessage message_1;
    uMessage_subscribe(&message_1, UMESSAGE_THEME_CHANGED, message_cb, NULL);
    uMessage_publish(UMESSAGE_THEME_CHANGED);

    for(;;) {

    }

    return 0;
}