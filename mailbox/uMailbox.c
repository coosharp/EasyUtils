/**
 * @file uMailbox.c
 *
 */
  
/*********************
 *      INCLUDES
 *********************/
#include "uMailbox.h"
/*********************
 *      MACROS
 *********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
bool _push_mail_list(struct uMail * mail);
void _pop_mail_list(struct uMail * mail);
/**********************
 *  STATIC VARIABLES
 **********************/
static uint32_t ulMailIdx = 0;
static struct uMail * tMailList[UMAILBOX_CAP] = {NULL};
/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 

void uMailbox_write_mail(struct uMail * mail, void * param, uMailbox_callback_t callback)
{
    mail->param = param;
    mail->callback = callback;
}

bool uMailbox_send_mail(struct uMail * mail)
{
    return _push_mail_list(mail);
}

void uMailbox_peek_mail(struct uMail ** mail)
{
    *mail = tMailList[ulMailIdx - 1];
}

void uMailbox_delete_mail(struct uMail * mail)
{
    _pop_mail_list(mail);
}

void uMailbox_delete_all_mail(void)
{
    for(uint32_t i = 0; i < sizeof(tMailList) / sizeof(tMailList[0]); i++)
        tMailList[i] = NULL;
}

void uMailbox_read_mail(struct uMail * mail)
{
    if(mail == NULL) return;
    
    if(mail->callback != NULL) {
        mail->callback(mail->param);
    }
    _pop_mail_list(mail);
}
/**********************
 *   STATIC FUNCTIONS
 **********************/
bool _push_mail_list(struct uMail * mail)
{
    if(ulMailIdx >= sizeof(tMailList) / sizeof(tMailList[0])) {
        return false;
    }

    tMailList[ulMailIdx] = mail;

    ulMailIdx += 1;
    return true;
}

void _pop_mail_list(struct uMail * mail)
{
    tMailList[ulMailIdx - 1] = NULL;

    ulMailIdx -= 1;
}

/******************************* (END OF FILE) *********************************/



 







