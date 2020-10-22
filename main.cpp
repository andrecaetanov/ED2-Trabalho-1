#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
#include <chrono>

#include "quick_sort.h"
#include "selection_sort.h"

#define NUMBER_ARRAYS 1

using namespace std;

//TODO: Implementar contador de swaps e comparações
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
    cout << "Lista Desordenada" << endl;
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

        cout << i + 1 << ": " << book.title << endl;
        books->push_back(book);
    }
    cout << endl;
}

void executeSorting(vector<Book> *books, vector<double> *quickSortDurations, vector<double> *selectionSortDurations)
{
    //Copia vetor inicial para utilizar elementos no SelectionSort
    vector<Book> *booksCopy = new vector<Book>;
    for (int i = 0; i < books->size(); i++)
    {
        booksCopy->push_back(books->at(i));
    }

    //QuickSort
    auto start = chrono::steady_clock::now();
    QuickSort::sort(books, 0, books->size() - 1);
    cout << "Lista ordenada com QuickSort:" << endl;
    for (int i = 0; i < books->size(); i++)
    {
        cout << i + 1 << ": " << books->at(i).title << endl;
    }
    cout << endl;
    auto end = chrono::steady_clock::now();
    chrono::duration<double> totalDuration = end - start;
    quickSortDurations->push_back(totalDuration.count());
    cout << "Duracao QuickSort: " << totalDuration.count() << "s" << std::endl;
    cout << endl;

    //SelectionSort
    start = chrono::steady_clock::now();
    SelectionSort::sort(booksCopy);
    cout << "Lista ordenada com SelectionSort:" << endl;
    for (int i = 0; i < booksCopy->size(); i++)
    {
        cout << i + 1 << ": " << booksCopy->at(i).title << endl;
    }
    cout << endl;
    end = chrono::steady_clock::now();
    totalDuration = end - start;
    selectionSortDurations->push_back(totalDuration.count());
    cout << "Duracao SelectionSort: " << totalDuration.count() << "s" << std::endl;
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

    //cria listas de durações médias, comparações e trocas
    double quickSortDurationAverage[arraySize];
    double selectionSortDurationAverage[arraySize];
    int quickSortComparisonsAverage[arraySize];
    int selectionSortComparisonsAverage[arraySize];
    int quickSortSwapsAverage[arraySize];
    int selectionSortSwapsAverage[arraySize];

    // Execução
    for (int i = 0; i < arraySize; i++)
    {
        vector<double> quickSortDurations;
        vector<double> selectionSortDurations;

        for (int j = 0; j < NUMBER_ARRAYS; j++)
        {
            // Le o dataset e guarda N elementos em uma lista
            int n = nArray[i];
            vector<Book> books;
            readDataset(&dataset, &books, lenght, n);
            executeSorting(&books, &quickSortDurations, &selectionSortDurations);
        }

        //Calcula a media e insiro no vector
        double averageQuick = 0;
        double averageSelection = 0;
        for (int j = 0; j < NUMBER_ARRAYS; j++)
        {
            averageQuick += quickSortDurations.at(j);
            averageSelection += selectionSortDurations.at(j);
        }
        averageQuick = averageQuick / NUMBER_ARRAYS;
        averageSelection = averageSelection / NUMBER_ARRAYS;
        quickSortDurationAverage[i] = averageQuick;
        selectionSortDurationAverage[i] = averageSelection;
    }

    cout << endl;

    //imprime duracao media para cada tamanho de lista
    for (int i = 0; i < arraySize; i++)
    {
        cout << "Quick Sort " << nArray[i] << " livros: " << quickSortDurationAverage.at(i) << "s " << endl;
        cout << "Selection Sort " << nArray[i] << " livros: " << selectionSortDurationAverage.at(i) << "s " << endl;
    }

    inFile.close();
    dataset.close();
    return 0;
}