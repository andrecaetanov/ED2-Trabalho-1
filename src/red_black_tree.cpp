#include "red_black_tree.h"
#include <algorithm>
#include <iostream>

using namespace std;

RBTree::RBTree()
{
    this->root = NULL;
}

RBTree::~RBTree()
{
    this->root = NULL;
}

bool RBTree::isEmpty()
{
    if (this->root == NULL)
    {
        return true;
    }
    return false;
}

int RBTree::getHeight(RBTreeNode *node)
{
    int height = 0;
    if (node != NULL)
    {
        int left_height = getHeight(node->getLeft());
        int right_height = getHeight(node->getRight());
        int max_height = max(left_height, right_height);
        height = max_height + 1;
    }
    return height;
}

void RBTree::insert(int key)
{
    RBTreeNode *node = new RBTreeNode(key);
    this->root = auxInsert(node, root);
    cout << root->getKey() << endl;
    //checkRBProperties(node);
}

RBTreeNode *RBTree::auxInsert(RBTreeNode *newNode, RBTreeNode *node)
{
    if (node == NULL)
    {
        cout << "inserted root" << endl;
        return newNode;
    }
    if (newNode->getKey() < node->getKey())
    {
        node->setLeft(auxInsert(newNode, node->getLeft()));
        node->getLeft()->setParent(node);
    }

    else
    {
        node->setRight(auxInsert(newNode, node->getRight()));
        node->getLeft()->setParent(node);
    }
    cout << "inserted node " << node->getKey() << endl;
    return node;
}

RBTreeNode *RBTree::findUncle(RBTreeNode *node)
{
    RBTreeNode *grandParent = node->getParent()->getParent();
    if (grandParent != NULL)
    {
        if (grandParent->getLeft() == node->getParent())
            return grandParent->getRight();
        else
            return grandParent->getLeft();
    }
    else
    {
        return NULL;
    }
}

void RBTree::checkRBProperties(RBTreeNode *node)
{
    RBTreeNode *parent = node->getParent();
    cout << "checking prop" << endl;
    if (parent != NULL)
    {
        while (parent->getColor() == true)
        {
            RBTreeNode *grandParent = parent->getParent();
            RBTreeNode *uncle = this->root;
            if (parent == grandParent->getLeft())
            {
                if (grandParent->getRight() == NULL)
                {
                    grandParent->setRight(uncle);
                }
                if (uncle->getColor() == true)
                {
                    parent->setColor(false);
                    uncle->setColor(false);
                    grandParent->setColor(true);
                    if (grandParent->getKey() != root->getKey())
                    {
                        node = grandParent;
                    }
                    else
                    {
                        break;
                    }
                }
                else if (node == grandParent->getLeft()->getRight())
                {
                    leftRotate(parent);
                }
                else
                {
                    parent->setColor(false);
                    grandParent->setColor(true);
                    rightRotate(grandParent);
                    if (grandParent->getKey() != root->getKey())
                    {
                        node = grandParent;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            else
            {
                if (grandParent->getLeft() == NULL)
                {
                    grandParent->setLeft(uncle);
                }
                if (uncle->getColor() == true)
                {
                    parent->setColor(false);
                    uncle->setColor(false);
                    grandParent->setColor(true);
                    if (grandParent->getKey() != root->getKey())
                    {
                        node = grandParent;
                    }
                    else
                    {
                        break;
                    }
                }
                else if (node == grandParent->getRight()->getLeft())
                {
                    rightRotate(parent);
                }
                else
                {
                    parent->setColor(false);
                    grandParent->setColor(true);
                    leftRotate(grandParent);
                    if (grandParent->getKey() != root->getKey())
                    {
                        node = grandParent;
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }
    }
    root->setColor(false);
}

RBTreeNode *RBTree::search(int key)
{
    RBTreeNode *node = this->root;
    if (node == NULL) //nao encontrou no na árvore, retorna null
    {
        return NULL;
    }
    else
    {
        while (node != NULL)
        {
            if (key == node->getKey()) //No encontrado, retorna o mesmo
                return node;
            else
            {
                if (key < node->getKey())
                    node = node->getLeft();
                else
                    node = node->getRight();
            }
        }
        return NULL;
    }
}

void RBTree::rightRotate(RBTreeNode *node)
{
    RBTreeNode *aux = node->getLeft();
    RBTreeNode *parent = node->getParent();
    node->setLeft(aux->getRight());

    if (aux->getRight() != NULL)
    {
        aux->getRight()->setParent(node);
    }
    aux->setParent(parent);
    if (node->getParent() == nullptr)
    {
        this->root = aux;
    }
    else if (node == node->getParent()->getRight())
    {
        parent->setRight(aux);
    }
    else
    {
        parent->setLeft(aux);
    }
    aux->setRight(node);
    node->setParent(aux);
}

void RBTree::leftRotate(RBTreeNode *node)
{
    RBTreeNode *aux = node->getRight();
    RBTreeNode *parent = node->getParent();
    node->setRight(aux->getLeft());

    if (aux->getLeft() != NULL)
    {
        aux->getLeft()->setParent(node);
    }
    aux->setParent(parent);
    if (node->getParent() == nullptr)
    {
        this->root = aux;
    }
    else if (node == node->getParent()->getLeft())
    {
        parent->setLeft(aux);
    }
    else
    {
        parent->setRight(aux);
    }
    aux->setLeft(node);
    node->setParent(aux);
}

RBTreeNode *RBTree::getRoot()
{
    return this->root;
}

void RBTree::print(RBTreeNode *node)
{
    if (node != NULL)
    {
        cout << "Key: " << node->getKey();
        if (node->getRight() != NULL)
        {
            cout << " Right: " << node->getRight()->getKey() << "RightColor: " << node->getRight()->getColor();
        }
        if (node->getLeft() != NULL)
        {
            cout << " Left: " << node->getLeft()->getKey() << "LeftColor: " << node->getLeft()->getColor();
        }

        cout << endl;

        print(node->getRight());
        print(node->getLeft());
    }
}