#include <iostream>
#include "list.h"
#include "book.h"

template <typename T>
List<T>::List()
{
    first = NULL;
}

template <typename T>
Node<T> *List<T>::getFirst()
{
    return first;
}

template <typename T>
Node<T> *List<T>::insert(T *value)
{
    Node<T> *node = first;
    Node<T> *newNode = new Node<T>(value);

    if (node == NULL)
    {
        first = newNode;
    }
    else
    {
        while (node->getNext() != NULL)
        {
            node = node->getNext();
        }

        node->setNext(newNode);
    }

    return newNode;
}

template <typename T>
void List<T>::destroy()
{
    Node<T> *node = getFirst();
    if (node != NULL)
    {
        while (node->getNext() != NULL)
        {
            Node<T> *nextNode = node->getNext();
            delete node;
            node = nextNode;
        }
    }
}

template class List<Book>;