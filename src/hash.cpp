#include "hash.h"
#include <iostream>
#include "math.h"

using namespace std;

Hash::Hash(int size)
{
    vector<vector<Entity>> entries(size);
    this->entries = entries;
    this->size = size;
}

int Hash::hashFunction(unsigned long long int k)
{
    double a = (sqrt(5) - 1) / 2;
    long double ka = k * a;
    double kamod = modf(ka, &kamod);
    int hash = (int)floor(this->size * kamod);
    return hash;
}

void Hash::insert(Entity *data)
{
    int hash = hashFunction(data->id);

    for (Entity entity : this->entries[hash])
    {
        if (entity.id == data->id)
        {
            return;
        }
    }

    this->entries[hash].push_back(*data);
}

void Hash::read()
{
    cout << "Hash of size " << this->size << endl;

    for (int i = 0; i < this->size; i++)
    {
        cout << i << ":";

        for (Entity entity : this->entries[i])
        {
            cout << " " << entity.id;
        }

        cout << endl;
    }
}