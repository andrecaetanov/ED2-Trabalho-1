#include "red_black_tree.h"
#include <algorithm>
#include <iostream>

using namespace std;

RBTree::RBTree()
{
    this->root = NULL;
}

//destrutor com liberacao da arvore
RBTree::~RBTree()
{
    this->root = dispose(root);
}

RBTreeNode *RBTree::dispose(RBTreeNode *node)
{
    if (node != NULL)
    {
        node->setLeft(dispose(node->getLeft()));
        node->setRight(dispose(node->getRight()));
        node = NULL;
    }
    return NULL;
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
void RBTree::insert(Book *book, int *comparisons, int *dataMovement)
{
    cout << "Inserting book: " << book->id << endl;
    //checa se árvore está vazia, inserindo assim a raiz
    if (isEmpty())
    {
        root = new RBTreeNode(book);
    }

    //caso a árvore não esteja vazia, insere o nó em uma folha de acordo com sua chave
    else
    {
        RBTreeNode *parent = getRoot();
        RBTreeNode *newNode = new RBTreeNode(book);
        //procura pelo local correto de inserção a partir da raiz
        while (parent != NULL)
        {
            //checa se posição correta é para a esquerda do nó atual
            *comparisons = *comparisons + 1;
            if (parent->getKey() > book->id)
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
        checkRBProperties(newNode, comparisons, dataMovement);
    }
}

//checa propriedades da arvore sempre que um novo nó é inserido
void RBTree::checkRBProperties(RBTreeNode *node, int *comparisons, int *dataMovement)
{
    while (node->getParent()->getColor() == true)
    {
        RBTreeNode *grandparent = node->getParent()->getParent();
        RBTreeNode *uncle = getRoot();

        //realiza checagem se o pai é o filho da esquerda do avô
        if (node->getParent() == grandparent->getLeft())
        {
            //se existe um filho a direita do avô, esse é o tio
            if (grandparent->getRight())
            {
                uncle = grandparent->getRight();
            }
            //caso a cor do pai e do tio sejam vermelhos, altera as cores
            if (uncle->getColor() == true)
            {
                node->getParent()->setColor(false);
                uncle->setColor(false);
                grandparent->setColor(true);
                *comparisons = *comparisons + 1;
                //verifica proximidade da raiz
                if (grandparent->getKey() != root->getKey())
                {
                    node = grandparent;
                }
                else
                {
                    break;
                }
            }
            //caso a cor do tio não seja vermelha, realiza rotação de acordo com as propriedades
            //se o no estiver na subarvore esquerda do avo
            else if (node == grandparent->getLeft()->getRight())
            {
                *dataMovement = *dataMovement + 1;
                leftRotate(node->getParent());
            }
            else
            {
                node->getParent()->setColor(false);
                grandparent->setColor(true);
                *dataMovement = *dataMovement + 1;
                rightRotate(grandparent);
                *comparisons = *comparisons + 1;
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
        //realiza checagem se o pai é o filho da direita do avô
        else
        {
            //se existe um filho a esquerda do avô, esse é o tio
            if (grandparent->getLeft())
            {
                uncle = grandparent->getLeft();
            }
            if (uncle->getColor() == true)
            {
                node->getParent()->setColor(false);
                uncle->setColor(false);
                grandparent->setColor(true);
                *comparisons = *comparisons + 1;
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
                *dataMovement = *dataMovement + 1;
                rightRotate(node->getParent());
            }
            else
            {
                node->getParent()->setColor(false);
                grandparent->setColor(true);
                *dataMovement = *dataMovement + 1;
                leftRotate(grandparent);
                *comparisons = *comparisons + 1;
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
RBTreeNode *RBTree::search(long long unsigned int key, int *comparisons)
{
    RBTreeNode *node = this->root;
    if (node == NULL) //nao encontrou no na árvore, retorna null
    {
        cout << "Node does not exist in the tree" << endl;
        return NULL;
    }
    else
    {
        //continua percorrendo enquanto não encontrou nó
        while (node != NULL)
        {
            *comparisons = *comparisons + 1;
            if (key == node->getKey())
            {
                //No encontrado, retorna o mesmo
                cout << "Found node! Key: " << node->getKey() << endl;
                return node;
            }
            else
            {
                *comparisons = *comparisons + 1;
                if (key < node->getKey())
                {
                    node = node->getLeft();
                }
                else
                {
                    node = node->getRight();
                }
            }
        }
        return NULL;
    }
}

//rotação para direita
void RBTree::rightRotate(RBTreeNode *node)
{
    RBTreeNode *aux = new RBTreeNode();
    if (node->getLeft()->getRight())
    {
        aux->setLeft(node->getLeft()->getRight());
    }
    aux->setBook(node->getBook());
    aux->setColor(node->getColor());
    aux->setRight(node->getRight());

    node->setBook(node->getLeft()->getBook());
    node->setColor(node->getLeft()->getColor());
    node->setRight(aux);

    if (aux->getLeft())
    {
        aux->getLeft()->setParent(aux);
    }
    if (aux->getRight())
    {
        aux->getRight()->setParent(aux);
    }
    aux->setParent(node);

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
    RBTreeNode *aux = new RBTreeNode();
    if (node->getRight()->getLeft())
    {
        aux->setRight(node->getRight()->getLeft());
    }
    aux->setBook(node->getBook());
    aux->setColor(node->getColor());
    aux->setLeft(node->getLeft());

    node->setBook(node->getRight()->getBook());
    node->setColor(node->getRight()->getColor());
    node->setLeft(aux);

    if (aux->getLeft())
    {
        aux->getLeft()->setParent(aux);
    }
    if (aux->getRight())
    {
        aux->getRight()->setParent(aux);
    }
    aux->setParent(node);

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
    printByRamification(root, 0);
}

void RBTree::printByRamification(RBTreeNode *node, int level)
{
    if (node != NULL)
    {
        cout << "Level " << level << ": ";
        cout << node->getBook()->id;
        if (node->getColor() == false)
        {
            cout << " - Black " << endl;
        }
        else
        {
            cout << " - Red " << endl;
        }

        printByRamification(node->getLeft(), level + 1);
        printByRamification(node->getRight(), level + 1);
    }
}
