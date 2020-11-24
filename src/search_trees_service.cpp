#include "search_trees_service.h"
#include "dataset_helper.h"
#include <chrono>
#include <iostream>

using namespace std;

#define NUMBER_OF_TREES 5

void TreeService::searchInsertedKeys(RBTree *tree, vector<long long unsigned int> *keys, TreesStats *rbStats)
{
    int comparisons = 0;
    auto start = chrono::steady_clock::now();
    for (int i = 0; i < keys->size(); i++)
    {
        tree->search(keys->at(i), &comparisons);
    }
    auto end = chrono::steady_clock::now();
    chrono::duration<double> totalDuration = end - start;

    rbStats->searchDurations.push_back(totalDuration.count());
    cout << "Tempo de duracao de execucao da busca: " << totalDuration.count() << "s" << endl;

    rbStats->searchComparisons.push_back(comparisons);
    cout << "Numero de comparacoes: " << comparisons << endl;
}

void TreeService::execute()
{
    //Leitura do arquivo de entrada
    fstream inFile;
    ofstream outFile;
    int arraySize;

    cout << "Abrindo arquivo de entrada:" << endl;

    inFile.open("entradaTree.txt");
    if (!inFile)
    {
        cout << "Nao foi possivel abrir o arquivo de entrada." << endl;
        inFile.close();
        exit(0);
    }
    // monta o vetor do tamanho das árvores
    inFile >> arraySize;
    int nArray[arraySize] = {0};
    for (int i = 0; i < arraySize; i++)
    {
        inFile >> nArray[i];
    }

    inFile.close();

    //instacia o objeto de estatísticas
    TreesStats *rbStats = new TreesStats();

    //realizo a inserção e busca do trabalho
    for (int i = 0; i < arraySize; i++)
    {
        for (int j = 0; j < NUMBER_OF_TREES; j++)
        {
            cout << "----------- Arvore Vermelha-Preta - " << nArray[i] << " -----------" << endl;
            cout << endl;

            //cria nova árvore, lê valores, insere na árvore e cria vetor de chaves inseridas para busca
            RBTree *tree = new RBTree();
            vector<long long unsigned int> *keys = new vector<long long unsigned int>;
            DatasetHelper::readDatasetRBTree(tree, nArray[i], keys, rbStats);
            cout << endl;

            //procura pelas chaves inseridas a partir do vetor criado anteriormente
            searchInsertedKeys(tree, keys, rbStats);
            cout << endl;
        }
        rbStats->calcAverages();
        rbStats->clear();
    }

    cout << endl;

    //garantir que ta funcionando os stats
    //fazer o output file
    // Imprime no prompt e registra no arquivo de saida as estatisticas de desempenho
    outFile.open("saidaTree.txt");

    cout << "Estatisticas gerais" << endl;
    cout << endl;
    outFile << "Estatisticas gerais" << endl;
    outFile << endl;

    for (int i = 0; i < arraySize; i++)
    {
        cout << "Arvore Vermelha-Preta - " << nArray[i] << " chaves: " << endl;
        outFile << "QArvore Vermelha-Preta - " << nArray[i] << " chaves: " << endl;
        rbStats->print(i, &outFile);
    }
}