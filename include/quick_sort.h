#include <vector>
#include "sorting_stats.h"

template <typename T>
class QuickSort
{
private:
    static void swap(T *a, T *b);
    static int partition(vector<T> *entities, int begin, int end, int *swaps, int *comparisons);

public:
    static void sort(vector<T> *entities, int begin, int end, int *swaps, int *comparisons);
};