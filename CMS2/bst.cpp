#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

struct Leaf* initBST(int item) {
    struct Leaf* temp = new Leaf;
    temp->priority = item;
    temp->left = temp->right = NULL;
    return temp;
}

void traverseBST(struct Leaf *root) {
    if (root != NULL) {
        traverseBST(root->left);
        printf("%d \n", root->priority);
        traverseBST(root->right);
    }
}

struct Leaf* insertToBST(struct Leaf* n, int priority) {
    if (n == NULL) return initBST(priority);

    if (priority <= n->priority) {
        n->left = insertToBST(n->left, priority);
    }
    else if (priority > n->priority) {
        n->right = insertToBST(n->right, priority);
    }

    return n;
}

struct Leaf* searchBST(struct Leaf* root, int priority) {
    if (root == NULL || root->priority == priority) {
        return root;
    }

    if (root->priority < priority) {
        return searchBST(root->right, priority);
    }

    return searchBST(root->left, priority);
}
