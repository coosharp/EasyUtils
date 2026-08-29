/**
 * @file uMessage.c
 *
 */
  
/*********************
 *      INCLUDES
 *********************/
#include "uMessage.h"
/*********************
 *      MACROS
 *********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void _add_message(struct uMessage * message);
static void _remove_message(struct uMessage * message);
/**********************
 *  STATIC VARIABLES
 **********************/
static struct uMessage * tMessageList = NULL;
/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 
void uMessage_subscribe(struct uMessage * message, 
                        uMessage_id_t id, 
                        uMessage_callback_t callback, 
                        void * user_data)
{
    message->id = id;
    message->callback = callback;
    message->user_data = user_data;

    _add_message(message);
}

void uMessage_unsubscribe(struct uMessage * message)
{
    _remove_message(message);
}

void uMessage_publish(uMessage_id_t id)
{
    struct uMessage * message = tMessageList;

    while(message != NULL) {
        if(message->id == id) {
            if(message->callback != NULL) 
                message->callback(message);
        }
        message = message->next;
    }
}


/**********************
 *   STATIC FUNCTIONS
 **********************/
static void _add_message(struct uMessage * message)
{
    message->next = tMessageList;
    tMessageList = message;
}

static void _remove_message(struct uMessage * message)
{
    struct uMessage ** pp = &tMessageList;

    while(*pp) {
        if(*pp == message) {
            *pp = message->next;
            return;
        }
        pp = &((*pp)->next);
    }
}



/******************************* (END OF FILE) *********************************/



 







