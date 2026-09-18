/**
 * @file u_ll.h
 *
 */
  
#ifndef _U_LL_H
#define _U_LL_H



#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
/*********************
 *      MACROS
 *********************/
#define U_LL_MEMSET(node, size)    memset((node), 0, (size))
#define U_LL_MALLOC(size)          malloc((size))
#define U_LL_FREE(ptr)             free((ptr))
/*********************
 *    DECLARATIONS
 *********************/
struct u_ll
{
        uint32_t n_size;
        uint8_t * head;
        uint8_t * tail;
};

void            u_ll_init       (struct u_ll * ll_p, uint32_t node_size);
void *          u_ll_ins_head   (struct u_ll * ll_p);
void *          u_ll_ins_prev   (struct u_ll * ll_p, void * node_p);
void *          u_ll_ins_tail   (struct u_ll * ll_p);
void            u_ll_remove     (struct u_ll * ll_p, void * node_p);
void            u_ll_clear      (struct u_ll * ll_p, void (* cleanup_cb)(void * node_p));
void            u_ll_chg_list   (struct u_ll * ll_ori_p, struct u_ll * ll_new_p, void * node_p, bool head);
void *          u_ll_get_next   (const struct u_ll * ll_p, const void * node_p);
void *          u_ll_get_prev   (const struct u_ll * ll_p, const void * node_p);
uint32_t        u_ll_get_len    (const struct u_ll * ll_p);
void            u_ll_move_before(struct u_ll * ll_p, void * node_p, void * after_node);

/**********************
 *   STATIC FUNCTIONS
 **********************/
static inline void * u_ll_get_head(const struct u_ll * ll_p)
{
        return ll_p->head;
}

static inline void * u_ll_get_tail(const struct u_ll * ll_p)
{
        return ll_p->tail;
}

static inline bool u_ll_is_empty(const struct u_ll * ll_p)
{
        return ((ll_p->head == NULL && ll_p->tail == NULL) ? true : false);
}


#ifdef __cplusplus
}
#endif

#endif /*_U_LL_H*/


/******************************* (END OF FILE) *********************************/




