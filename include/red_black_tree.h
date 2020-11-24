#include "red_black_node.h"
#pragma once

class RBTree
{
private:
    RBTreeNode *root;
    bool isEmpty();
    void checkRBProperties(RBTreeNode *node);

public:
    RBTree();
    ~RBTree();
    RBTreeNode *getRoot();
    //void insert(int key);
    void insert(Book *book);
    RBTreeNode *search(int key);
    void leftRotate(RBTreeNode *node);
    void rightRotate(RBTreeNode *node);
    void print();
    void printByRamification(RBTreeNode *node, int level);
};