#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
#include <chrono>
#include "sorting_service.h"

using namespace std;

void menu()
{
    int menuOption;
    cout << "Nesse trabalho, foram desenvolvidas analises de Algoritmos de Ordenacao, armazenamento de dados em tabelas Hash e busca em Estruturas Balanceadas." << endl;
    cout << endl;
    cout << "-> Digite 1 para realizar uma analise dos Algoritmos de Ordenacao Selection e Quick Sort." << endl;
    cout << "-> Digite 2 para realizar armazenamento de dados em tabelas Hash com tratamento de colisao." << endl;
    cout << "-> Digite 3 para realizar busca em Estruturas Balanceadas de Arvore Vermelho-Preta e Arvore B." << endl;
    cout << endl;
    cout << "Digite o valor da atividade que deseja realizar: " << endl;
    cin >> menuOption;

    switch (menuOption)
    {
    case 1:
        SortingService::execute();
        break;
    case 2:
        //hashTable();
        break;
    case 3:
        //trees();
        break;
    default:
        cout << "Valor invalido inserido." << endl;
        break;
    }
}

int main()
{
    menu();
    return 0;
}