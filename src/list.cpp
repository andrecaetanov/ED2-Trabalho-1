#include <iostream>
#include "list.h"
#include "book.h"
#include "author.h"

template <typename T>
List<T>::List()
{
    this->first = NULL;
}

template <typename T>
Node<T> *List<T>::getFirst()
{
    return this->first;
}

template <typename T>
Node<T> *List<T>::insert(T *entity)
{
    Node<T> *node = first;
    Node<T> *newNode = new Node<T>(entity);

    if (node == NULL)
    {
        first = newNode;
    }
    else
    {
        while (node->next != NULL)
        {
            node = node->next;
        }

        node->next = newNode;
    }

    return newNode;
}

template <typename T>
void List<T>::dispose()
{
    Node<T> *node = getFirst();
    if (node != NULL)
    {
        while (node->next != NULL)
        {
            Node<T> *nextNode = node->next;
            delete node;
            node = nextNode;
        }
    }

    delete this;
}

template class List<Book>;
template class List<Author>;