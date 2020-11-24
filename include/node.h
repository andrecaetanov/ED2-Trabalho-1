template <typename T>
class Node
{
public:
    Node(T *entity);
    T *entity;
    Node<T> *next;
};
