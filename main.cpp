#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstdint>
#include<bits/stdc++.h>

#include "global.h"
#include "Router.h"
#include "Terminales.h"
#include "Cola.h"
#include "Algoritmos.h"
#include "Files.h"
#include "Admin.h"

using namespace std;

#define ARCHIVO_GRAFO       "../grafo1"
#define ARCHIVO_TERMINALES  "../Terminales1"
#define CANTIDAD_CICLOS     10

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
    //Creo las terminales
    Terminal terminalesArray[cantidadTerminales];



    //-----Creo el Administrador del Sistema-----//

    //Con el constructor se inicilizan las matrices: matrizCaminos, matrizCostos, matrizPaquetesEnColas
    //Incluso se calcula dijkstra pero con todas las colas vacias
    Admin adminSist( &grafo[0][0], cantidadRouters);

    adminSist.printMatrices();



    //-------Inicializo los Routers y las Terminales-------//
    int cantidadEnlaces = 0;
    int idTerminal = 0;
    int indice = 0;
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

        //Inicializo las Terminales
        if (idTerminal != -1){  //Si el router tiene asociada una terminal, la crea
            terminalesArray[indice].setAll( idTerminal, i, &terminalesEnlace[0]);
            indice++;
        }
    }

    //-------Creo una pagina en cada terminal para arrancar-------
    /*for (int i = 0; i < cantidadTerminales ; ++i) {
        int idRouter = terminalesArray[i].getIdRouter();
        pag Pagina;
        terminalesArray[i].crearPagina( &Pagina);
        routersArray[idRouter].recibirPagina( Pagina);
    }*/


    //-------Ciclos-------//
    int contadorCiclos = 0;
    while (contadorCiclos < CANTIDAD_CICLOS)
    {
        //-------Creacion de Paginas-------
        for (int i = 0; i < cantidadTerminales; ++i) {
            int random = rand() % 5;
            if (random == 4 ) {      //Aproximadamente en uno de cada 5 ciclos, crea una pagina, cada terminal.
                int idRouter = terminalesArray[i].getIdRouter();
                pag Pagina;
                terminalesArray[i].crearPagina( &Pagina);
                routersArray[idRouter].recibirPagina( Pagina);
            }
        }


        //-------Ordenamiento de Colas-------
        for (int i = 0; i < cantidadRouters; ++i) {
            //Obtengo todos los caminos del router[i]
            int arrayCaminos[cantidadRouters];
            adminSist.getCaminosRouter( &arrayCaminos[0], i);
            //reordeno todos los paquetes de las colas
            routersArray[i].reordenarColas( &arrayCaminos[0]);
        }


        //-------Armado y enviado de páginas recibidas-------
        for (int i = 0; i < cantidadRouters; ++i) {
            int terminalId = routersArray[i].getTerminalId();
            if(terminalId >= 0) {                            //Veo si el router tiene terminal asociada
                pag Pagina;
                int retorno;
                do {
                    retorno = routersArray[i].armarPaginasRecibidas(&Pagina);   //Obtengo una pagina si hay
                    enviarPaginaATerminal( &Pagina, &terminalesArray[idTerminal]);        //La envio a la terminal
                } while (retorno > 0);   //Si retorno una pagina hay que llamarla de nuevo por si hay otra
            }
        }


        //-------Envio de Paquetes-------
        enviarPaquetes( &routersArray[0]);


        //-------Recomputo de rutas------
        if (contadorCiclos%2 == 0){ //cada 2 ciclos
            adminSist.setMatrizPaquetesEnColas( &routersArray[0]);
            adminSist.setMatrizCostos();
            adminSist.setMatrizCaminos();
        }


        contadorCiclos++;
    }


    return 0;
}
