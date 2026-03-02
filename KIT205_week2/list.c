#include <stdio.h>
#include <stdlib.h>
#include "list.h"


// Function to create and return a new empty list.
List new_list() {
	List temp;
	temp.head = NULL;
	return temp;
}

// Function to print the contents of a list.
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

// Function to insert a new node with given data at the front of the list.
void insert_at_front(List* self, int data) {
	ListNodePtr new_node = malloc(sizeof * new_node);

	new_node->data = data;
	new_node->next = self->head;
	self->head = new_node;
}

// Function to insert a new node with given data in the list in ascending order.
void insert_in_order(List* self, int data) {
	ListNodePtr current = self->head;
	ListNodePtr prev = NULL;

	ListNodePtr new_node = malloc(sizeof * new_node);
	new_node->data = data;
	new_node->next = NULL;

	while (current != NULL && current->data < data) {
		prev = current;
		current = current->next;
	}

	if (current == self->head) { // at front
		new_node->next = current;
		self->head = new_node;
	}
	else {                     // middle
		new_node->next = current;
		prev->next = new_node;
	}
}

// Function to delete the first occurrence of a node with given data from the list.
void delete_list(List* self, int data) {
	ListNodePtr current = self->head;
	ListNodePtr prev = NULL;

	while (current != NULL) {
		if (current->data == data) {
			if (prev == NULL) {        // front of list
				self->head = current->next;
				free(current);
				current = self->head;
			}
			else {                    // middle of list
				prev->next = current->next;
				free(current);
				current = prev->next;
			}
		}
		else {
			prev = current;
			current = current->next;
		}
	}
}

// Function to free the memory allocated to a list and all its nodes.
void destroy_list(List* self) {
	ListNodePtr current = self->head;
	while (current != NULL) {
		ListNodePtr to_free = current;
		current = current->next;
		free(to_free);
	}
	self->head = NULL;
}

//Unir test function
void list_test() {
	printf("LIST UNIT TESTS\n");

	printf("Creating list...\n");

	List list1 = new_list() :

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

	// tEST INSERT IN ORDER

	printf("tESTING INSERT IN ORDER\n");

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

	// Test delete_list (front, middle, end, not found)

	printf("TESTING DELETE_LIST\n");

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

	printf("\n");

	destroy_list(&list3);

	printf("All tests complete.\n");
}
//