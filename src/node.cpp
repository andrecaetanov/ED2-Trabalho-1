#include <iostream>
#include "node.h"
#include "book.h"

template <typename T>
Node<T>::Node(T *value)
{
    this->value = value;
    next = NULL;
}

template <typename T>
T *Node<T>::getValue()
{
    return value;
}

template <typename T>
Node<T> *Node<T>::getNext()
{
    return next;
}

template <typename T>
void Node<T>::setNext(Node<T> *next)
{
    this->next = next;
}

template class Node<Book>;