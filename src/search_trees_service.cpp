#include "search_trees_service.h"
#include "red_black_tree.h"
#include <iostream>
using namespace std;

void TreeService::execute()
{
    RBTree *newTree = new RBTree();

    newTree->insert(15);

    newTree->insert(20);

    newTree->insert(30);

    newTree->print(newTree->getRoot());
    delete newTree;
}