#include <iostream>
#include <fstream>
#include <vector>
#include "sorting_stats.h"
#include "book.h"

class SortingService
{
public:
    static void execute();

private:
    static void sort(vector<Book> *books, SortingStats *stats, int type);
};
