#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "u_ll.h"

struct demo_node
{
    int value;
};

int main(void)
{
        struct u_ll ll = {0};
        struct demo_node *n1 = NULL;
        struct demo_node *n2 = NULL;
        struct demo_node *n3 = NULL;
        struct demo_node *tmp = NULL;

        u_ll_init(&ll, sizeof(struct demo_node));

        n1 = (struct demo_node *)u_ll_ins_head(&ll);
        n1->value = 10;

        n2 = (struct demo_node *)u_ll_ins_tail(&ll);
        n2->value = 20;

        n3 = (struct demo_node *)u_ll_ins_tail(&ll);
        n3->value = 30;

        printf("head=%p tail=%p empty=%d\n",
                u_ll_get_head(&ll),
                u_ll_get_tail(&ll),
                u_ll_is_empty(&ll));

        for (tmp = (struct demo_node *)u_ll_get_head(&ll);
             tmp != NULL;
             tmp = (struct demo_node *)u_ll_get_next(&ll, tmp)) 
        {
                printf("value=%d\n", tmp->value);
        }

        u_ll_remove(&ll, n2);
        free(n2);

        printf("after remove len=%u\n", u_ll_get_len(&ll));

        for (tmp = (struct demo_node *)u_ll_get_head(&ll);
             tmp != NULL;
             tmp = (struct demo_node *)u_ll_get_next(&ll, tmp)) 
        {
                printf("value=%d\n", tmp->value);
        }

        free(n1);
        free(n3);
        
        return 0;
}
