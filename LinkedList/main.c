#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "linked_list.h"

// Functions to test sorting with different data sets

// Function to test sorting with int values
void test_merge_sort_int(int *values, size_t count, const char *test_name) {
    printf("\n=== %s ===\n", test_name);

    // Create a linked list
    LinkedList *list = list_create();
    if (!list) {
        printf("Failed to create list.\n");
        return;
    }

    // Add values to the linked list
    for (size_t i = 0; i < count; i++) {
        if (list_add(list, &values[i]) == -1) {
            printf("Failed to add element %d\n", values[i]);
            list_destroy(list, NULL);
            return;
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
}

// Function to test sorting with char values
void test_merge_sort_char(char *values, size_t count, const char *test_name) {
    printf("\n=== %s ===\n", test_name);

    // Create a linked list
    LinkedList *list = list_create();
    if (!list) {
        printf("Failed to create list.\n");
        return;
    }

    // Add values to the linked list
    for (size_t i = 0; i < count; i++) {
        if (list_add(list, &values[i]) == -1) {
            printf("Failed to add element '%c'\n", values[i]);
            list_destroy(list, NULL);
            return;
        }
    }

    // Print the list before sorting
    printf("Before sorting:\n");
    for (size_t i = 0; i < list_size(list); i++) {
        void *data;
        if (list_get_at(list, i, &data) == 0) {
            printf("'%c' -> ", *(char *)data);
        }
    }
    printf("NULL\n");

    // Sort the list using merge sort
    list_merge_sort(list, compare_chars);

    // Print the list after sorting
    printf("After sorting:\n");
    for (size_t i = 0; i < list_size(list); i++) {
        void *data;
        if (list_get_at(list, i, &data) == 0) {
            printf("'%c' -> ", *(char *)data);
        }
    }
    printf("NULL\n");

    // Free memory
    list_destroy(list, NULL);
}

// Function to test sorting with float values
void test_merge_sort_float(float *values, size_t count, const char *test_name) {
    printf("\n=== %s ===\n", test_name);

    // Create a linked list
    LinkedList *list = list_create();
    if (!list) {
        printf("Failed to create list.\n");
        return;
    }

    // Add values to the linked list
    for (size_t i = 0; i < count; i++) {
        if (list_add(list, &values[i]) == -1) {
            printf("Failed to add element %.2f\n", values[i]);
            list_destroy(list, NULL);
            return;
        }
    }

    // Print the list before sorting
    printf("Before sorting:\n");
    for (size_t i = 0; i < list_size(list); i++) {
        void *data;
        if (list_get_at(list, i, &data) == 0) {
            printf("%.2f -> ", *(float *)data);
        }
    }
    printf("NULL\n");

    // Sort the list using merge sort
    list_merge_sort(list, compare_floats);

    // Print the list after sorting
    printf("After sorting:\n");
    for (size_t i = 0; i < list_size(list); i++) {
        void *data;
        if (list_get_at(list, i, &data) == 0) {
            printf("%.2f -> ", *(float *)data);
        }
    }
    printf("NULL\n");

    // Free memory
    list_destroy(list, NULL);
}

int main(void) {
    // Test Case 1: Random unordered numbers
    int values1[] = {4, 1, 7, 3, 9, 2, 6, 5, 8, 0};
    test_merge_sort_int(values1, 10, "Random Order");

    // Test Case 2: Already sorted numbers
    int values2[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    test_merge_sort_int(values2, 10, "Already Sorted");

    // Test Case 3: Reverse order
    int values3[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    test_merge_sort_int(values3, 10, "Reverse Order");

    // Test Case 4: All elements are the same
    int values4[] = {5, 5, 5, 5, 5, 5, 5, 5, 5, 5};
    test_merge_sort_int(values4, 10, "All Same Elements");

    // Test Case 5: Some repeating elements
    int values5[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    test_merge_sort_int(values5, 10, "Repeating Elements");

    // Test Case 6: Single element list
    int values6[] = {42};
    test_merge_sort_int(values6, 1, "Single Element");

    // Test Case 7: Two elements, already sorted
    int values7[] = {1, 2};
    test_merge_sort_int(values7, 2, "Two Elements Sorted");

    // Test Case 8: Two elements, reversed
    int values8[] = {2, 1};
    test_merge_sort_int(values8, 2, "Two Elements Reversed");

    // Test Case 9: Random unordered floats
    float values9[] = {4.2, 1.1, 7.3, 3.9, 9.8, 2.5, 6.6, 5.4, 8.0, 0.2};
    test_merge_sort_float(values9, 10, "Random Order (Floats)");

    // Test Case 10: Random unordered chars
    char values10[] = {'d', 'a', 'g', 'c', 'j', 'b', 'f', 'e', 'h', 'i'};
    test_merge_sort_char(values10, 10, "Random Order (Chars)");

    return 0;
}