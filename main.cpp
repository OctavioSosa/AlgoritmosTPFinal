#include <stdio.h>
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
#include "Prints.h"

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


    ///---Imprimo---
    cout<<"Informacion inicial sobre el sistema:"<<endl;
    printVar("Cantidad de Routers", cantidadRouters);
    printVar("Cantidad de Aristas", cantidadAristas);
    printVar("Cantidad de Terminales", cantidadTerminales);
    cout<<endl;
    printArray("Routers que tienen terminales", &terminalesEnlace[0], cantidadTerminales);
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
    /*///---Imprimo---
    cout<<"Paginas Creadas Forzadamente: "<<endl;
    cout<<"IP Origen \t\t Pagina \t IP Destino"<<endl;
    for (int i = 0; i < cantidadTerminales ; ++i) {
        int idRouter = terminalesArray[i].getIdRouter();
        pag Pagina;
        terminalesArray[i].crearPagina( &Pagina);
        routersArray[idRouter].recibirPagina( Pagina);
        ///---Imprimo pagina---
        cout<<"   "<<idRouter<<"."<<i<<" -> ";
        printPagina(&Pagina);
    }*/ 


    //-------Ciclos-------//
    int contadorCiclos = 0;
    while (contadorCiclos < CANTIDAD_CICLOS)
    {
        ///---Imprimo ciclo---
        printSeparador();
        cout<<"Ciclo "<<contadorCiclos<<": "<<endl<<endl;

        //-------Ordenamiento de Colas-------
        for (int i = 0; i < cantidadRouters; ++i) {
            //Obtengo todos los caminos del router[i]
            int arrayCaminos[cantidadRouters];
            adminSist.getCaminosRouter( &arrayCaminos[0], i);
            //reordeno todos los paquetes de las colas
            routersArray[i].reordenarColas( &arrayCaminos[0]);
        }


        //-------Creacion de Paginas-------
        ///---Imprimo---
        cout<<"Paginas Creadas: "<<endl;
        cout<<"IP Origen \t\t Pagina \t IP Destino"<<endl;

        for (int i = 0; i < cantidadTerminales; ++i) {
            int random = rand() % 5;
            if (random == 3 ) {      //Aproximadamente en uno de cada 5 ciclos, crea una pagina, cada terminal.
                int idRouter = terminalesArray[i].getIdRouter();
                pag Pagina;
                //Crea y envía la página
                terminalesArray[i].crearPagina( &Pagina);       //La terminal i crea una pagina
                routersArray[idRouter].recibirPagina( Pagina);  //Esa pagina es enviada desde la terminal hacia el router asociado a la terminal. En el router se divide en paquetes

                ///---Imprimo pagina---
                cout<<"   "<<idRouter<<"."<<i<<" -> ";
                printPagina(&Pagina);
            }
        }


        ///---Imprimo Colas---
        cout<<endl;
        printColasRouters( &routersArray[0], cantidadRouters);



        //-------Armado y enviado de páginas recibidas-------
        ///---Imprimo texto de paginas---
        cout<<"Paginas que llegaron a su destino: "<<endl;
        for (int i = 0; i < cantidadRouters; ++i) {
            int terminalId = routersArray[i].getTerminalId();
            if(terminalId >= 0) {                            //Veo si el router tiene terminal asociada
                pag Pagina;
                int retorno;
                do {
                    retorno = routersArray[i].armarPaginasRecibidas(&Pagina);   //Obtengo una pagina si hay
                    if (retorno > 0) {
                        enviarPaginaATerminal(&Pagina, &terminalesArray[idTerminal]);        //La envio a la terminal
                        ///---Imprimo pagina recibida---
                        cout<<"Pagina recibida por la terminal "<<terminalId<<": ";
                        printPagina(&Pagina);
                    }
                } while (retorno > 0);   //Si retorno una pagina hay que llamarla de nuevo por si hay otra
            }
        }
        cout<<endl;


        //-------Envio de Paquetes-------
        //enviarPaquetes( &routersArray[0]);
        cout<<"Enviamos los paqutes. Las colas quedan: "<<endl;
        printColasRouters( &routersArray[0], cantidadRouters);


        //-------Recomputo de rutas------
        if (contadorCiclos%2 == 0){ //cada 2 ciclos
            adminSist.setMatrizPaquetesEnColas( &routersArray[0]);
            adminSist.setMatrizCostos();
            adminSist.setMatrizCaminos();

            ///---Imprimo matrices---
            cout<<"Recalculo las Rutas: "<<endl;
            adminSist.printMatrices();
        }


        contadorCiclos++;
    }


    return 0;
}




