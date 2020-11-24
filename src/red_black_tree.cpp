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

//checa se a árvore está ou não vazia
bool RBTree::isEmpty()
{
    if (this->root == NULL)
    {
        return true;
    }
    return false;
}

//insere novo nó com chave key
void RBTree::insert(int key)
{
    //checa se árvore está vazia, inserindo assim a raiz
    if (isEmpty())
    {
        root = new RBTreeNode(key);
    }

    //caso a árvore não esteja vazia, insere o nó em uma folha de acordo com sua chave
    else
    {
        RBTreeNode *parent = getRoot();
        RBTreeNode *newNode = new RBTreeNode(key);

        //procura pelo local correto de inserção a partir da raiz
        while (parent != NULL)
        {
            //checa se posição correta é para a esquerda do nó atual
            if (parent->getKey() > key)
            {
                if (parent->getLeft() == NULL)
                {
                    parent->setLeft(newNode);
                    newNode->setColor(true);
                    newNode->setParent(parent);
                    break;
                }
                else
                {
                    parent = parent->getLeft();
                }
            }
            //checa para a direita do nó atual
            else
            {
                if (parent->getRight() == NULL)
                {
                    parent->setRight(newNode);
                    newNode->setColor(true);
                    newNode->setParent(parent);
                    break;
                }
                else
                {
                    parent = parent->getRight();
                }
            }
        }
        checkRBProperties(newNode);
    }
}

//checa propriedades da arvore sempre que um novo nó é inserido
void RBTree::checkRBProperties(RBTreeNode *node)
{
    while (node->getParent()->getColor() == true)
    {
        RBTreeNode *grandparent = node->getParent()->getParent();
        RBTreeNode *uncle = getRoot();

        if (node->getParent() == grandparent->getLeft())
        {
            if (grandparent->getRight())
            {
                uncle = grandparent->getRight();
            }
            if (uncle->getColor() == true)
            {
                node->getParent()->setColor(false);
                uncle->setColor(false);
                grandparent->setColor(true);
                if (grandparent->getKey() != root->getKey())
                {
                    node = grandparent;
                }
                else
                {
                    break;
                }
            }
            else if (node == grandparent->getLeft()->getRight())
            {
                leftRotate(node->getParent());
            }
            else
            {
                node->getParent()->setColor(false);
                grandparent->setColor(true);
                rightRotate(grandparent);
                if (grandparent->getKey() != root->getKey())
                {
                    node = grandparent;
                }
                else
                {
                    break;
                }
            }
        }
        else
        {
            if (grandparent->getLeft())
            {
                uncle = grandparent->getLeft();
            }
            if (uncle->getColor() == true)
            {
                node->getParent()->setColor(false);
                uncle->setColor(false);
                grandparent->setColor(true);
                if (grandparent->getKey() != root->getKey())
                {
                    node = grandparent;
                }
                else
                {
                    break;
                }
            }
            else if (node == grandparent->getRight()->getLeft())
            {
                rightRotate(node->getParent());
            }
            else
            {
                node->getParent()->setColor(false);
                grandparent->setColor(true);
                leftRotate(grandparent);
                if (grandparent->getKey() != root->getKey())
                {
                    node = grandparent;
                }
                else
                {
                    break;
                }
            }
        }
    }
    //garantindo que raiz é sempre preta
    root->setColor(false);
}

//busca por um nó, retornando o próprio caso encontrado ou nulo
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
            if (key == node->getKey())
            {
                //No encontrado, retorna o mesmo
                cout << "Found node! Key: " << node->getKey() << endl;
                return node;
            }
            else
            {
                if (key < node->getKey())
                    node = node->getLeft();
                else
                    node = node->getRight();
            }
        }
        cout << "Node does not exist in the tree" << endl;
        return NULL;
    }
}

//rotação para direita
void RBTree::rightRotate(RBTreeNode *node)
{
    RBTreeNode *newNode = new RBTreeNode();
    if (node->getLeft()->getRight())
    {
        newNode->setLeft(node->getLeft()->getRight());
    }
    newNode->setRight(node->getRight());
    newNode->setKey(node->getKey());
    newNode->setColor(node->getColor());

    node->setKey(node->getLeft()->getKey());
    node->setColor(node->getLeft()->getColor());

    node->setRight(newNode);
    if (newNode->getLeft())
    {
        newNode->getLeft()->setParent(newNode);
    }
    if (newNode->getRight())
    {
        newNode->getRight()->setParent(newNode);
    }
    newNode->setParent(node);

    if (node->getLeft()->getLeft())
    {
        node->setLeft(node->getLeft()->getLeft());
    }
    else
    {
        node->setLeft(NULL);
    }

    if (node->getLeft())
    {
        node->getLeft()->setParent(node);
    }
}

//rotação para esquerda
void RBTree::leftRotate(RBTreeNode *node)
{
    RBTreeNode *newNode = new RBTreeNode();
    if (node->getRight()->getLeft())
    {
        newNode->setRight(node->getRight()->getLeft());
    }
    newNode->setLeft(node->getLeft());
    newNode->setKey(node->getKey());
    newNode->setColor(node->getColor());
    node->setKey(node->getRight()->getKey());
    node->setColor(node->getRight()->getColor());
    node->setLeft(newNode);
    if (newNode->getLeft())
    {
        newNode->getLeft()->setParent(newNode);
    }
    if (newNode->getRight())
    {
        newNode->getRight()->setParent(newNode);
    }
    newNode->setParent(node);

    if (node->getRight()->getRight())
    {
        node->setRight(node->getRight()->getRight());
    }
    else
    {
        node->setRight(NULL);
    }

    if (node->getRight())
    {
        node->getRight()->setParent(node);
    }
}

//retorna raiz da árvore
RBTreeNode *RBTree::getRoot()
{
    return this->root;
}

//imprimir por nível, facilitando leitura
void RBTree::print()
{
    printByLevel(root, 0);
}

void RBTree::printByLevel(RBTreeNode *node, int level)
{
    if (node != NULL)
    {
        cout << "Level " << level << ": ";
        cout << node->getKey();
        if (node->getColor() == false)
        {
            cout << " - Black " << endl;
        }
        else
        {
            cout << " - Red " << endl;
        }

        printByLevel(node->getLeft(), level + 1);
        printByLevel(node->getRight(), level + 1);
    }
}
