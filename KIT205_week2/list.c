#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

// Create a new empty list
List new_list() {
    List temp;
    temp.head = NULL;
    return temp;
}

// Print the list
void print_list(List* self) {
    ListNodePtr current = self->head;

    while (current != NULL) {
        printf("%d", current->data);
        current = current->next;

        if (current != NULL)
            printf(", ");
    }

    printf("\n");
}

// Insert at front
void insert_at_front(List* self, int data) {
    ListNodePtr new_node = malloc(sizeof * new_node);
    if (new_node == NULL)
        return;

    new_node->data = data;
    new_node->next = self->head;
    self->head = new_node;
}

// Insert in ascending order
void insert_in_order(List* self, int data) {
    ListNodePtr current = self->head;
    ListNodePtr prev = NULL;

    ListNodePtr new_node = malloc(sizeof * new_node);
    if (new_node == NULL)
        return;

    new_node->data = data;
    new_node->next = NULL;

    while (current != NULL && current->data < data) {
        prev = current;
        current = current->next;
    }

    if (prev == NULL) {
        new_node->next = self->head;
        self->head = new_node;
    }
    else {
        new_node->next = current;
        prev->next = new_node;
    }
}

// Delete first occurrence
void delete_list(List* self, int data) {
    ListNodePtr current = self->head;
    ListNodePtr prev = NULL;

    while (current != NULL) {
        if (current->data == data) {

            if (prev == NULL) {
                self->head = current->next;
            }
            else {
                prev->next = current->next;
            }

            free(current);
            return;
        }

        prev = current;
        current = current->next;
    }
}

// Free entire list
void destroy_list(List* self) {
    ListNodePtr current = self->head;

    while (current != NULL) {
        ListNodePtr to_free = current;
        current = current->next;
        free(to_free);
    }

    self->head = NULL;
}

// ===============================
// reverse and merge (NEW FUNCTIONS)
// ===============================

List reverse(List* self) {
    List result = new_list();

    for (ListNodePtr cur = self->head; cur != NULL; cur = cur->next) {
        insert_at_front(&result, cur->data);
    }

    return result;
}

List merge(List* a, List* b) {
    List result = new_list();

    ListNodePtr pa = a->head;
    ListNodePtr pb = b->head;
    ListNodePtr tail = NULL;

    while (pa != NULL && pb != NULL) {
        int pick;

        if (pa->data <= pb->data) {
            pick = pa->data;
            pa = pa->next;
        }
        else {
            pick = pb->data;
            pb = pb->next;
        }

        ListNodePtr node = malloc(sizeof * node);
        if (node == NULL) return result;

        node->data = pick;
        node->next = NULL;

        if (result.head == NULL) {
            result.head = node;
            tail = node;
        }
        else {
            tail->next = node;
            tail = node;
        }
    }

    while (pa != NULL) {
        ListNodePtr node = malloc(sizeof * node);
        if (node == NULL) return result;

        node->data = pa->data;
        node->next = NULL;

        if (result.head == NULL) {
            result.head = node;
            tail = node;
        }
        else {
            tail->next = node;
            tail = node;
        }

        pa = pa->next;
    }

    while (pb != NULL) {
        ListNodePtr node = malloc(sizeof * node);
        if (node == NULL) return result;

        node->data = pb->data;
        node->next = NULL;

        if (result.head == NULL) {
            result.head = node;
            tail = node;
        }
        else {
            tail->next = node;
            tail = node;
        }

        pb = pb->next;
    }

    return result;
}

// ===============================
// Testing reverse and merge
// ===============================

static void test_reverse_and_merge(void) {

    printf("\n===== TESTING reverse =====\n");

    List l = new_list();
    insert_at_front(&l, 5);
    insert_at_front(&l, 3);
    insert_at_front(&l, 7);
    insert_at_front(&l, 2);
    insert_at_front(&l, 0);

    printf("Original: ");
    print_list(&l);

    printf("Expected reversed: 5, 3, 7, 2, 0\n");
    List r = reverse(&l);

    printf("Reversed: ");
    print_list(&r);

    destroy_list(&l);
    destroy_list(&r);

    printf("\n===== TESTING merge =====\n");

    List a = new_list();
    List b = new_list();

    insert_in_order(&a, 1);
    insert_in_order(&a, 3);
    insert_in_order(&a, 5);
    insert_in_order(&a, 7);

    insert_in_order(&b, 2);
    insert_in_order(&b, 3);
    insert_in_order(&b, 6);
    insert_in_order(&b, 8);

    printf("List A: ");
    print_list(&a);
    printf("List B: ");
    print_list(&b);

    printf("Expected merged: 1, 2, 3, 3, 5, 6, 7, 8\n");
    List m = merge(&a, &b);

    printf("Merged:   ");
    print_list(&m);

    destroy_list(&a);
    destroy_list(&b);
    destroy_list(&m);
}

// ===============================
// Menu Ad Hoc Test
// ===============================

static void option_insert(List* my_list) {
    int value;
    printf("Enter a number to insert: ");
    scanf("%d", &value);
    insert_at_front(my_list, value);
}

static void option_delete(List* my_list) {
    int value;
    printf("Enter a number to delete: ");
    scanf("%d", &value);
    delete_list(my_list, value);
}

static void option_print(List* my_list) {
    printf("List: ");
    print_list(my_list);
}

void list_adhoc_test() {

    List my_list = new_list();
    int quit = 0;

    while (!quit) {
        int option;

        printf("\nMenu:\n");
        printf("0 - Quit\n");
        printf("1 - Insert\n");
        printf("2 - Delete\n");
        printf("3 - Print\n");
        printf("Choose option: ");

        scanf("%d", &option);

        if (option == 0) {
            quit = 1;
        }
        else if (option == 1) {
            option_insert(&my_list);
        }
        else if (option == 2) {
            option_delete(&my_list);
        }
        else if (option == 3) {
            option_print(&my_list);
        }
        else {
            printf("Invalid option.\n");
        }
    }

    destroy_list(&my_list);

    // Run additional tests AFTER menu exits
    test_reverse_and_merge();
}