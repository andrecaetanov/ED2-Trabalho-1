#include <iostream>
#include "sorting_service.h"
#include "hash_service.h"
#include "search_trees_service.h"

using namespace std;

#define SORT_NUMBER_ARRAYS 5
#define HASH_SIZE 1000
#define HASH_NUMBER_BOOKS 1000

void menu()
{
    int menuOption;
    cout << "Trabalho da disciplina Estrutura de Dados 2 - 2020.1" << endl;
    cout << "Desenvolvido por: Andre Caetano e Bernardo Cruz" << endl;
    cout << endl;

    cout << "Esse trabalho consiste de 3 partes distintas, escolha um delas para seguir:" << endl;
    cout << endl;
    cout << "-> Digite 1 para realizar uma analise dos algoritmos de ordenacao Selection e Quick Sort;" << endl;
    cout << "-> Digite 2 para realizar armazenamento e leitura de dados em tabelas Hash com tratamento de colisao;" << endl;
    cout << "-> Digite 3 para realizar busca em estruturas balanceadas de Arvore Vermelho-Preta e Arvore B." << endl;
    cout << endl;
    cout << "Digite o valor da atividade que deseja realizar: " << endl;
    cin >> menuOption;
    cout << endl;

    switch (menuOption)
    {
    case 1:
        SortingService::execute(SORT_NUMBER_ARRAYS);
        break;
    case 2:
        HashService::execute(HASH_SIZE, HASH_NUMBER_BOOKS);
        break;
    case 3:
        TreeService::execute();
        break;
    default:
        cout << "Valor inserido invalido." << endl;
        break;
    }
}

int main()
{
    menu();
    return 0;
}