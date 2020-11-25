#include "author.h"

Author::Author()
{
    this->frequency = 0;
}

int Author::getSortingParameter()
{
    return this->frequency * -1;
}