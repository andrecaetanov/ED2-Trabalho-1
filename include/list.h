#include "node.h"

template <typename T>
class List
{
private:
    Node<T> *first;

public:
    List();
    Node<T> *getFirst();
    Node<T> *insert(T *entity);
    void dispose();
};
