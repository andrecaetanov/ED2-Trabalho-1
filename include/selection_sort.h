#include <vector>
#include "book.h"

class SelectionSort
{
private:
    static void swap(Book *a, Book *b);

public:
    static void sort(vector<Book> *books, int *swaps, int *comparisons);
};