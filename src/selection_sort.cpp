#include "selection_sort.h"

void SelectionSort::swap(Book *bookA, Book *bookB)
{
    Book temp = *bookA;
    *bookA = *bookB;
    *bookB = temp;
}

void SelectionSort::sort(vector<Book> *books, int *swaps, int *comparisons)
{
    int min;
    for (int i = 0; i < books->size(); i++)
    {
        min = i;
        for (int j = i + 1; j < books->size(); j++)
        {
            if (books->at(j).title < books->at(min).title)
            {
                comparisons++;
                min = j;
            }
        }
        if (books->at(i).title >= books->at(min).title)
        {
            comparisons++;
            swap(&books->at(i), &books->at(min));
            swaps++;
        }
    }
}
