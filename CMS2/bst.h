#pragma once

#ifndef BST_H
#define BST_H

#include "L2L.h"

struct Leaf {
    int key;
    void *data;
    struct Leaf *right, *left;
};

struct Leaf* initBST(int item);

void traverseBST(struct Leaf *root);

struct Leaf* insertToBST(struct Leaf* n, int key);

struct Leaf* searchBST(struct Leaf* root, int key);

int sizeOfBST(struct Leaf* root);

#endif // BST_H
