#include "red_black_node.h"
#include "search_trees_stats.h"
#pragma once

class RBTree
{
private:
    RBTreeNode *root;
    bool isEmpty();
    void checkRBProperties(RBTreeNode *node, int *comparisons, int *dataMovement);

public:
    RBTree();
    ~RBTree();
    RBTreeNode *dispose(RBTreeNode *node);
    RBTreeNode *getRoot();
    void insert(Book *book, int *comparisons, int *dataMovement);
    RBTreeNode *search(long long unsigned int key, int *comparisons);
    void leftRotate(RBTreeNode *node);
    void rightRotate(RBTreeNode *node);
    void print();
    void printByRamification(RBTreeNode *node, int level);
};