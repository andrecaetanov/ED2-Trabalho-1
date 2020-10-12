#include <iostream>
#include <fstream>
#include <time.h>

#include "book.h"
#include "list.h"

using namespace std;

int main()
{
    // Le o arquivo de entrada e guarda os valores de N em um array
    int arraySize;
    fstream inFile;

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
    int lenght = dataset.tellg();
    dataset.seekg(0, dataset.beg);

    // Execute
    for (int n : nArray)
    {
        for (int i = 0; i < 5; i++)
        {
            // Gera um numero aleatorio que representa a posicao no arquivo e salta para a proxima linha
            srand(time(NULL));
            int randomChar = rand() % (lenght);
            dataset.seekg(randomChar);
            string unused;
            getline(dataset, unused);

            // Le o dataset e guarda N elementos em uma lista
            List<Book> *books = new List<Book>();

            for (int i = 0; i < n; i++)
            {
                Book *book = new Book();
                getline(dataset, book->authors, ',');
                getline(dataset, book->bestsellersRank, ',');
                getline(dataset, book->categories, ',');
                getline(dataset, book->edition, ',');
                getline(dataset, book->id, ',');
                getline(dataset, book->isbn10, ',');
                getline(dataset, book->isbn13, ',');
                getline(dataset, book->ratingAvg, ',');
                getline(dataset, book->ratingCount, ',');
                getline(dataset, book->title);
                cout << book->title << endl;
                books->insert(book);
            }

            dataset.seekg(0, dataset.beg);
        }
    }

    inFile.close();
    dataset.close();
    return 0;
}