#include <fstream>
#include <vector>
#pragma once

using namespace std;

class TreesStats
{
public:
    TreesStats();
    vector<double> insertionDurations;
    vector<double> searchDurations;
    vector<int> insertionComparisons;
    vector<int> searchComparisons;
    vector<int> dataMovement;
    vector<double> insertionDurationsAverages;
    vector<int> insertionComparisonsAverages;
    vector<double> searchDurationsAverages;
    vector<int> searchComparisonsAverages;
    vector<int> dataMovementAverages;
    void clear();
    void calcAverages();
    void print(int index, ofstream *outFile);
};