//
// Created by octa on 30/6/21.
//

#ifndef ALGORITMOSTPFINAL_FILES_H
#define ALGORITMOSTPFINAL_FILES_H
#include <fstream>

using namespace std;


int getNuberLines(string nombreArchivo);
void getMatrizFromFile(string nombreArchivo, int * matriz, int * cantAristas);
void getTerminalesFromFile(string nombreArchivo, int * matriz);

#endif //ALGORITMOSTPFINAL_FILES_H
