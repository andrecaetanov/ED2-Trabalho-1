class RBTreeNode
{
private:
    int key; //book ID
    RBTreeNode *left;
    RBTreeNode *right;
    RBTreeNode *parent;
    bool color; //(false = black, true = red)
    int height;

public:
    RBTreeNode();
    RBTreeNode(int key);
    ~RBTreeNode();
    void setLeft(RBTreeNode *node);
    void setRight(RBTreeNode *node);
    void setParent(RBTreeNode *node);
    void setColor(bool color);
    void setKey(int key);
    RBTreeNode *getLeft();
    RBTreeNode *getRight();
    RBTreeNode *getParent();
    bool getColor();
    int getKey();
    void changeColor();
};