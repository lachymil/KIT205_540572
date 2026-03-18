#pragma once
#pragma once

/**
 * @struct bstNode
 * @brief Represents a single node in a binary search tree
 *
 * Contains an integer data item and pointers to its left and right children.
 */
typedef struct bstNode {
    int data_item;
    struct bstNode* left;
    struct bstNode* right;
} *BSTNodePtr;

/**
 * @struct bst
 * @brief Represents a binary search tree
 *
 * Contains a pointer to the root node of the BST.
 */
typedef struct bst {
    BSTNodePtr root;
} BST;

/**
 * @brief Creates a new, empty binary search tree
 *
 * @return The new binary search tree
 */
BST new_bst();

/**
 * @brief Finds a node with a given data item in a binary search tree
 *
 * @param self Pointer to the binary search tree to search
 * @param n The data item to search for
 *
 * @return Pointer to the node with the given data item, or NULL if it is not found
 */
BSTNodePtr find_bst(BST* self, int n);

/**
 * @brief Inserts a node with a given data item into a binary search tree
 *
 * @param self Pointer to the binary search tree to insert into
 * @param n The data item to insert
 */
void insert_bst(BST* self, int n);

/**
 * @brief Deletes a node with a given data item from a binary search tree
 *
 * @param self Pointer to the binary search tree to delete from
 * @param n The data item to delete
 */
void delete_bst(BST* self, int n);

/**
 * @brief Prints the data items of a binary search tree in ascending order
 *
 * @param self Pointer to the binary search tree to print
 */
void print_in_order_bst(BST* self);

/**
 * @brief Prints the tree in pre-order
 *
 * @param self Pointer to the binary search tree to print
 */
void print_pre_order_bst(BST* self);

/**
 * @brief Prints the tree in post-order
 *
 * @param self Pointer to the binary search tree to print
 */
void print_post_order_bst(BST* self);

/**
 * @brief Returns the height of the BST
 *
 * @param self Pointer to the binary search tree
 * @return Height of the tree
 */
int height_bst(BST* self);

/**
 * @brief Frees all memory allocated for a binary search tree
 *
 * @param self Pointer to the binary search tree to destroy
 */
void destroy_bst(BST* self);

/**
 * @brief Interactive test function
 */
void bst_adhoc_test();

/**
 * @brief Unit-style test function
 */
void bst_test();