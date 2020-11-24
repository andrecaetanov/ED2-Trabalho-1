#include <chrono>
#include <time.h>
#include "hash_service.h"
#include "hash.h"
#include "dataset_helper.h"
#include "book.h"
#include "quick_sort.h"

void HashService::execute(int hashSize, int numberBooks)
{
    srand(time(NULL));

    Hash<Book> *booksHash = new Hash<Book>();
    Hash<Author> *authorsHash = new Hash<Author>();
    vector<Author> authorsVector;

    booksHash->create(hashSize);
    authorsHash->create(hashSize);

    // Le os datasets de livros e autores e salva os N livros e seus autores em suas tabelas hash
    DatasetHelper::readDatasetHash(booksHash, authorsHash, &authorsVector, numberBooks);
    cout << endl;

    cout << "Hash de livros:" << endl;
    booksHash->read();
    cout << endl;

    cout << "Hash de autores:" << endl;
    authorsHash->read();
    cout << endl;

    sort(&authorsVector);

    booksHash->dispose();
    authorsHash->dispose();
}

void HashService::sort(vector<Author> *authorsVector)
{
    SortingStats *sortingStats = new SortingStats();
    int swaps = 0;
    int comparisons = 0;
    ofstream outFile;

    outFile.open("saida.txt");

    cout << "Vetor de autores desordenado:" << endl;
    cout << "id - nome - frequencia" << endl;
    for (Author author : *authorsVector)
    {
        cout << author.id << " - " << author.name << " - " << author.frequency << endl;
    }
    cout << endl;

    cout << "Ordenando autores por frequencia..." << endl;
    auto start = chrono::steady_clock::now();

    // Ordena os autores por frequencia em ordem decrescente
    QuickSort<Author>::sort(authorsVector, 0, authorsVector->size() - 1, &swaps, &comparisons);

    auto end = chrono::steady_clock::now();

    cout << endl;
    cout << "Vetor de autores ordenado:" << endl;
    outFile << "Vetor de autores ordenado:" << endl;

    cout << "id - nome - frequencia" << endl;
    outFile << "id - nome - frequencia" << endl;
    for (Author author : *authorsVector)
    {
        cout << author.id << " - " << author.name << " - " << author.frequency << endl;
        outFile << author.id << " - " << author.name << " - " << author.frequency << endl;
    }
    cout << endl;
    outFile << endl;

    cout << "Analise da ordenacao dos autores" << endl;
    outFile << "Analise da ordenacao dos autores" << endl;

    chrono::duration<double> totalDuration = end - start;
    sortingStats->durations.push_back(totalDuration.count());
    cout << "Tempo de duracao de execucao: " << totalDuration.count() << "s" << endl;
    outFile << "Tempo de duracao de execucao: " << totalDuration.count() << "s" << endl;

    sortingStats->swaps.push_back(swaps);
    cout << "Numero de copias de registro: " << swaps << endl;
    outFile << "Numero de copias de registro: " << swaps << endl;

    sortingStats->comparisons.push_back(comparisons);
    cout << "Numero de comparacoes: " << comparisons << endl;
    outFile << "Numero de comparacoes: " << comparisons << endl;

    outFile.close();
    delete sortingStats;
}