#include <iostream>
#include <fstream>
#include <vector>
#include "book.h"
#include "hash.h"
#include "red_black_tree.h"
#include "search_trees_stats.h"
#include "author.h"

class DatasetHelper
{
public:
    static void readDatasetVector(vector<Book> *books, unsigned int size);
    static void readDatasetHash(Hash<Book> *booksHash, Hash<Author> *authorsHash, vector<Author> *authorsVector, unsigned int size);
    static void readDatasetRBTree(RBTree *tree, unsigned int size, vector<long long unsigned int> *keys, TreesStats *rbStats);

private:
    static void openDataset(fstream *dataset, string fileName);
    static void setRandomPosition(fstream *dataset);
    static unsigned long long int getDatasetLenght(fstream *dataset);
    static void readStringAttribute(string *line, string *attribute, size_t *position);
    static void readIntVectorAttribute(string *line, vector<int> *attribute, size_t *position);
    static void readIntAttribute(string *line, unsigned long long *attribute, size_t *position);
    static Book *readBooksDatasetLine(fstream *dataset);
};