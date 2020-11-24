#include <iostream>
#include <fstream>
#include <vector>
#include "book.h"
#include "hash.h"
#include "red_black_tree.h"

class DatasetHelper
{
public:
    static void readDatasetVector(vector<Book> *books, unsigned int size);
    static void readDatasetHash(Hash *hash, unsigned int size);
    static void readDatasetRBTree(RBTree *tree, unsigned int size);

private:
    static void openDataset(fstream *dataset);
    static void setRandomPosition(fstream *dataset);
    static unsigned long long int getDatasetLenght(fstream *dataset);
    static void readStringAttribute(string *line, string *attribute, size_t *position);
    static void readIntVectorAttribute(string *line, vector<int> *attribute, size_t *position);
    static void readIntAttribute(string *line, unsigned long long *attribute, size_t *position);
    static Book *readBooksDatasetLine(fstream *dataset);
};