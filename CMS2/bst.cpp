#include "bst.h"
#include <stdio.h>
#include <stdlib.h>
#include <QDebug>

struct Leaf* initBST(int item) {
    struct Leaf* temp = new Leaf;
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

void traverseBST(struct Leaf *root) {
    if (root != NULL) {
        traverseBST(root->left);

        qDebug() << "Key: " << root->key;

        traverseBST(root->right);
    }
}

struct Leaf* insertToBST(struct Leaf* n, int key) {
    if (n == NULL) return initBST(key);

    if (key <= n->key) {
        n->left = insertToBST(n->left, key);
    }
    else if (key > n->key) {
        n->right = insertToBST(n->right, key);
    }

    return n;
}

struct Leaf* searchBST(struct Leaf* root, int key) {
    if (root == NULL || root->key == key) {
        return root;
    }

    if (root->key <= key) {
        return searchBST(root->right, key);
    }

    return searchBST(root->left, key);
}

int sizeOfBST(struct Leaf* root) {
    if(root == NULL) return 0;
    else {
        return (sizeOfBST(root->left) + 1 + sizeOfBST(root->right));
    }
}
