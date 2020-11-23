#include "red_black_node.h"

class RBTree
{
private:
    RBTreeNode *root;
    bool isEmpty();
    RBTreeNode *auxInsert(RBTreeNode *newNode, RBTreeNode *node);
    int getHeight(RBTreeNode *node);
    void checkRBProperties(RBTreeNode *node);
    RBTreeNode *findUncle(RBTreeNode *node);

public:
    RBTree();
    ~RBTree();
    RBTreeNode *getRoot();
    void insert(int key);
    RBTreeNode *search(int key);
    void leftRotate(RBTreeNode *node);
    void rightRotate(RBTreeNode *node);
    void print(RBTreeNode *node);
};