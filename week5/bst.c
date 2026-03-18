#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "bst.h"

// create an empty bst
BST new_bst() {
    BST temp;
    temp.root = NULL;
    return temp;
}

// recursive function to find a value and return the containing node
static BSTNodePtr find_bst_node(BSTNodePtr self, int n) {
    if (self == NULL || n == self->data_item) {
        return self;
    }
    else if (n < self->data_item) {
        return find_bst_node(self->left, n);
    }
    else {
        return find_bst_node(self->right, n);
    }
}

// find a value in the tree and return the node
BSTNodePtr find_bst(BST* self, int n) {
    return find_bst_node(self->root, n);
}

// recursive function to insert a value
static BSTNodePtr insert_bst_node(BSTNodePtr self, int n) {
    if (self == NULL) {
        self = malloc(sizeof * self);
        if (self == NULL) {
            return NULL;
        }
        self->data_item = n;
        self->left = NULL;
        self->right = NULL;
    }
    else if (n < self->data_item) {
        self->left = insert_bst_node(self->left, n);
    }
    else if (n > self->data_item) {
        self->right = insert_bst_node(self->right, n);
    }
    // duplicate values are ignored
    return self;
}

// insert a value into the tree
void insert_bst(BST* self, int n) {
    self->root = insert_bst_node(self->root, n);
}

// helper function for delete
static BSTNodePtr min_node(BSTNodePtr self) {
    BSTNodePtr current = self;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

// recursive function to delete a value
static BSTNodePtr delete_bst_node(BSTNodePtr self, int n) {
    if (self != NULL) {
        if (n == self->data_item) {
            // found item
            if (self->left != NULL && self->right != NULL) {
                // two child case
                BSTNodePtr successor = min_node(self->right);
                self->data_item = successor->data_item;
                self->right = delete_bst_node(self->right, self->data_item);
            }
            else {
                // one or zero child case
                BSTNodePtr to_free = self;
                if (self->left != NULL) {
                    self = self->left;
                }
                else {
                    self = self->right;
                }
                free(to_free);
            }
        }
        else if (n < self->data_item) {
            self->left = delete_bst_node(self->left, n);
        }
        else {
            self->right = delete_bst_node(self->right, n);
        }
    }
    return self;
}

// delete a value from the tree
void delete_bst(BST* self, int n) {
    self->root = delete_bst_node(self->root, n);
}

// recursive function to print in-order
static void print_in_order_bst_node(BSTNodePtr self) {
    if (self == NULL) {
        printf("_");
    }
    else {
        printf("(");
        print_in_order_bst_node(self->left);
        printf(" %d ", self->data_item);
        print_in_order_bst_node(self->right);
        printf(")");
    }
}

// print the tree in-order
void print_in_order_bst(BST* self) {
    print_in_order_bst_node(self->root);
}

// recursive function to print pre-order
static void print_pre_order_bst_node(BSTNodePtr self) {
    if (self == NULL) {
        printf("_");
    }
    else {
        printf("(");
        printf(" %d ", self->data_item);
        print_pre_order_bst_node(self->left);
        print_pre_order_bst_node(self->right);
        printf(")");
    }
}

// print the tree in pre-order
void print_pre_order_bst(BST* self) {
    print_pre_order_bst_node(self->root);
}

// recursive function to print post-order
static void print_post_order_bst_node(BSTNodePtr self) {
    if (self == NULL) {
        printf("_");
    }
    else {
        printf("(");
        print_post_order_bst_node(self->left);
        print_post_order_bst_node(self->right);
        printf(" %d ", self->data_item);
        printf(")");
    }
}

// print the tree in post-order
void print_post_order_bst(BST* self) {
    print_post_order_bst_node(self->root);
}

// recursive height function
static int height_bst_node(BSTNodePtr self) {
    if (self == NULL) {
        return -1;   // empty tree has height -1
    }

    int left_height = height_bst_node(self->left);
    int right_height = height_bst_node(self->right);

    if (left_height > right_height) {
        return left_height + 1;
    }
    else {
        return right_height + 1;
    }
}

// public height function
int height_bst(BST* self) {
    return height_bst_node(self->root);
}

// recursive function to destroy all nodes
static void destroy_bst_node(BSTNodePtr self) {
    if (self != NULL) {
        destroy_bst_node(self->left);
        self->left = NULL;
        destroy_bst_node(self->right);
        self->right = NULL;
        free(self);
    }
}

// destroy the tree
void destroy_bst(BST* self) {
    destroy_bst_node(self->root);
    self->root = NULL;
}

// ad hoc interactive test
void bst_adhoc_test() {
    BST tree = new_bst();
    int quit = 0;
    int data;

    while (quit == 0) {
        printf("Enter some data (0 to stop): ");
        scanf("%d", &data);

        if (data != 0) {
            insert_bst(&tree, data);
        }
        else {
            quit = 1;
        }
    }

    printf("\nIn-order:   ");
    print_in_order_bst(&tree);
    printf("\n");

    printf("Pre-order:  ");
    print_pre_order_bst(&tree);
    printf("\n");

    printf("Post-order: ");
    print_post_order_bst(&tree);
    printf("\n");

    printf("Height: %d\n", height_bst(&tree));

    destroy_bst(&tree);
}

// unit-style tests
void bst_test() {
    BST tree = new_bst();

    // new tree tests
    assert(tree.root == NULL);
    assert(find_bst(&tree, 99) == NULL);
    assert(height_bst(&tree) == -1);

    // insert tests
    insert_bst(&tree, 50);
    assert(tree.root != NULL);
    assert(tree.root->data_item == 50);
    assert(height_bst(&tree) == 0);

    insert_bst(&tree, 30);
    insert_bst(&tree, 70);
    insert_bst(&tree, 20);
    insert_bst(&tree, 40);
    insert_bst(&tree, 60);
    insert_bst(&tree, 80);

    assert(find_bst(&tree, 50) != NULL);
    assert(find_bst(&tree, 30) != NULL);
    assert(find_bst(&tree, 70) != NULL);
    assert(find_bst(&tree, 20) != NULL);
    assert(find_bst(&tree, 40) != NULL);
    assert(find_bst(&tree, 60) != NULL);
    assert(find_bst(&tree, 80) != NULL);
    assert(find_bst(&tree, 999) == NULL);

    assert(height_bst(&tree) == 2);

    // duplicate insert should do nothing
    insert_bst(&tree, 70);
    assert(height_bst(&tree) == 2);

    printf("Initial tree in-order:   ");
    print_in_order_bst(&tree);
    printf("\n");

    printf("Initial tree pre-order:  ");
    print_pre_order_bst(&tree);
    printf("\n");

    printf("Initial tree post-order: ");
    print_post_order_bst(&tree);
    printf("\n");

    // delete leaf node
    delete_bst(&tree, 20);
    assert(find_bst(&tree, 20) == NULL);

    // delete node with one child
    delete_bst(&tree, 30);
    assert(find_bst(&tree, 30) == NULL);

    // delete node with two children
    delete_bst(&tree, 70);
    assert(find_bst(&tree, 70) == NULL);

    // delete root
    delete_bst(&tree, 50);
    assert(find_bst(&tree, 50) == NULL);

    // delete non-existent value
    delete_bst(&tree, 999);

    printf("Tree after deletions in-order:   ");
    print_in_order_bst(&tree);
    printf("\n");

    printf("Tree after deletions pre-order:  ");
    print_pre_order_bst(&tree);
    printf("\n");

    printf("Tree after deletions post-order: ");
    print_post_order_bst(&tree);
    printf("\n");

    destroy_bst(&tree);
    assert(tree.root == NULL);
    assert(height_bst(&tree) == -1);

    printf("All BST tests passed.\n");
}