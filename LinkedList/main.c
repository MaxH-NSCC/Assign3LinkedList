#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "linked_list.h"

int main(void) {
    // Create a linked list
    LinkedList *list = list_create();
    if (!list) {
        printf("Failed to create list.\n");
        return 1;
    }

    // Add unordered ints
    int values[] = {4, 1, 7, 3, 9, 2, 6, 5, 8, 0};
    for (int i = 0; i < 10; i++) {
        if (list_add(list, &values[i]) == -1) {
            printf("Failed to add element %d\n", values[i]);
            return 1;
        }
    }

    // Print the list before sorting
    printf("Before sorting:\n");
    for (size_t i = 0; i < list_size(list); i++) {
        void *data;
        if (list_get_at(list, i, &data) == 0) {
            printf("%d -> ", *(int *)data);
        }
    }
    printf("NULL\n");

    // Sort the list using merge sort
    list_merge_sort(list, compare_ints);

    // Print the list after sorting
    printf("After sorting:\n");
    for (size_t i = 0; i < list_size(list); i++) {
        void *data;
        if (list_get_at(list, i, &data) == 0) {
            printf("%d -> ", *(int *)data);
        }
    }
    printf("NULL\n");

    // Free memory
    list_destroy(list, NULL);
    return 0;
}
