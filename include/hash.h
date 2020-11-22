#include <vector>
#include "entity.h"
#pragma once

using namespace std;

class Hash
{
private:
    int size;
    int hashFunction(unsigned long long int k);

public:
    Hash(int size);
    vector<vector<Entity>> entries;
    void insert(Entity *data);
    void read();
    void destroy();
};