#include "search_trees_service.h"
#include "search_trees_stats.h"
#include "red_black_tree.h"
#include "dataset_helper.h"
#include <iostream>

using namespace std;

#define NUMBER_OF_TREES 5

void TreeService::execute()
{
    //Leitura do arquivo de entrada
    fstream inFile;
    int arraySize;

    cout << "Abrindo arquivo de entrada:" << endl;

    inFile.open("entradaTree.txt");
    if (!inFile)
    {
        cout << "Nao foi possivel abrir o arquivo de entrada." << endl;
        inFile.close();
        exit(0);
    }

    inFile >> arraySize;
    int nArray[arraySize] = {0};
    for (int i = 0; i < arraySize; i++)
    {
        inFile >> nArray[i];
    }

    inFile.close();

    TreesStats *rbStats = new TreesStats();

    for (int i = 0; i < arraySize; i++)
    {
        for (int j = 0; j < NUMBER_OF_TREES; j++)
        {
            cout << "----------- Arvore Vermelha-Preta - " << nArray[i] << " -----------" << endl;
            cout << endl;
            RBTree *tree = new RBTree();
            DatasetHelper::readDatasetRBTree(tree, nArray[i]);
            cout << endl;
        }
    }

    //------------------Código de teste na classe Books----------------------//
    // RBTree *tree = new RBTree();
    // DatasetHelper::readDatasetRBTree(tree, 7);
    // tree->print();

    //------------------Código do Trabalho----------------------//
    // for (int i = 0; i < arraySize; i++)
    // {
    //     for (int j = 0; j < NUMBER_OF_TREES; j++)
    //     {
    //         RBTree *tree = new RBTree();
    //         DatasetHelper::readDatasetRBTree(tree, nArray[i]);
    //     }
    // }
}