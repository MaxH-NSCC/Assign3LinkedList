#include "linked_list.h"
#include <stddef.h>
#include <stdlib.h>

// Linked list structures
struct LinkedListNode {
    void * data;
    struct LinkedListNode * next;
};

struct LinkedList {
    size_t size;
    struct LinkedListNode * head;
    struct LinkedListNode * tail;
};

// Linked list functions

// Creates and initializes an empty linked list
LinkedList *list_create(void) {
    // create and return an empty linked list:
    LinkedList * list = malloc(sizeof(LinkedList));
    if (list == NULL) {
        return NULL;
    }
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
    return list;
};

// Inserts a new node at the end of the list
// returns 0 on success. -1 on failure
int list_add(LinkedList *list, void *data) {
    if (list == NULL) return -1;

    LinkedListNode * new_node = malloc(sizeof(LinkedListNode));
    if (new_node == NULL) return -1;

    new_node->data = data;
    new_node->next = NULL;

    if (list->size == 0) {
        list->head = new_node;
    } else {
        list->tail->next = new_node;
    }
    list->tail = new_node;
    list->size++;
    return 0;
};

// Inserts a new node at a specific index (0-based)
// Returns 0 if successful, -1 if index is out of bounds
int list_insert_at(LinkedList *list, size_t index, void *data) {
    if (list == NULL || index > list->size) return -1;

    LinkedListNode * new_node = malloc(sizeof(LinkedListNode));
    if (new_node == NULL) return -1;
    new_node->data = data;

    if (index == 0) {
        new_node->next = list->head;
        list->head = new_node;
    } else {
        LinkedListNode * cursor = list->head;

        for (size_t i = 0; i < index - 1; i++){
            cursor = cursor->next;
        }

        new_node->next = cursor->next;
        cursor->next = new_node;
    }

    list->size++;
    return 0;
};

// fetches an element at specified index
// returns 0 on success, -1 on failure
int list_get_at(LinkedList *list, size_t index, void **out_data) {
    if (list == NULL || out_data == NULL || index >= list->size) return -1;

    LinkedListNode * cursor = list->head;

    for (size_t i = 0; i < index; i++){
        cursor = cursor->next;
    }

    *out_data = cursor->data;
    return 0;
};

// Removes and returns the element at a specific index
// returns 0 on sucsess, -1 on failure
int list_remove_at(LinkedList *list, size_t index, void **out_data) {
    if (list == NULL || index >= list->size) return -1;

    LinkedListNode * cursor = list->head;
    LinkedListNode * removed_node;

    if (index == 0) {
        removed_node = list->head;
        list->head = list->head->next;
        if (list->size == 1) {
            list->tail = NULL;
        }

    } else {
        for (size_t i = 0; i < index -1; i++) {
            cursor = cursor->next;
        }
        removed_node = cursor->next;
        cursor->next = removed_node->next;

        if (list->size == 1) {
            list->tail = cursor->next;
        }
    }

    *out_data = removed_node->data;
    list->size--;
    free(removed_node);
    return 0;
};

// Returns the size of the list
size_t list_size(const LinkedList *list) {
    if (list == NULL) return -1;
    return list->size;
};

// Frees all nodes and also applies a free function to stored data
// if NULL is passed in for the function pointer it does not free any data
// and only frees the list itself.
void list_destroy(LinkedList *list, void (*free_func)(void *)) {
    if (list == NULL) return;

    if (list->size == 0) {
        free(list);
        return;
    }

    if (list->size == 1) {
        if (free_func != NULL) {
            free_func(list->head->data);
        }
        free(list->head);
        free(list);
        return;
    }

    LinkedListNode * cursor = list->head;
    while (cursor != NULL) {
        LinkedListNode * to_delete = cursor;
        cursor = cursor->next;

        if (free_func != NULL) {
            free_func(to_delete->data);
        }
        free(to_delete);
    }
    free(list);
};

// Linked list iterator functions

// the linked list iterator is an "object" that
// helps us move from one item to the next item
// efficiently, but without exposing the internal components of the
// linked list itself.
typedef struct ListIterator {
    LinkedListNode * cursor;
    LinkedList * list;
} ListIterator;

// Creates an iterator for the given list starting at the first element
ListIterator *list_iterator_create(LinkedList *list) {
    if (list == NULL) return NULL;
    ListIterator * iter = malloc(sizeof(ListIterator));
    if (iter == NULL) return NULL;

    iter->cursor = list->head;
    iter->list = list;
    return iter;
};

// Advances the iterator and retrieves the next element
// Returns 1 if there is a next element, 0 if the end of the list is reached
int list_iterator_next(ListIterator *iter, void **out_data) {
    if (iter == NULL) return -1;
    iter->cursor = iter->cursor->next;
    if (iter->cursor->next == NULL) {
        *out_data = iter->cursor->data;
        return 0;
    } else {
        *out_data = iter->cursor->data;
        return 1;
    }
};

// Resets the iterator to the start of the list
void list_iterator_reset(ListIterator *iter) {
    if (iter == NULL) return;
    iter->cursor = iter->list->head;
};

// Destroys the iterator and frees any allocated memory
// notice this has nothing to do with the list that this iterator is pointing to
void list_iterator_destroy(ListIterator *iter) {
    if (iter == NULL) return;
    free(iter);
};

// Compares two ints returning 1 if a is greater, -1 if b is greater and 0 if neither of those are true
// casts void pointers to ints so it can be compared and returns the results
int compare_ints(const void *a, const void *b) {
    int *int_a = (int*)a;
    int *int_b = (int*)b;
    if (*int_a > *int_b) {
        return 1;
    } else if (*int_a < *int_b) {
        return -1;
    } else {
        return 0;
    }
}

int compare_chars();

int compare_floats();

// Merge two linked lists into one sorted list
// Takes two list nodes left and right that represent sorted lists
// Recursively merge the nodes together in order
// Function uses comparison function compare to determine the sorting type and returns the proper sorting order
// Returns the head of the sorted list
LinkedListNode *merge_sorted_lists(LinkedListNode *left, LinkedListNode *right, int (*compare)(const void *, const void *)) {
    if (left == NULL) return right;
    if (right == NULL) return left;

    LinkedListNode *result = NULL;

    if (compare(left->data, right->data) <= 0) {
        result = left;
        result->next = merge_sorted_lists(left->next, right, compare);
    } else {
        result = right;
        result->next = merge_sorted_lists(left, right->next, compare);
    }

    return result;
};

// Split linked list into two halves
// First half is 1/2 the size of the linked list other half is the remaining nodes
// Centre position is calculated by getting size/2
// Finds the middle of the linked list by iterating through it until it reaches the centre
// Split list at middle point
void split_list(LinkedListNode *head, LinkedListNode **left, LinkedListNode **right) {
    if (head == NULL || head->next == NULL) {
        *left = head;
        *right = NULL;
        return;
    }

    LinkedListNode *cursor = head;
    size_t count = 0;

    while (cursor != NULL) {
        count++;
        cursor = cursor->next;
    }

    size_t mid = count / 2;
    cursor = head;

    for (size_t i = 0; i < mid - 1; i++) {
        cursor = cursor->next;
    }

    *left = head;
    *right = cursor->next;
    cursor->next = NULL;
};

// Recursively sorts the linked list using merge sort
// If the list is empty or only has one node, return it
// if larger split the list, recursively sort both halves, then merge.
LinkedListNode *merge_sort_nodes(LinkedListNode *head, int (*compare)(const void *, const void *)) {
    if (head == NULL || head->next == NULL) {
        return head;
    }

    LinkedListNode *left;
    LinkedListNode *right;

    split_list(head, &left, &right);

    left = merge_sort_nodes(left, compare);
    right = merge_sort_nodes(right, compare);

    return merge_sorted_lists(left, right, compare);
};

// Sorts a linked list using the merge sort
void list_merge_sort(LinkedList *list, int (*compare)(const void *, const void *)) {
    if (list == NULL || list->head == NULL || list->size < 2) {
        return;
    }

    list->head = merge_sort_nodes(list->head, compare);

    LinkedListNode *current = list->head;
    while (current->next != NULL) {
        current = current->next;
    }
    list->tail = current;
};