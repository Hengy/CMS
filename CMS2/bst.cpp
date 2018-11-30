#include "bst.h"
#include <stdio.h>
#include <stdlib.h>
#include <QDebug>

struct Leaf* initBST(int newKey, void* data) {
    struct Leaf* temp = new Leaf;
    temp->key = newKey;
    temp->left = temp->right = NULL;
    temp->data = data;
    return temp;
}

void traverseBST(struct Leaf *root) {
    if (root != NULL) {
        traverseBST(root->left);

        qDebug() << "Key: " << root->key;

        traverseBST(root->right);
    }
}

struct Leaf* insertToBST(struct Leaf* n, int key, void* data) {
    if (n == NULL) return initBST(key, data);

    if (key <= n->key) {
        n->left = insertToBST(n->left, key, data);
    }
    else if (key > n->key) {
        n->right = insertToBST(n->right, key, data);
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

Leaf* deleteHelper(Leaf* l, Leaf* newBST, int* n, int j) {
    if (l != NULL) {
        newBST = deleteHelper(l->left, newBST, n, j);

        (*n)++;

        if ((*n) != j) {
            if (newBST == NULL) {
                newBST = initBST(l->key, l->data);
            } else {
                insertToBST(newBST, l->key, l->data);
            }
        }

        newBST = deleteHelper(l->right, newBST, n, j);
    }

    return newBST;
}

Leaf* deleteFromBST(Leaf* l, int j) {
    Leaf* newBST = NULL;

    int n = 0;
    int* p = &n;

    newBST = deleteHelper(l, newBST, p, j);

    return newBST;
}
