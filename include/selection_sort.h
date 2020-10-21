#include <vector>
#include "book.h"

class SelectionSort
{
private:
    static void swap(Book *a, Book *b);
    // static int numComparisons;
    // static int numSwaps;

public:
    SelectionSort();
    static void sort(vector<Book> *books);
    // int getNumComparisons();
    // int getNumSwaps();
};