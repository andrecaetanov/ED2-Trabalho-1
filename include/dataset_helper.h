#include <iostream>
#include <fstream>
#include <vector>
#include "book.h"

class DatasetHelper
{
public:
    static void readDatasetVector(vector<Book> *books, unsigned int listSize);
    static void readDatasetHash();

private:
    static void readAttribute(string *line, string *attribute, size_t *position);
    static void openDataset(fstream *dataset);
};