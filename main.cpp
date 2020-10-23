#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
#include <chrono>

#include "quick_sort.h"
#include "selection_sort.h"
#include "sorting_stats.h"

#define NUMBER_ARRAYS 5
#define QUICK_SORT 1
#define SELECTION_SORT 2

using namespace std;

//TODO: Gerar arquivo de saída com estatísicas de cada lista e média da duração total para cada tamanho
//TODO: Escreve relatório

void readAttribute(string *line, string *attribute, size_t *position)
{
    size_t firstDelimiter = line->find("\"", *position);
    size_t secondDelimiter = line->find("\",", firstDelimiter);

    if (secondDelimiter == string::npos)
    {
        secondDelimiter = line->find("\"", firstDelimiter + 1);
    }

    *attribute = line->substr(firstDelimiter + 1, secondDelimiter - firstDelimiter - 1);
    *position = secondDelimiter + 1;
}

void readDataset(fstream *dataset, vector<Book> *books, unsigned int datasetLenght, unsigned int listSize)
{
    //cout << "Lista Desordenada" << endl;
    for (int i = 0; i < listSize; i++)
    {
        Book book;

        // Gera um numero aleatorio que representa a posicao no arquivo e salta para a proxima linha
        int randomChar = rand() % (datasetLenght);
        dataset->seekg(randomChar);
        string unused;
        getline(*dataset, unused);

        // Le uma linha e separa os valores em atributos do livro
        string line;
        getline(*dataset, line);

        size_t lastPosition = 0;
        readAttribute(&line, &book.authors, &lastPosition);
        readAttribute(&line, &book.bestsellersRank, &lastPosition);
        readAttribute(&line, &book.categories, &lastPosition);
        readAttribute(&line, &book.edition, &lastPosition);
        readAttribute(&line, &book.id, &lastPosition);
        readAttribute(&line, &book.isbn10, &lastPosition);
        readAttribute(&line, &book.isbn13, &lastPosition);
        readAttribute(&line, &book.ratingAvg, &lastPosition);
        readAttribute(&line, &book.ratingCount, &lastPosition);
        readAttribute(&line, &book.title, &lastPosition);

        //cout << i + 1 << ": " << book.title << endl;
        books->push_back(book);
    }
    cout << endl;
}

void sort(vector<Book> *books, SortingStats *stats, int type)
{
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
        QuickSort::sort(books, 0, books->size() - 1, &swaps, &comparisons);
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
    cout << "Duracao: " << totalDuration.count() << "s" << endl;

    stats->swaps.push_back(swaps);
    cout << "Numero de copias de registro: " << swaps << endl;

    stats->comparisons.push_back(comparisons);
    cout << "Numero de comparacoes: " << comparisons << endl;

    cout << endl;
}

int main()
{
    srand(time(NULL));

    // Le o arquivo de entrada e guarda os valores de N em um array
    fstream inFile;
    int arraySize;

    inFile.open("entrada.txt");
    if (!inFile)
    {
        cout << "Nao foi possivel abrir o arquivo de entrada." << endl;
        return 0;
    }

    inFile >> arraySize;
    int nArray[arraySize] = {0};

    for (int i = 0; i < arraySize; i++)
    {
        inFile >> nArray[i];
    }

    // Abre o dataset e guarda o tamanho do arquivo em bytes
    fstream dataset;

    dataset.open("dataset.csv");
    if (!dataset)
    {
        cout << "Nao foi possivel abrir o dataset." << endl;
        return 0;
    }

    dataset.seekg(0, dataset.end);
    unsigned int lenght = dataset.tellg();
    dataset.seekg(0, dataset.beg);

    // Cria objetos para armazenar estatísticas de desempenho dos algoritmos de ordenação
    SortingStats *quickSortStats = new SortingStats();
    SortingStats *selectionSortStats = new SortingStats();

    // Execução
    for (int i = 0; i < arraySize; i++)
    {
        for (int j = 0; j < NUMBER_ARRAYS; j++)
        {
            // Le o dataset e guarda N elementos em uma lista
            int n = nArray[i];
            vector<Book> books;
            readDataset(&dataset, &books, lenght, n);

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

    // Imprime as estatisticas de desempenho
    for (int i = 0; i < arraySize; i++)
    {
        cout << "Quick Sort " << nArray[i] << " livros: " << endl;
        quickSortStats->print(i);

        cout << endl;

        cout << "Selection Sort " << nArray[i] << " livros: " << endl;
        selectionSortStats->print(i);
    }

    inFile.close();
    dataset.close();
    return 0;
}