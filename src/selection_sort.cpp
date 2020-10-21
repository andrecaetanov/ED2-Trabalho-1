#include "selection_sort.h"

// SelectionSort::SelectionSort()
// {
//     numComparisons = 0;
//     numSwaps = 0;
// }

void SelectionSort::swap(Book *bookA, Book *bookB)
{
    Book temp = *bookA;
    *bookA = *bookB;
    *bookB = temp;
    // numSwaps++;
}

void SelectionSort::sort(vector<Book> *books)
{
    int min;
    for (int i = 0; i < books->size(); i++)
    {
        min = i;
        for (int j = i + 1; j < books->size(); j++)
        {
            if (books->at(j).title < books->at(min).title)
            {
                // numComparisons++;
                min = j;
            }
        }
        if (books->at(i).title >= books->at(min).title)
        {
            // numComparisons++;
            swap(&books->at(i), &books->at(min));
        }
    }
}

// int SelectionSort::getNumComparisons()
// {
//     return numComparisons;
// }

// int SelectionSort::getNumSwaps()
// {
//     return numSwaps;
// }