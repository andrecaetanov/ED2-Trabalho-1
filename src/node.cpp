#include "node.h"
#include "book.h"
#include "author.h"

template <typename T>
Node<T>::Node(T *entity)
{
    this->entity = entity;
    next = NULL;
}

template class Node<Book>;
template class Node<Author>;