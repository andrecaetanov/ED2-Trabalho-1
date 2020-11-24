#include "search_trees_service.h"
#include "red_black_tree.h"
#include <iostream>
using namespace std;

void TreeService::execute()
{
    RBTree *newTree = new RBTree();

    newTree->insert(15);
    newTree->insert(20);
    newTree->insert(10);
    newTree->insert(40);
    newTree->insert(30);
    newTree->insert(12);
    newTree->insert(5);

    newTree->print();

    newTree->search(10);
    newTree->search(3);
    newTree->search(12);

    delete newTree;
}