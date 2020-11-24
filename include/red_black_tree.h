#include "red_black_node.h"

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
    void insert(int key);
    RBTreeNode *search(int key);
    void leftRotate(RBTreeNode *node);
    void rightRotate(RBTreeNode *node);
    void print();
    void printByLevel(RBTreeNode *node, int level);
};