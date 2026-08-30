/**
 * @file uMailbox.h
 *
 */
  
#ifndef _U_MAILBOX_H
#define _U_MAILBOX_H


#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <stdint.h>
#include <stdbool.h>
/*********************
 *      DEFINE
 *********************/
#define UMAILBOX_CAP  32
/*********************
 *    DECLARATIONS
 *********************/
typedef struct uMail uMail_t;
typedef void (* uMailbox_callback_t)(void * param);

struct uMail
{
    void * param;
    uMailbox_callback_t callback;
    struct uMail * next;
};
/**********************
*  GLOBAL PROTOTYPES
 **********************/

void uMailbox_write_mail(struct uMail * mail, void * param, uMailbox_callback_t callback);

bool uMailbox_send_mail(struct uMail * mail);

void uMailbox_peek_mail(struct uMail ** mail);

void uMailbox_delete_mail(struct uMail * mail);

void uMailbox_delete_all_mail(void);

void uMailbox_read_mail(struct uMail * mail);

#ifdef __cplusplus
}
#endif

#endif /*_EUTL_MAILBOX_H*/


/******************************* (END OF FILE) *********************************/


