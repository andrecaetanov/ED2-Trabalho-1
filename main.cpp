#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>

#include "quick_sort.h"
#include "selection_sort.h"

#define NUMBER_ARRAYS 1

using namespace std;

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

    //Comentei quicksort para testes
    // QuickSort::sort(books, 0, books->size() - 1);
    // cout << "Lista ordenada com QuickSort:" << endl;
    // for (int i = 0; i < books->size(); i++)
    // {
    //     cout << i + 1 << ": " << books->at(i).title << endl;
    // }
    // cout << endl;

    SelectionSort::sort(books);
    cout << "Lista ordenada com SelectionSort:" << endl;
    for (int i = 0; i < books->size(); i++)
    {
        cout << i + 1 << ": " << books->at(i).title << endl;
    }
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

    // Execução
    for (int n : nArray)
    {
        for (int i = 0; i < NUMBER_ARRAYS; i++)
        {
            // Le o dataset e guarda N elementos em uma lista
            vector<Book> books;
            readDataset(&dataset, &books, lenght, n);
        }
    }

    inFile.close();
    dataset.close();
    return 0;
}