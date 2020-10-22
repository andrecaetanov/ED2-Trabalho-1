#include "selection_sort.h"

void SelectionSort::swap(Book *bookA, Book *bookB)
{
    Book temp = *bookA;
    *bookA = *bookB;
    *bookB = temp;
}

void SelectionSort::sort(vector<Book> *books)
{
    int min;
    int numComparisons = 0;
    int numSwaps = 0;
    for (int i = 0; i < books->size(); i++)
    {
        min = i;
        for (int j = i + 1; j < books->size(); j++)
        {
            if (books->at(j).title < books->at(min).title)
            {
                numComparisons++;
                min = j;
            }
        }
        if (books->at(i).title >= books->at(min).title)
        {
            numComparisons++;
            swap(&books->at(i), &books->at(min));
            numSwaps++;
        }
    }
    //cout << "Total de comparacoes: " << numComparisons << endl;
    //cout << "Total de trocas: " << numSwaps << endl;
}
