#include "book.h"

Book::Book()
{
    this->frequency = 0;
}

string Book::getSortingParameter()
{
    return this->title;
}