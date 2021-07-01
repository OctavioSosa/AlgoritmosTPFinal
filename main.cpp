#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstdint>

#include "global.h"
#include "Router.h"
#include "Terminales.h"
#include "Cola.h"
#include "Algoritmos.h"
#include "Files.h"

using namespace std;

#define ARCHIVO_GRAFO       "../grafo1"
#define ARCHIVO_TERMINALES  "../Terminales1"

//Definicion de variables globales
int cantidadRouters;
int cantidadTerminales;
int idPagina_global= 0;

int main() {
    int cantidadAristas;

    //-----Obtengo toda la iformacion de los archivos: grafo, terminales, cantidadTerminales, cantidadRouter, cantidadAristas-----//

    //Obtemgo la cantidad de routers del archivo
    cantidadRouters = getNuberLines(ARCHIVO_GRAFO);

    //Obtengo la matriz que corresponde al grafo desde el archivo
    int grafo[cantidadRouters][cantidadRouters];
    getMatrizFromFile(ARCHIVO_GRAFO, &grafo[0][0], &cantidadAristas);

    //Obtengo la cantidad de terminales que hay
    cantidadTerminales = getNuberLines(ARCHIVO_TERMINALES);
    int terminalesEnlace[cantidadTerminales];
    getTerminalesFromFile( ARCHIVO_TERMINALES, &terminalesEnlace[0]);


    //-------Inicializo los Routers-------//
    int cantidadEnlaces = 0;
    int idTerminal = 0;
    Router routersArray[cantidadRouters];
    for (int i = 0; i < cantidadRouters; ++i) {
        //Obtengo el id de la terminal asociada al router, si es que tiene
        idTerminal = getIdTerminal( i, &terminalesEnlace[0]);

        //Obtengo la cantidad de enlaces asociados al router
        cantidadEnlaces = getCantidadDeEnlaces( i, &grafo[0][0]);

        //Obtengo el id de los routers con los cuales se enlaza
        int enlaces[cantidadEnlaces];
        getEnlaces(&enlaces[0], cantidadEnlaces,  i, &grafo[0][0]);

        //Obtengo el bandwidth de cadaenlace
        int bandWidth[cantidadEnlaces];
        getBandWidthEnlaces( &bandWidth[0], cantidadEnlaces, i, &grafo[0][0]);

        //Inicializo los routers
        routersArray[i].setAll( i, idTerminal, cantidadEnlaces, &enlaces[0], &bandWidth[0]);
    }



    return 0;
}
