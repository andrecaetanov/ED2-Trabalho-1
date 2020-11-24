#include "search_trees_stats.h"
#include <iostream>

TreesStats::TreesStats()
{
}

void TreesStats::clear()
{
    durations.clear();
    comparisons.clear();
    swaps.clear();
}

void TreesStats::calcAverages()
{
    double durationsAverage = 0;
    double swapsAverage = 0;
    double comparisonsAverage = 0;

    for (int i = 0; i < durations.size(); i++)
    {
        durationsAverage += durations.at(i);
        swapsAverage += swaps.at(i);
        comparisonsAverage += comparisons.at(i);
    }

    durationsAverage = durationsAverage / durations.size();
    swapsAverage = swapsAverage / durations.size();
    comparisonsAverage = comparisonsAverage / durations.size();

    durationsAverages.push_back(durationsAverage);
    swapsAverages.push_back(swapsAverage);
    comparisonsAverages.push_back(comparisonsAverage);
}

void TreesStats::print(int index, ofstream *outFile)
{
    cout << "Tempo medio de duracao de execucao: " << durationsAverages.at(index) << "s " << endl;
    cout << "Numero medio de copias de registro: " << swapsAverages.at(index) << endl;
    cout << "Numero medio de comparacoes: " << comparisonsAverages.at(index) << endl;
    cout << endl;

    *outFile << "Tempo medio de duracao de execucao: " << durationsAverages.at(index) << "s " << endl;
    *outFile << "Numero medio de copias de registro: " << swapsAverages.at(index) << endl;
    *outFile << "Numero medio de comparacoes: " << comparisonsAverages.at(index) << endl;
    *outFile << endl;
}