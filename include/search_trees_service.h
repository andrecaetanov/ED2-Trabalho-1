#include <fstream>
#include "red_black_tree.h"
#include <vector>
#include "search_trees_stats.h"

class TreeService
{
public:
    static void execute();
    static void searchInsertedKeys(RBTree *tree, vector<long long unsigned int> *keys, TreesStats *rbStats);
};