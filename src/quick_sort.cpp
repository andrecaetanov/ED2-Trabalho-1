#include <time.h>
#include "quick_sort.h"
#include "book.h"
#include "author.h"

template <typename T>
void QuickSort<T>::swap(T *entityA, T *entityB)
{
    T temp = *entityA;
    *entityA = *entityB;
    *entityB = temp;
}

template <typename T>
int QuickSort<T>::partition(vector<T> *entities, int begin, int end, int *swaps, int *comparisons)
{
    srand(time(NULL));
    int random = begin + rand() % (end - begin);
    swap(&entities->at(random), &entities->at(end));

    T pivot = entities->at(end);
    int i = begin - 1;

    for (int j = begin; j <= end - 1; j++)
    {
        if (entities->at(j).getSortingParameter() < pivot.getSortingParameter())
        {
            i++;
            swap(&entities->at(i), &entities->at(j));
            *swaps = *swaps + 1;
            *comparisons = *comparisons + 1;
        }
    }

    swap(&entities->at(i + 1), &entities->at(end));
    *swaps = *swaps + 1;

    return i + 1;
}

template <typename T>
void QuickSort<T>::sort(vector<T> *entities, int begin, int end, int *swaps, int *comparisons)
{
    if (begin < end)
    {
        int pi = partition(entities, begin, end, swaps, comparisons);
        sort(entities, begin, pi - 1, swaps, comparisons);
        sort(entities, pi + 1, end, swaps, comparisons);
    }
}

template class QuickSort<Book>;
template class QuickSort<Author>;