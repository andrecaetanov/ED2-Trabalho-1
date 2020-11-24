#include "list.h"
#include "entity.h"
#pragma once

using namespace std;

template <typename T>
class Hash
{
private:
    int size;
    int hashFunction(unsigned long long int k);

public:
    Hash();
    List<T> **entries;
    int getSize();
    void create(int size);
    void insert(T *data);
    T *search(int id);
    void read();
    void destroy();
};