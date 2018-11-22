#pragma once

#ifndef BST_H
#define BST_H

struct Leaf {
    int priority;
    void *data;
    struct Leaf *right, *left;
};

#endif // BST_H
