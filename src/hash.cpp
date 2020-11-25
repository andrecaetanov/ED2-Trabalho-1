#include "hash.h"
#include <iostream>
#include "math.h"
#include "book.h"
#include "author.h"

using namespace std;

template <typename T>
Hash<T>::Hash()
{
}

template <typename T>
int Hash<T>::getSize()
{
    return size;
}

template <typename T>
int Hash<T>::hashFunction(unsigned long long int k)
{
    return k % size;
}

template <typename T>
void Hash<T>::create(int size)
{
    entries = new List<T> *[size];

    for (int i = 0; i < size; i++)
    {
        entries[i] = NULL;
    }

    this->size = size;
}

template <typename T>
void Hash<T>::insert(T *data)
{
    int hash = hashFunction(data->id);

    if (entries[hash] == NULL)
    {
        entries[hash] = new List<T>();
    }
    else
    {
        T *entity = search(data->id);
        if (entity != NULL)
        {
            entity->frequency++;
            return;
        }
    }

    Node<T> *node = entries[hash]->insert(data);
    data->frequency++;
}

template <typename T>
T *Hash<T>::search(int id)
{
    int hash = hashFunction(id);

    if (entries[hash] != NULL)
    {
        Node<T> *node = entries[hash]->getFirst();

        if (node != NULL)
        {
            T *entity = node->entity;
            if (entity->id == id)
            {
                return entity;
            }

            while (node->next != NULL)
            {
                node = node->next;

                T *entity = node->entity;
                if (entity->id == id)
                {
                    return entity;
                }
            }
        }
    }

    return NULL;
}

template <typename T>
void Hash<T>::read()
{
    cout << "Hash de tamanho " << size << endl;
    for (int i = 0; i < size; i++)
    {
        cout << i << ":";

        List<T> *entry = entries[i];
        if (entry != NULL)
        {
            Node<T> *node = entry->getFirst();
            if (node != NULL)
            {
                cout << " " << node->entity->id;

                while (node->next != NULL)
                {
                    node = node->next;
                    cout << " " << node->entity->id;
                }
            }
        }

        cout << endl;
    }
}

template <typename T>
void Hash<T>::dispose()
{
    for (int i = 0; i < size; i++)
    {
        List<T> *entry = entries[i];
        if (entry != NULL)
        {
            entry->dispose();
        }
    }

    delete entries;
    delete this;
}

template class Hash<Book>;
template class Hash<Author>;