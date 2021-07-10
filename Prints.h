//
// Created by octa on 9/7/21.
//

#ifndef ALGORITMOSTPFINAL_PRINTS_H
#define ALGORITMOSTPFINAL_PRINTS_H

#include <fstream>
#include "global.h"
#include "Router.h"

using namespace std;

void printMatrizNxN(string title, int * matrix, int n);
void printArray(string title, int * array, int sizeArray);
void printVar(string titleVar, int valueVar);
void printSeparador();
void printPagina(pag * Pagina);
void printColas(Router * arrayRou, int idRouter);
void printColasRouters(Router * arrayRou, int sizeArray);


#endif //ALGORITMOSTPFINAL_PRINTS_H
