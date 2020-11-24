#include "red_black_node.h"
#include <iostream>

using namespace std;

RBTreeNode::RBTreeNode()
{
    this->left = NULL;
    this->right = NULL;
    this->color = false; //(false == black)
    this->parent = NULL;
}

RBTreeNode::RBTreeNode(int key)
{
    this->left = NULL;
    this->right = NULL;
    this->color = false;
    this->key = key;
    this->parent = NULL;
}

RBTreeNode::~RBTreeNode()
{
    this->left = NULL;
    this->right = NULL;
    this->color = false;
}

void RBTreeNode::setLeft(RBTreeNode *node)
{
    this->left = node;
}

void RBTreeNode::setRight(RBTreeNode *node)
{
    this->right = node;
}

void RBTreeNode::setParent(RBTreeNode *node)
{
    this->parent = node;
}

void RBTreeNode::setColor(bool color)
{
    this->color = color;
}

void RBTreeNode::setKey(int key)
{
    this->key = key;
}

RBTreeNode *RBTreeNode::getLeft()
{
    return this->left;
}

RBTreeNode *RBTreeNode::getRight()
{
    return this->right;
}

RBTreeNode *RBTreeNode::getParent()
{
    return this->parent;
}

bool RBTreeNode::getColor()
{
    return this->color;
}

int RBTreeNode::getKey()
{
    return this->key;
}