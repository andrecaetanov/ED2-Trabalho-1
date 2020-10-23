#include <time.h>
#include "quick_sort.h"

void QuickSort::swap(Book *bookA, Book *bookB)
{
    Book temp = *bookA;
    *bookA = *bookB;
    *bookB = temp;
}

int QuickSort::partition(vector<Book> *books, int begin, int end, int *swaps, int *comparisons)
{
    srand(time(NULL));
    int random = begin + rand() % (end - begin);
    swap(&books->at(random), &books->at(end));

    Book pivot = books->at(end);
    int i = begin - 1;

    for (int j = begin; j <= end - 1; j++)
    {
        if (books->at(j).title < pivot.title)
        {
            i++;
            swap(&books->at(i), &books->at(j));
            swaps++;
            comparisons++;
        }
    }

    swap(&books->at(i + 1), &books->at(end));
    swaps++;

    return i + 1;
}

void QuickSort::sort(vector<Book> *books, int begin, int end, int *swaps, int *comparisons)
{
    if (begin < end)
    {
        int pi = partition(books, begin, end, swaps, comparisons);
        sort(books, begin, pi - 1, swaps, comparisons);
        sort(books, pi + 1, end, swaps, comparisons);
    }
}