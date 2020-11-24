#include "book.h"
#pragma once

class RBTreeNode
{
private:
    Book *book;
    long long unsigned int key; //book ID
    RBTreeNode *left;
    RBTreeNode *right;
    RBTreeNode *parent;
    bool color; //(false = black, true = red)

public:
    RBTreeNode();
    RBTreeNode(Book *book);
    //RBTreeNode(int key);
    ~RBTreeNode();
    void setLeft(RBTreeNode *node);
    void setRight(RBTreeNode *node);
    void setParent(RBTreeNode *node);
    void setColor(bool color);
    void setBook(Book *book);
    void setKey(long long unsigned int key);
    RBTreeNode *getLeft();
    RBTreeNode *getRight();
    RBTreeNode *getParent();
    bool getColor();
    long long unsigned int getKey();
    Book *getBook();
};