#pragma once

// Definition of a singly linked list node
typedef struct listNode {
    int data;
    struct listNode* next;
} *ListNodePtr;

// Definition of a singly linked list
typedef struct list {
    ListNodePtr head;
} List;

// Function declarations
List new_list();
void print_list(List* self);
void insert_at_front(List* self, int data);
void insert_in_order(List* self, int data);
void delete_list(List* self, int data);
void destroy_list(List* self);
void list_test();
void list_adhoc_test();
