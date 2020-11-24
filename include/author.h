#include <iostream>
#include "entity.h"
#pragma once

using namespace std;

class Author : public Entity
{
public:
    Author();
    string name;
    int getSortingParameter();
};