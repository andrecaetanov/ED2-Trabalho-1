template <typename T>
class Node
{
private:
    T *value;
    Node *next;

public:
    Node(T *value);
    T *getValue();
    Node *getNext();
    void setNext(Node *next);
};