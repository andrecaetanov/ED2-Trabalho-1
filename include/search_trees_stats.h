#include <fstream>
#include <vector>
#pragma once

using namespace std;

class TreesStats
{
public:
    TreesStats();
    vector<double> durations;
    vector<int> comparisons;
    vector<int> swaps;
    vector<double> durationsAverages;
    vector<int> comparisonsAverages;
    vector<int> swapsAverages;
    void clear();
    void calcAverages();
    void print(int index, ofstream *outFile);
};