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

    if (prev == NULL) {  // insert at front (or empty list)
        new_node->next = self->head;
        self->head = new_node;
    }
    else {               // insert middle or end
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

            if (prev == NULL) {  // deleting front
                self->head = current->next;
            }
            else {               // deleting middle or end
                prev->next = current->next;
            }

            free(current);
            return;  // stop after first delete
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

// Unit tests
void list_test() {

    printf("===== LIST UNIT TESTS =====\n\n");

    // Test insert_at_front
    printf("Testing insert_at_front...\n");

    List list1 = new_list();

    insert_at_front(&list1, 5);
    insert_at_front(&list1, 3);
    insert_at_front(&list1, 7);
    insert_at_front(&list1, 2);
    insert_at_front(&list1, 0);

    printf("Expected: 0, 2, 7, 3, 5\n");
    printf("Result:   ");
    print_list(&list1);
    printf("\n");

    destroy_list(&list1);


    // Test insert_in_order
    printf("Testing insert_in_order...\n");

    List list2 = new_list();

    insert_in_order(&list2, 5);
    insert_in_order(&list2, 3);
    insert_in_order(&list2, 7);
    insert_in_order(&list2, 2);
    insert_in_order(&list2, 0);

    printf("Expected: 0, 2, 3, 5, 7\n");
    printf("Result:   ");
    print_list(&list2);
    printf("\n");

    destroy_list(&list2);


    // Test delete_list
    printf("Testing delete_list...\n");

    List list3 = new_list();

    insert_in_order(&list3, 1);
    insert_in_order(&list3, 2);
    insert_in_order(&list3, 3);
    insert_in_order(&list3, 4);
    insert_in_order(&list3, 5);

    printf("Original: ");
    print_list(&list3);

    printf("Delete 1 (front)\n");
    delete_list(&list3, 1);
    print_list(&list3);

    printf("Delete 3 (middle)\n");
    delete_list(&list3, 3);
    print_list(&list3);

    printf("Delete 5 (end)\n");
    delete_list(&list3, 5);
    print_list(&list3);

    printf("Delete 99 (not found)\n");
    delete_list(&list3, 99);
    print_list(&list3);

    destroy_list(&list3);

    printf("\nAll tests complete.\n");
}




// Ad hoc testing - v2 (menu + option_* functions)


// helper functions 

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

// Updated ad hoc test using menu
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
}
