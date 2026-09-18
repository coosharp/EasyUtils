/**
 * @file u_ll.c
 *
 */
  
/*********************
 *      INCLUDES
 *********************/
#include "u_ll.h"
/*********************
 *      MACROS
 *********************/
#define U_LL_NODE_META_SIZE             (sizeof(uint8_t *) + sizeof(uint8_t *))
#define U_LL_PREV_P_OFFSET(ll_p)        (ll_p->n_size)
#define U_LL_NEXT_P_OFFSET(ll_p)        (ll_p->n_size + sizeof(uint8_t *))
/**********************
 *  STATIC PROTOTYPES
 **********************/
static void _node_set_prev(struct u_ll * ll_p, uint8_t * node_p, uint8_t * prev_node);
static void _node_set_next(struct u_ll * ll_p, uint8_t * node_p, uint8_t * next_node);
/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 

void u_ll_init(struct u_ll * ll_p, uint32_t node_size)
{
        ll_p->head = NULL;
        ll_p->tail = NULL;

#ifdef U_ARCH_64
        /*Round the size up to 8*/
        node_size = (node_size + 7) & (~0x7);
#else
        /*Round the size up to 4*/
        node_size = (node_size + 3) & (~0x3);
#endif

        ll_p->n_size = node_size;
}

void * u_ll_ins_head(struct u_ll * ll_p)
{
        uint8_t * node_p = U_LL_MALLOC(ll_p->n_size + U_LL_NODE_META_SIZE);

        if(node_p != NULL) {
                _node_set_prev(ll_p, node_p, NULL);               /*No prev. before the new head*/
                _node_set_next(ll_p, node_p, ll_p->head);         /*After new comes the old head*/

                if(ll_p->head != NULL)                            /*If there is old head then before it goes the new*/
                        _node_set_prev(ll_p, ll_p->head, node_p);

                ll_p->head = node_p;                              /*Set the new head in the dsc.*/

                if(ll_p->tail == NULL)                            /*If there is no tail (1. node) set the tail too*/
                        ll_p->tail = node_p;
        }

        return node_p;
}

void * u_ll_ins_prev(struct u_ll * ll_p, void * node_p)
{
        uint8_t * new_node = NULL;

        if(u_ll_get_head(ll_p) == node_p) {
                return u_ll_ins_head(ll_p);
        }
        else {
                new_node = U_LL_MALLOC(ll_p->n_size + U_LL_NODE_META_SIZE);
                
                if(new_node != NULL) {
                        uint8_t * prev_node = u_ll_get_prev(ll_p, node_p);

                        _node_set_next(ll_p, prev_node, new_node);
                        _node_set_prev(ll_p, new_node, prev_node);
                        _node_set_prev(ll_p, node_p, new_node);
                        _node_set_next(ll_p, new_node, node_p);
                }
        }
        return new_node;
}

void * u_ll_ins_tail(struct u_ll * ll_p)
{
        uint8_t * node_p = U_LL_MALLOC(ll_p->n_size + U_LL_NODE_META_SIZE);

        if(node_p != NULL) {
                _node_set_next(ll_p, node_p, NULL);               /*No next after the new tail*/
                _node_set_prev(ll_p, node_p, ll_p->tail);         /*The prev. before new is the old tail*/

                if(ll_p->tail != NULL)                            /*If there is old tail then the new comes after it*/
                        _node_set_next(ll_p, ll_p->tail, node_p);
                
                ll_p->tail = node_p;                              /*Set the new tail in the dsc.*/

                if(ll_p->head == NULL)                            /*If there is no head (1. node) set the head too*/
                        ll_p->head = node_p;
        }

        return node_p;
}

void u_ll_remove(struct u_ll * ll_p, void * node_p)
{
        if(u_ll_get_head(ll_p) == node_p) {

                /*The new head will be the node after 'node_p'*/
                ll_p->head = u_ll_get_next(ll_p, node_p);

                if(ll_p->head == NULL) {
                        ll_p->tail = NULL;
                }
                        
                else {
                        _node_set_prev(ll_p, ll_p->head, NULL);
                }
                        
        }
        else if(u_ll_get_tail(ll_p) == node_p) {

                /*The new tail will be the node before 'node_p'*/
                ll_p->tail = u_ll_get_prev(ll_p, node_p);

                if(ll_p->tail == NULL) {
                        ll_p->head = NULL;
                }
                else {
                        _node_set_next(ll_p, ll_p->tail, NULL);
                }
        }
        else {
                uint8_t * prev_node = u_ll_get_prev(ll_p, node_p);
                uint8_t * next_node = u_ll_get_next(ll_p, node_p);

                _node_set_next(ll_p, prev_node, next_node);
                _node_set_prev(ll_p, next_node, prev_node);
        }
}

void u_ll_clear(struct u_ll * ll_p, void (* cleanup_cb)(void * node_p))
{
        uint8_t * node_p = u_ll_get_head(ll_p);
        uint8_t * next_node = NULL;

        while(node_p != NULL) {
                next_node = u_ll_get_next(ll_p, node_p);
                if(cleanup_cb) {
                        u_ll_remove(ll_p, node_p);
                        U_LL_FREE(node_p);
                }
                else {
                        cleanup_cb(node_p);
                }
                node_p = next_node;
        }
}

void u_ll_chg_list(struct u_ll * ll_ori_p, struct u_ll * ll_new_p, void * node_p, bool head)
{
        u_ll_remove(ll_ori_p, node_p);

        if(head) {

                /*Set node as head*/
                _node_set_prev(ll_new_p, node_p, NULL);
                _node_set_next(ll_new_p, node_p, ll_new_p->head);

                if(ll_new_p->head != NULL) 
                        _node_set_prev(ll_new_p, ll_new_p->head, node_p);

                ll_new_p->head = node_p; 

                if(ll_new_p->tail == NULL)  
                        ll_new_p->tail = node_p;
        }
        else {

                /*Set node as tail*/
                _node_set_next(ll_new_p, node_p, NULL); 
                _node_set_prev(ll_new_p, node_p, ll_new_p->tail); 

                if(ll_new_p->tail != NULL) 
                        _node_set_next(ll_new_p, ll_new_p->tail, node_p);

                ll_new_p->tail = node_p;  

                if(ll_new_p->head == NULL) 
                        ll_new_p->head = node_p;
        }
}

void * u_ll_get_next(const struct u_ll * ll_p, const void * node_p)
{
        /*Pointer to the next node is stored in the end of this node.
         *Go there and return the address found there*/

        const uint8_t * temp_node = (const uint8_t *)node_p;

        temp_node += U_LL_NEXT_P_OFFSET(ll_p);

        return *((uint8_t **)temp_node);
}

void * u_ll_get_prev(const struct u_ll * ll_p, const void * node_p)
{
        /*Pointer to the prev. node is stored in the end of this node.
         *Go there and return the address found there*/

        const uint8_t * temp_node = (const uint8_t *)node_p;

        temp_node += U_LL_PREV_P_OFFSET(ll_p);

        return *((uint8_t **)temp_node);
}

uint32_t u_ll_get_len(const struct u_ll * ll_p)
{
        uint32_t len = 0;
        void * node_p = u_ll_get_head(ll_p);

        for(; node_p != NULL; node_p = u_ll_get_next(ll_p, node_p)) {
                len++;
        }

        return len;
}

void u_ll_move_before(struct u_ll * ll_p, void * node_p, void * after_node)
{
        if(node_p == after_node) return;

        uint8_t * before_node;
        if(after_node != NULL) {
                before_node = u_ll_get_prev(ll_p, after_node);
        }
        else {
                before_node = u_ll_get_tail(ll_p);
        }

        if(node_p == before_node) return;

        u_ll_remove(ll_p, node_p);

        _node_set_next(ll_p, before_node, node_p);
        _node_set_prev(ll_p, node_p, before_node);
        _node_set_prev(ll_p, after_node, node_p);
        _node_set_next(ll_p, node_p, after_node);

        if(after_node == NULL) ll_p->tail = node_p;
        if(before_node == NULL) ll_p->head = node_p;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/**
 * Set the previous node pointer of a node
 * @param ll_p pointer to linked list
 * @param act pointer to a node which prev. node pointer should be set
 * @param prev pointer to a node which should be the previous node before 'act'
 */
static void _node_set_prev(struct u_ll * ll_p, uint8_t * node_p, uint8_t * prev_node)
{
        uint8_t * act8 = node_p;

        act8 += U_LL_PREV_P_OFFSET(ll_p);

        struct u_ll_node ** act_node_p = (struct u_ll_node **)act8;
        struct u_ll_node ** prev_node_p = (struct u_ll_node **)&prev_node;

        *act_node_p = *prev_node_p;
}


/**
 * Set the 'next node pointer' of a node
 * @param ll_p pointer to linked list
 * @param act pointer to a node which next node pointer should be set
 * @param next pointer to a node which should be the next node before 'act'
 */
static void _node_set_next(struct u_ll * ll_p, uint8_t * node_p, uint8_t * next_node)
{
        uint8_t * act8 = node_p;

        act8 += U_LL_NEXT_P_OFFSET(ll_p);
        
        struct u_ll_node ** act_node_p = (struct u_ll_node **) act8;
        struct u_ll_node ** next_node_p = (struct u_ll_node **)&next_node;

        *act_node_p = *next_node_p;
}


/******************************* (END OF FILE) *********************************/


