#include <stdio.h>
#include "bst.h"

int main(void) {
    bst_test();

    printf("\nNow running ad hoc BST test...\n");
    bst_adhoc_test();

    return 0;
}