#include <vector>
#include "book.h"
#include "sorting_stats.h"

class QuickSort
{
private:
    static void swap(Book *a, Book *b);
    static int partition(vector<Book> *books, int begin, int end, int *swaps, int *comparisons);

public:
    static void sort(vector<Book> *books, int begin, int end, int *swaps, int *comparisons);
};