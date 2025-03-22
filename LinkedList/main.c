#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "linked_list.h"

int test_split_list() {
    LinkedList *list = list_create();

    // Add elements to linked list
    int values[] = {1, 2, 3, 4, 5, 6};
    for (int i = 0; i < 6; i++) {
        list_add(list, &values[i]);
    }

    // Pointers for split lists
    LinkedListNode *left = NULL;
    LinkedListNode *right = NULL;

    // Call split_list
    split_list(list, &left, &right);

    // Ensure both parts exist
    if (!left || !right) return -1;

    // Free list
    list_destroy(list, NULL);

    // Success
    return 0;
}

int main(void) {
    int result = 0;

    // split list test
    result = test_split_list();
    if (result == 0) {
        printf("split_list succeeded\n");
    } else {
        printf("split_list failed\n");
    }
    return 0;

}
