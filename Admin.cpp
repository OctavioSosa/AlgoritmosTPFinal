//
// Created by octa on 1/7/21.
//

#include "Admin.h"
#include "Algoritmos.h"
#include "Terminales.h"
#include "Router.h"
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
        for (int j = 0; j < cantiColas; ++j) {
            int enlaces[cantiColas-1];
            getEnlaces(&enlaces[0], cantiColas-1,  i, grafo); //Obtengo la matriz de enlaces
            k = enlaces[j];                                                             //guardo el router asignado a la cola j
            matrizPaquetesEnColas[i*cantRouters + k] = arrayRouters[i].getSizeCola(j);   //Asigno la cantidad de paquetes a la matriz paqutes en cola
        }

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
    cout<<"Matriz Grafo:"<<endl;
    for (int i = 0; i < cantRouters; ++i) {
        for (int j = 0; j < cantRouters; ++j) {
            cout<<grafo[i*cantRouters + j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    cout<<endl;

    cout<<"Matriz Caminos:"<<endl;
    for (int i = 0; i < cantRouters; ++i) {
        for (int j = 0; j < cantRouters; ++j) {
            cout<<matrizCaminos[i * cantRouters + j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    cout<<endl;

    cout<<"Matriz Costos:"<<endl;
    for (int i = 0; i < cantRouters; ++i) {
        for (int j = 0; j < cantRouters; ++j) {
            cout<<matrizCostos[i*cantRouters + j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    cout<<endl;


    cout<<"Matriz Paquetes en Colas:"<<endl;
    for (int i = 0; i < cantRouters; ++i) {
        for (int j = 0; j < cantRouters; ++j) {
            cout<<matrizPaquetesEnColas[i*cantRouters + j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
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
    for (int i = 0; i < cantidadRouters; ++i) {     //Recorro toodo el array de routers
        cantColas = arrayRouts[i].getCantidadEnlaces();
        for (int j = 0; j < cantColas; ++j) {       //Recorro todas la colas
            //Obtengo los paquetes a enviar de una cola de un router
            bandWidth = arrayRouts[i].getBandWidthCola(j);
            paquete arrayPaquetes[bandWidth];
            arrayRouts[i].getCola( &arrayPaquetes[0], bandWidth, j);  //pongo todos los paquetes que tiene que enviar la cola j del router i en el array de paquetes

            //Envio los paquetes al router correspondiente
            for (int k = 0; k < bandWidth; ++k) {   //Recorro toodo el array de paquetes
                idRou = arrayPaquetes[k].ip_destino.idRouter;           //pregunta cual es el router
                cantidColas = arrayRouts[idRou].getCantidadEnlaces() + 1; //sacar cantidad de colas del router
                arrayRouts[idRou].enviarPaqueteACola( arrayPaquetes[k], cantidColas); //Envio el paquete a la cola propia
            }
        }

    }
}