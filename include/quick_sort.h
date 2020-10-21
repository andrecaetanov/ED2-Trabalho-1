#include <vector>
#include "book.h"

class QuickSort
{
private:
    static void swap(Book *a, Book *b);
    static int partition(vector<Book> *books, int p, int q);
    //static int numComparisons;
    //static int numSwaps;

public:
    static void sort(vector<Book> *books, int p, int r);
    //int getNumComparisons();
    //int getNumSwaps();
};