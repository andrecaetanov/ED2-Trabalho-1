#include "sorting_service.h"
#include <chrono>
#include <time.h>
#include "selection_sort.h"
#include "quick_sort.h"
#include "dataset_helper.h"

#define NUMBER_ARRAYS 5
#define QUICK_SORT 1
#define SELECTION_SORT 2

using namespace std;

void SortingService::sort(vector<Book> *books, SortingStats *stats, int type)
{
    srand(time(NULL));

    int swaps = 0;
    int comparisons = 0;

    auto start = chrono::steady_clock::now();

    cout << endl;

    if (type == SELECTION_SORT)
    {
        cout << "Lista ordenada com SelectionSort:" << endl;
        SelectionSort::sort(books, &swaps, &comparisons);
        cout << endl;
    }
    else
    {
        cout << "Lista ordenada com QuickSort:" << endl;
        QuickSort<Book>::sort(books, 0, books->size() - 1, &swaps, &comparisons);
        cout << endl;
    }

    cout << endl;

    auto end = chrono::steady_clock::now();

    // Imprime os títulos dos livros ordenados
    for (int i = 0; i < books->size(); i++)
    {
        cout << i + 1 << ": " << books->at(i).title << endl;
    }

    cout << endl;

    chrono::duration<double> totalDuration = end - start;
    stats->durations.push_back(totalDuration.count());
    cout << "Tempo de duracao de execucao: " << totalDuration.count() << "s" << endl;

    stats->swaps.push_back(swaps);
    cout << "Numero de copias de registro: " << swaps << endl;

    stats->comparisons.push_back(comparisons);
    cout << "Numero de comparacoes: " << comparisons << endl;

    cout << endl;
}

void SortingService::execute()
{
    // Le o arquivo de entrada e guarda os valores de N em um array
    fstream inFile;
    ofstream outFile;
    int arraySize;
    cout << "Abrindo arquivo entrada" << endl;

    inFile.open("entrada.txt");
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

    // Cria objetos para armazenar estatísticas de desempenho dos algoritmos de ordenação
    SortingStats *quickSortStats = new SortingStats();
    SortingStats *selectionSortStats = new SortingStats();

    cout << "comeca criacao de vectors" << endl;

    // Execução
    for (int i = 0; i < arraySize; i++)
    {
        for (int j = 0; j < NUMBER_ARRAYS; j++)
        {
            // Le o dataset e guarda N elementos em uma lista
            int n = nArray[i];
            vector<Book> books;
            cout << "comeca ler dataset" << endl;
            DatasetHelper::readDatasetVector(&books, n);

            // Copia vetor inicial para utilizar elementos em ambas as ordenações
            vector<Book> *booksCopy = new vector<Book>;
            for (int i = 0; i < books.size(); i++)
            {
                booksCopy->push_back(books.at(i));
            }

            // Executa ordenações
            sort(&books, quickSortStats, QUICK_SORT);
            sort(booksCopy, selectionSortStats, SELECTION_SORT);
        }

        // Calcula as medias
        quickSortStats->calcAverages();
        selectionSortStats->calcAverages();

        // Limpa vetores com estatísticas de desempenho
        quickSortStats->clear();
        selectionSortStats->clear();
    }

    cout << endl;

    // Imprime no prompt e registra no arquivo de saida as estatisticas de desempenho
    outFile.open("saida.txt");

    cout << "Estatisticas gerais" << endl;
    cout << endl;
    outFile << "Estatisticas gerais" << endl;
    outFile << endl;

    for (int i = 0; i < arraySize; i++)
    {
        cout << "Quick Sort " << nArray[i] << " livros: " << endl;
        outFile << "Quick Sort " << nArray[i] << " livros: " << endl;
        quickSortStats->print(i, &outFile);

        cout << "Selection Sort " << nArray[i] << " livros: " << endl;
        outFile << "Selection Sort " << nArray[i] << " livros: " << endl;
        selectionSortStats->print(i, &outFile);
    }

    outFile.close();
}