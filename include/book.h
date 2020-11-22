#include <iostream>
#include <vector>
#include "entity.h"
#pragma once

using namespace std;

class Book : public Entity
{
public:
    Book();
    vector<int> authors;
    string bestsellersRank;
    string categories;
    string edition;
    string isbn10;
    string isbn13;
    string ratingAvg;
    string ratingCount;
    string title;
};
