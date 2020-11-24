#include "dataset_helper.h"
#include <chrono>
#include <sstream>

using namespace std;

void DatasetHelper::readDatasetVector(vector<Book> *books, unsigned int size)
{
    fstream dataset;

    openDataset(&dataset);
    setRandomPosition(&dataset);

    cout << "Lista desordenada:" << endl;
    for (int i = 0; i < size; i++)
    {
        Book *book = readBooksDatasetLine(&dataset);
        books->push_back(*book);
        cout << i + 1 << ": " << book->title << endl;
    }

    cout << endl;
    dataset.seekg(0, dataset.beg);
    dataset.close();
}

void DatasetHelper::readDatasetHash(Hash *hash, unsigned int size)
{
    fstream dataset;

    openDataset(&dataset);
    setRandomPosition(&dataset);

    for (int i = 0; i < size; i++)
    {
        Book *book = readBooksDatasetLine(&dataset);
        hash->insert(book);
    }

    dataset.seekg(0, dataset.beg);
    dataset.close();
}

//Lê dataset, insere elementos do dataset na arvore e preenche vetor de chaves para busca
void DatasetHelper::readDatasetRBTree(RBTree *tree, unsigned int size, vector<long long unsigned int> *keys, TreesStats *rbStats)
{
    fstream dataset;

    openDataset(&dataset);
    setRandomPosition(&dataset);

    cout << "Inserindo na arvore:" << endl;
    cout << endl;

    for (int i = 0; i < size; i++)
    {
        Book *book = readBooksDatasetLine(&dataset);
        tree->insert(book);
        keys->push_back(book->id);
    }

    cout << endl;
    dataset.seekg(0, dataset.beg);
    dataset.close();
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

void DatasetHelper::setRandomPosition(fstream *dataset)
{
    // Gera um numero aleatorio que representa a posicao no arquivo e salta para a proxima linha
    int datasetLenght = getDatasetLenght(dataset);
    int randomPos = rand() % (datasetLenght);
    dataset->seekg(randomPos);
    string unused;
    getline(*dataset, unused);
}

unsigned long long int DatasetHelper::getDatasetLenght(fstream *dataset)
{
    dataset->seekg(0, dataset->end);
    unsigned long long int datasetLenght = dataset->tellg();
    dataset->seekg(0, dataset->beg);
    return datasetLenght;
}

void DatasetHelper::readStringAttribute(string *line, string *attribute, size_t *position)
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

void DatasetHelper::readIntVectorAttribute(string *line, vector<int> *attribute, size_t *position)
{
    string attributeString;
    int number;
    string numberString;

    readStringAttribute(line, &attributeString, position);
    size_t attributeStringSize = attributeString.size();

    size_t firstDelimiter = line->find("[");
    size_t secondDelimiter = firstDelimiter + 1;

    if (firstDelimiter == 1)
    {
        while (secondDelimiter < attributeStringSize - 2)
        {
            secondDelimiter = line->find(", ", secondDelimiter + 1);

            if (secondDelimiter >= attributeStringSize - 2)
            {
                secondDelimiter = line->find("]", firstDelimiter + 1);
            }

            numberString = attributeString.substr(firstDelimiter, secondDelimiter - firstDelimiter - 1);
            istringstream(numberString) >> number;
            attribute->push_back(number);
            firstDelimiter = secondDelimiter + 1;
        }
    }
}

void DatasetHelper::readIntAttribute(string *line, unsigned long long int *attribute, size_t *position)
{
    string attributeString;
    readStringAttribute(line, &attributeString, position);
    istringstream(attributeString) >> *attribute;
}

Book *DatasetHelper::readBooksDatasetLine(fstream *dataset)
{
    Book *book = new Book();

    // Le uma linha e separa os valores em atributos do livro
    string line;
    getline(*dataset, line);

    size_t lastPosition = 0;
    readIntVectorAttribute(&line, &book->authors, &lastPosition);
    readStringAttribute(&line, &book->bestsellersRank, &lastPosition);
    readStringAttribute(&line, &book->categories, &lastPosition);
    readStringAttribute(&line, &book->edition, &lastPosition);
    readIntAttribute(&line, &book->id, &lastPosition);
    readStringAttribute(&line, &book->isbn10, &lastPosition);
    readStringAttribute(&line, &book->isbn13, &lastPosition);
    readStringAttribute(&line, &book->ratingAvg, &lastPosition);
    readStringAttribute(&line, &book->ratingCount, &lastPosition);
    readStringAttribute(&line, &book->title, &lastPosition);

    return book;
}