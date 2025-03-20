#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"

void printValue(void *ptr, char type) {
    if (type == 'i') {
        printf("Integer value: %d\n", *(int *)ptr);
    } else if (type == 'f') {
        printf("Float value: %.2f\n", *(float *)ptr);
    } else if (type == 'c') {
        printf("Character value: %c\n", *(char *)ptr);
    } else {
        printf("Unknown type.\n");
    }
}

int main(void)
{
    printf("Starting testing\n");

    // list create
    LinkedList * my_linked_list = list_create();
    if (my_linked_list == NULL) {
        printf("Error creating list!\n");
        return 1;
    } else {
        printf("List created successfully!\n");
    }

    // list size
    int list_size_result = list_size(my_linked_list);
    printf("Size of list: %d\n", list_size_result);

    // list add
    int result = list_add(my_linked_list, "Albert");
    if (result == -1) {
        printf("Failed to add to linked list!\n");
        return 1;
    } else {
        printf("Added to linked list!\n");
    }
    list_size_result = list_size(my_linked_list);
    printf("Size of list: %d\n", list_size_result);

    result = list_add(my_linked_list, "B");
    if (result == -1) {
        printf("Failed to add to linked list!\n");
        return 1;
    } else {
        printf("Added to linked list!\n");
    }

    for (int i = 0; i < 10; i++) {
        int result2 = list_add(my_linked_list, i+1);
        if (result2 == -1) {
            printf("FAILED\n");
            return 1;
        }
        if (result2 == 0) {
            printf("Added to linked list again!\n");
        }
    }

    // list size check
    list_size_result = list_size(my_linked_list);
    printf("Size of list: %d\n", list_size_result);


    // list get
    void* get_data;
    result = list_get_at(my_linked_list, 0, &get_data);
    if (result == -1) {
        printf("Failed to get data");
        return 1;
    }
    if (result == 0) {
        printValue(get_data, 'c');
        printf("Success getting value!\n");
    }

    result = list_get_at(my_linked_list, 1, &get_data);
    if (result == -1) {
        printf("Failed to get data");
        return 1;
    }
    if (result == 0) {
        printValue(get_data, 'c');
        printf("Success getting value!\n");
    }

    // list insert
    result = list_insert_at(my_linked_list, 1, "Z");
    if (result == -1) {
        printf("Failed to insert value\n");
    }
    if (result == 0) {
        printf("Inserted value\n");
    }

    // list size check
    list_size_result = list_size(my_linked_list);
    printf("Size of list: %d\n", list_size_result);

    // list get check
    result = list_get_at(my_linked_list, 0, &get_data);
    if (result == -1) {
        printf("Failed");
        return 1;
    }
    if (result == 0) {
        printValue(get_data, 'c');
        printf("Success getting value!\n");
    }

    result = list_get_at(my_linked_list, 1, &get_data);
    if (result == -1) {
        printf("Failed");
        return 1;
    }
    if (result == 0) {
        printValue(get_data, 'c');
        printf("Success getting value!\n");
    }

    // list remove
    result = list_remove_at(my_linked_list, 1, &get_data);
    if (result == -1) {
        printf("Failed to insert value\n");
    }
    if (result == 0) {
        printf("Removed value\n");
    }
    printValue(get_data, 'c');

    // list size check
    list_size_result = list_size(my_linked_list);
    printf("Size of list: %d\n", list_size_result);

    // list get check
    result = list_get_at(my_linked_list, 0, &get_data);
    if (result == -1) {
        printf("Failed");
        return 1;
    }
    if (result == 0) {
        printValue(get_data, 'c');
        printf("Success getting value!\n");
    }

    result = list_get_at(my_linked_list, 1, &get_data);
    if (result == -1) {
        printf("Failed");
        return 1;
    }
    if (result == 0) {
        printValue(get_data, 'c');
        printf("Success getting value!\n");
    }

    // Free list
    list_destroy(my_linked_list, NULL);
    // using the free function gives an error

    return 0;
}
