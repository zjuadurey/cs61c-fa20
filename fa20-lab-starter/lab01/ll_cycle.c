#include <stddef.h>
#include "ll_cycle.h"

int ll_has_cycle(node *head) {
    /* your code here */

    if (!head) return 0;

    node *tortoise = head, *hare = head;

    while (1) {
        if (tortoise->next && tortoise->next->next) {
            tortoise = tortoise->next->next;
        } else break;
        hare = hare->next;

        if (hare == tortoise) {
            return 1;
        } else continue;
    }

    return 0;
}