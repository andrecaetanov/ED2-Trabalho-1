#include "dataset_helper.h"

using namespace std;

void DatasetHelper::readDatasetVector(vector<Book> *books, unsigned int listSize)
{
    // Abre o dataset e guarda o tamanho do arquivo em bytes
    cout << "Abrindo dataset" << endl;
    fstream dataset;
    openDataset(&dataset);

    dataset.seekg(0, dataset.end);
    unsigned long long int datasetLenght = dataset.tellg();
    dataset.seekg(0, dataset.beg);

    cout << "Gerando numero aleatorio para representar a posicao inicial de leitura do arquivo" << endl;
    // Gera um numero aleatorio que representa a posicao no arquivo e salta para a proxima linha
    int randomPos = rand() % (datasetLenght);
    dataset.seekg(randomPos);
    string unused;
    getline(dataset, unused);

    cout << "Lista desordenada:" << endl;
    for (int i = 0; i < listSize; i++)
    {
        Book book;

        // Le uma linha e separa os valores em atributos do livro
        string line;
        getline(dataset, line);

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

    dataset.seekg(0, dataset.beg);
    cout << endl;
    dataset.close();
}

void DatasetHelper::readAttribute(string *line, string *attribute, size_t *position)
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

void DatasetHelper::openDataset(fstream *dataset)
{
    dataset->open("dataset.csv");
    if (!dataset)
    {
        cout << "Nao foi possivel abrir o dataset." << endl;
        dataset->close();
        exit(0);
    }
}