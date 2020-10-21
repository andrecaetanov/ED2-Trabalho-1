#include <time.h>
#include "quick_sort.h"

void QuickSort::swap(Book *bookA, Book *bookB)
{
    Book temp = *bookA;
    *bookA = *bookB;
    *bookB = temp;
    //numSwaps++;
}

int QuickSort::partition(vector<Book> *books, int begin, int end)
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
            //numComparisons++;
            i++;
            swap(&books->at(i), &books->at(j));
        }
    }

    swap(&books->at(i + 1), &books->at(end));

    return i + 1;
}

void QuickSort::sort(vector<Book> *books, int begin, int end)
{
    if (begin < end)
    {
        int pi = partition(books, begin, end);
        sort(books, begin, pi - 1);
        sort(books, pi + 1, end);
    }
}

// int QuickSort::getNumComparisons()
// {
//     return numComparisons;
// }

// int QuickSort::getNumSwaps()
// {
//     return numSwaps;
// }