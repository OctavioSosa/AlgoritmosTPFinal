//
// Created by octa on 1/7/21.
//

#include "Admin.h"
#include "Algoritmos.h"
#include "Terminales.h"
#include "Router.h"
#include "Prints.h"
#include<bits/stdc++.h>


Admin::Admin(int * _grafo, int _cantidadRouters)
{
    cantRouters = _cantidadRouters; //Cantidad de routers
    grafo = _grafo;                 //Puntero a la matriz grafo


    //Creo e inicializo la matriz Paquetes en Cola
    /* Esta matriz tiene la cantidad de paquetes que hay en cada cola. Igualmente en la cola propia.
     * Pero donde no hay enlaces y no hay colas, su valor es infinito*/
    //int matrPaqEnCol[cantRouters][cantRouters] = {0};
    matrizPaquetesEnColas = (int*) calloc(cantRouters*cantRouters, sizeof(int));//Se iniciliza en cero porque todas las colas empiezan sin paquetes
    //Inicializo los valores que son infinitor
    for (int i = 0; i < cantRouters; ++i) {
        for (int j = 0; j < cantRouters; ++j) {
            if(grafo[i*cantRouters + j] == INT_MAX){
                matrizPaquetesEnColas[i*cantRouters + j] = INT_MAX;
            }
        }
    }


    //Creo e inicializo la matriz costos
    //int matrCostos[cantRouters][cantRouters];
    matrizCostos = (int*) malloc(cantRouters*cantRouters * sizeof(int));
    setMatrizCostos();

    //Creo e inicializo la matriz caminos
    //int matrCaminos[cantRouters][cantRouters];
    matrizCaminos = (int*) malloc(cantRouters*cantRouters * sizeof(int));
    setMatrizCaminos();

}

Admin::~Admin()
{
    free(matrizPaquetesEnColas);
    free(matrizCostos);
    free(matrizCaminos);
}

void Admin::setMatrizPaquetesEnColas( Router * arrayRouters)
{
    int cantiColas;
    int k;
    for(int i = 0; i < cantRouters;i++){
        cantiColas = arrayRouters[i].getCantidadEnlaces() + 1;

        //Obtengo la matriz de enlaces
        int enlaces[cantiColas-1];
        getEnlaces(&enlaces[0], cantiColas-1,  i, grafo);

        //Coloco la cantidad de paquetes en los lugares correspondientes
        for (int j = 0; j < cantiColas-1; ++j) {
            k = enlaces[j];                                                             //guardo el router asignado a la cola j
            matrizPaquetesEnColas[i*cantRouters + k] = arrayRouters[i].getSizeCola(j);  //Asigno la cantidad de paquetes a la matriz paqutes en cola
        }

        //Paquetes que tengo en la cola propia
        matrizPaquetesEnColas[i*cantRouters + i] = arrayRouters[i].getSizeCola(cantiColas);  //Asigno la cantidad de paquetes que tengo en la cola propia

    }
}

void Admin::setMatrizCaminos()
{
    for (int i = 0; i < cantRouters; ++i) {
        dijkstra(&matrizCaminos[i*cantRouters + 0], cantRouters, i, cantRouters, matrizCostos);   //Cada fila de la matriz representa a un router
    }
}


/* \brief Devuelve el router al cual hay que enviarle los paquetes para llegar desde el
 *        router idRouter, hasta el router idRouDestino, por el camino mas corto*/
int Admin::getCaminoRouterADestino(int idRouter, int idRouDestino)
{
    return matrizCaminos[idRouter*cantRouters + idRouDestino];
}

/* \brief Devuelve un array con todos los router a los que hay que enviarles un paquete
 *        para llegar al router destino por el camino mas corto desde el router idRouter.
 *        Devuelve un array con todos los routers siguientes para cada router destino*/
void Admin::getCaminosRouter(int * arrayCam, int idRouter)
{
    for (int i = 0; i < cantRouters; ++i) {
        arrayCam[i] = matrizCaminos[idRouter*cantRouters + i];
    }
}


/* \brief       Esta funcion genera el calculo de los costos de cada enlace, que luego
 *              se necesitará para calcular dijkstra.
*/
void Admin::setMatrizCostos()
{
    for (int i = 0; i < cantRouters; ++i) {
        for (int j = 0; j < cantRouters; ++j) {
            if (grafo[i*cantRouters + j] != 0 && grafo[i*cantRouters + j] != INT_MAX ) {   //Para no hacer la division por cero
                /*Para calcular los costos hago: (matrizPaquetesEnColas[i][j]/grafo[i][j])+1
                 *Los costos son: Cantidad de ciclos que tardaría un paquete nuevo en enviarse por un cierto enlace*/
                matrizCostos[i*cantRouters + j] = (matrizPaquetesEnColas[i*cantRouters + j] / grafo[i*cantRouters + j]) + 1;
            } else {
                if (grafo[i*cantRouters + j] == 0) {
                    matrizCostos[i * cantRouters + j] = 0;//Estos son los valores i=j correspondientes a la cola propia
                    //Si estan en su propia cola tienen costo cero para enviarse
                } else if(grafo[i*cantRouters + j] == INT_MAX){
                    matrizCostos[i * cantRouters + j] = INT_MAX;//Si no hay enlace el costo es infinito
                }

            }
        }
    }
}


void Admin::printMatrices(){
    /*printMatrizNxN("Grafo", grafo, cantRouters);
    printMatrizNxN("Matriz Caminos", matrizCaminos, cantRouters);
    printMatrizNxN("Matriz Costos", matrizCostos, cantRouters);
    printMatrizNxN("Matriz Paquetes en Colas", matrizPaquetesEnColas, cantRouters);*/
    cout<<"Matriz Grafo:\t   Matriz Caminos:\t   Matriz Costos:\t   Matriz Paquetes en Colas: "<<endl;
    for (int i = 0; i < cantRouters; ++i) {
        for (int j = 0; j < cantRouters; ++j) {
            if(grafo[i*cantRouters + j] == 2147483647){
                cout << "- ";
            } else {
                cout<<grafo[i*cantRouters + j]<<" ";
            }
        }
        cout<<"\t\t\t";

        for (int j = 0; j < cantRouters; ++j) {
            if(matrizCaminos[i * cantRouters + j] == 2147483647){
                cout << "- ";
            } else {
                cout<<matrizCaminos[i * cantRouters + j]<<" ";
            }
        }
        cout<<"\t\t\t";

        for (int j = 0; j < cantRouters; ++j) {
            if(matrizCostos[i*cantRouters + j] == 2147483647){
                cout << "- ";
            } else {
                cout<<matrizCostos[i*cantRouters + j]<<" ";
            }
        }
        cout<<"\t\t\t";

        for (int j = 0; j < cantRouters; ++j) {
            if(matrizPaquetesEnColas[i*cantRouters + j] == 2147483647){
                cout << "- ";
            } else {
                cout<<matrizPaquetesEnColas[i*cantRouters + j]<<" ";
            }
        }
        cout<<endl;
    }
    cout<<endl;


}






//-------Otras Funciones------//


/* \brief   Envia la pagina Pagina a la terminal term
 * \param   Pagina: puntero a la pagina que se quiere enviar
 * \param   term: Puntero a la terminal a la cual se quiere enviar la pagina
 * */
void enviarPaginaATerminal(pag * Pagina, Terminal * term)
{
    term->recibirPagina(*Pagina);
}


void enviarPaquetes(Router * arrayRouts)
{
    int cantColas;
    int bandWidth;
    int idRou;
    int cantidColas;
    int minSize=0;
    for (int i = 0; i < cantidadRouters; ++i) {     //Recorro toodo el array de routers
        cantColas = arrayRouts[i].getCantidadEnlaces()+1;
        for (int j = 0; j < cantColas-1; ++j) {       //Recorro todas la colas, excepto la cola propia

            //Veo si la cola tiene paquetes para enviar
            minSize = arrayRouts[i].getSizeCola(j);
            if (minSize > 0) {  //si tiene los envío

                //Obtengo los paquetes a enviar de una cola de un router
                bandWidth = arrayRouts[i].getBandWidthCola(j);
                paquete arrayPaquetes[bandWidth];
                arrayRouts[i].getCola(&arrayPaquetes[0], bandWidth,
                                      j);  //pongo todos los paquetes que tiene que enviar la cola j del router i en el array de paquetes
                arrayRouts[i].borrarNPaquetesCola(bandWidth, j); //borro los paquetes que obtuve de la cola j

                //Verifico si la cola tiene mas paquetes que bandWidth
                //minSize = arrayRouts[i].getSizeCola(j); ///(Esto ya lo hago arriba)
                if (minSize > bandWidth) {
                    minSize = bandWidth;
                }

                //Envio los paquetes al router correspondiente
                idRou = arrayRouts[i].getIdRouterFromCola(j);               //pregunta cual es el router destino
                cantidColas = arrayRouts[idRou].getCantidadEnlaces() + 1;   //saca la cantidad de colas del router
                for (int k = 0; k < minSize; ++k) {   //Recorro toodo el array de paquetes
                    arrayRouts[idRou].enviarPaqueteACola(arrayPaquetes[k], cantidColas-1); //Envio el paquete a la cola propia de ese router
                }
            }
        }

    }
}