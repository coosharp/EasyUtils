#include <stdio.h>
#include "uMailbox.h"



static void mail1_cb(void * param)
{
    printf("mail 1 callback!\r\n");
}

static void mail2_cb(void * param)
{
    printf("mail 2 callback!\r\n");
}

static void mail3_cb(void * param)
{
    printf("mail 3 callback!\r\n");
}

int main(void)
{

    printf("Begin!\r\n");

    struct uMail mail_1 = {0};
    struct uMail mail_2 = {0};
    struct uMail mail_3 = {0};

    uMailbox_write_mail(&mail_1, NULL, mail1_cb);
    uMailbox_write_mail(&mail_2, NULL, mail2_cb);
    uMailbox_write_mail(&mail_3, NULL, mail3_cb);

    uMailbox_send_mail(&mail_1);
    uMailbox_send_mail(&mail_2);
    uMailbox_send_mail(&mail_3);
    uMailbox_send_mail(&mail_2);

    struct uMail * mail_active;

    for(int i = 0; i < 10; i++) {

        uMailbox_peek_mail(&mail_active);

        uMailbox_read_mail(mail_active);
    }

    printf("End!\r\n");

    return 0;
}