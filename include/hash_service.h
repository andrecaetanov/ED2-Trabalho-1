#include <vector>
#include "author.h"

class HashService
{
private:
    static void sort(vector<Author> *authorsVector);

public:
    static void execute(int hashSize, int numberBooks);
};