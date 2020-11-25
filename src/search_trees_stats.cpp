#include "search_trees_stats.h"
#include <iostream>

TreesStats::TreesStats()
{
}

void TreesStats::clear()
{
    insertionDurations.clear();
    searchDurations.clear();
    insertionComparisons.clear();
    searchComparisons.clear();
    dataMovement.clear();
}

void TreesStats::calcAverages()
{
    double insertionDurationsAverage = 0;
    double searchDurationsAverage = 0;
    double dataMovementAverage = 0;
    double insertionComparisonsAverage = 0;
    double searchComparisonsAverage = 0;

    for (int i = 0; i < insertionDurations.size(); i++)
    {
        insertionDurationsAverage += insertionDurations.at(i);
        searchDurationsAverage += searchDurations.at(i);
        dataMovementAverage += dataMovement.at(i);
        insertionComparisonsAverage += insertionComparisons.at(i);
        searchComparisonsAverage += searchComparisons.at(i);
    }

    insertionDurationsAverage = insertionDurationsAverage / insertionDurations.size();
    dataMovementAverage = dataMovementAverage / insertionDurations.size();
    insertionComparisonsAverage = insertionComparisonsAverage / insertionDurations.size();
    searchDurationsAverage = searchDurationsAverage / searchDurations.size();
    searchComparisonsAverage = searchComparisonsAverage / searchDurations.size();

    insertionDurationsAverages.push_back(insertionDurationsAverage);
    dataMovementAverages.push_back(dataMovementAverage);
    insertionComparisonsAverages.push_back(insertionComparisonsAverage);
    searchDurationsAverages.push_back(searchDurationsAverage);
    searchComparisonsAverages.push_back(searchComparisonsAverage);
}

void TreesStats::printInsertionStats(int index, ofstream *outFile)
{
    cout << "Tempo Medio de duracao de execucao da Insercao: " << insertionDurationsAverages.at(index) << "s " << endl;
    cout << "Numero Medio de movimentacoes de dados da Insercao: " << dataMovementAverages.at(index) << endl;
    cout << "Numero Medio de comparacoes da Insercao: " << insertionComparisonsAverages.at(index) << endl;

    *outFile << "Tempo Medio de duracao de execucao da Insercao: " << insertionDurationsAverages.at(index) << "s " << endl;
    *outFile << "Numero Medio de movimentacoes de dados da Insercao: " << dataMovementAverages.at(index) << endl;
    *outFile << "Numero Medio de comparacoes da insInsercaoercao: " << insertionComparisonsAverages.at(index) << endl;
    *outFile << endl;
}

void TreesStats::printSearchStats(int index, ofstream *outFile)
{
    cout << "Tempo Medio de duracao de execucao da Busca: " << searchDurationsAverages.at(index) << "s " << endl;
    cout << "Numero Medio de comparacoes da Busca: " << searchComparisonsAverages.at(index) << endl;
    cout << endl;

    *outFile << "Tempo Medio de duracao de execucao da Busca: " << searchDurationsAverages.at(index) << "s " << endl;
    *outFile << "Numero Medio de comparacoes da Busca: " << searchComparisonsAverages.at(index) << endl;
    *outFile << endl;
}