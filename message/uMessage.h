/**
 * @file uMessage.h
 *
 */
  
#ifndef _U_MESSAGE_H
#define _U_MESSAGE_H


#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <stdint.h>
/*********************
 *      MACROS
 *********************/

/*********************
 *    DECLARATIONS
 *********************/
typedef struct uMessage uMessage_t;
typedef void (* uMessage_callback_t)(uMessage_t * message);

typedef enum uMessage_id {

    UMESSAGE_NONE = 0,

    UMESSAGE_LANGUAGE_CHANGED,
    UMESSAGE_THEME_CHANGED,
    UMESSAGE_FONT_CHANGED,

    UMESSAGE_BATTERY_LOW,
    UMESSAGE_BATTERY_OKAY,
    UMESSAGE_BATTERY_CHARGING,
    UMESSAGE_BATTERY_FULL,

    UMESSAGE_WIFI_CONNECTED,
    UMESSAGE_WIFI_DISCONNECTED,

    UMESSAGE_BLE_CONNECTED,
    UMESSAGE_BLE_DISCONNECTED,

    UMESSAGE_POWER_ON,
    UMESSAGE_POWER_OFF,

    UMESSAGE_MAX

} uMessage_id_t;


struct uMessage
{
    uMessage_id_t id;
    uMessage_callback_t callback;
    void * user_data;
    struct uMessage * next;
};

/**********************
*  GLOBAL PROTOTYPES
 **********************/
void uMessage_subscribe(struct uMessage * message, 
                        uMessage_id_t id, 
                        uMessage_callback_t callback, 
                        void * user_data);

void uMessage_unsubscribe(struct uMessage * message);

void uMessage_publish(uMessage_id_t id);

static inline uMessage_id_t uMessage_get_id(struct uMessage * message)
{
    return message->id;
}

static inline void * uMessage_get_user_data(struct uMessage * message)
{
    return message->user_data;
}

#ifdef __cplusplus
}
#endif

#endif /*_U_MESSAGE_H*/


/******************************* (END OF FILE) *********************************/


