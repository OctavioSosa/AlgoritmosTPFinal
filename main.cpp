#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cstdint>

#include "global.h"
#include "Router.h"
#include "Terminales.h"
#include "Cola.h"

using namespace std;

//Definicion de variables globales
int cantidadRouters;
int cantidadTerminales;
int idPagina_global= 0;

int main() {
    /* ------Como leer un archivo------
    ifstream file;
    file.open("../archivo.txt", ios::in);
    file>>buffer;
    variable = buffer;
     */
    //Cuando leo el archivo selecciono la cantidad de Routers
    cantidadRouters = 5;
  //  Router r1 = Router(0,1,0);
   // Terminal t1 = Terminal(0, 0);

    return 0;
}
