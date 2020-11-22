#include "hash_service.h"
#include "hash.h"
#include "dataset_helper.h"

#define HASH_SIZE 100
#define NUMBER_BOOKS 100

void HashService::execute()
{
    Hash *hash = new Hash(HASH_SIZE);
    DatasetHelper::readDatasetHash(hash, NUMBER_BOOKS);
    hash->read();
}