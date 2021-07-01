//
// Created by octa on 28/6/21.
//

#include "global.h"
#include "Router.h"
#include "Cola.h"
#include<bits/stdc++.h>

using namespace std;

/* \brief Constructor de la clase Router.
 */
Router::Router(int _idRouter, int _idTerminal, int _cantEnlaces, int * matrizEnlaces, int * matrizBandWidth)
{
    idRouter    = _idRouter;
    idTerminal  = _idTerminal;
    cantEnlaces = _cantEnlaces;

    //Crear colas
    Cola colas[cantEnlaces+1];  //Una para cada enlace y una cola propia
    colas_p = &colas[0];

    //Inicializo todas las colas
    for (int i = 0; i < cantEnlaces; ++i) {
        colas[i].setAll(idRouter, matrizEnlaces[i], matrizBandWidth[i]);
    }

    //Inicializo la cola propia
    colas[cantEnlaces].setAll(idRouter,idRouter,0);
}


/* \brief Hace lo mismo que el contructor. Se utiliza cuando se contruyo con el constructor vacio.
 */
void Router::setAll(int _idRouter, int _idTerminal, int _cantEnlaces, int * matrizEnlaces, int * matrizBandWidth)
{
    idRouter    = _idRouter;
    idTerminal  = _idTerminal;
    cantEnlaces = _cantEnlaces;

    //Crear colas
    Cola colas[cantEnlaces+1];  //Una para cada enlace y una cola propia
    colas_p = &colas[0];

    //Inicializo todas las colas
    for (int i = 0; i < cantEnlaces; ++i) {
        colas[i].setAll(idRouter, matrizEnlaces[i], matrizBandWidth[i]);
    }

    //Inicializo la cola propia
    colas[cantEnlaces].setAll(idRouter,idRouter,0);
}




/* \brief   Esta funcion recibe una pagina entera de la terminal asociada al router y se encarga
 *          de dividirla en paquetes para luego colocarlos en la cola correspondiente.
 * \param   Pagina: la página que se desea dividir y colocar en la cola.
 */
void Router::transmitir( pag Pagina)
{
    //Comprueba que no se quiera llamar a este metodo desde un router que no tenga terminal asociada
    if(idTerminal == -1){
        return;
    }

    //-----Definicion variables-----
    int cantidadPaquetes;
    cantidadPaquetes = Pagina.sizePag;
    struct ip ip_origen;
    ip_origen.idRouter = idRouter;
    ip_origen.idTerminal = idTerminal;

    //-----Divide la pagina en paquetes-----
    //Crea los paquetes y los inicializa
    struct paquete arrayPaquetes[cantidadPaquetes];
    for (int i = 0; i < cantidadPaquetes; ++i) {
        arrayPaquetes[i].sizePag    = cantidadPaquetes;
        arrayPaquetes[i].ip_destino = Pagina.ip_destino;
        arrayPaquetes[i].ip_origen  = ip_origen;
        arrayPaquetes[i].numPaquete = i;
        arrayPaquetes[i].idPagina   = Pagina.idPagina;
    }

    //-----Coloca los paquetes en la cola correspondiente------
    //TODO: hacer
    //int indiceCola = getIndiceCola(Pagina.ip_destino.idRouter);   //Obtengo el indice de la cola que corresponde al router destino
    //colas_p[indiceCola].agregarArrayPaquetes( arrayPaquetes, cantidadPaquetes);

    /*for (int i = 0; i < cantidadPaquetes; ++i) {
        cola.addPaquete(arrayPaquetes[i]);
    }*/

}


void Router::recibirPagina (pag Pagina)
{
    //Comprueba que no se quiera llamar a este metodo desde un router que no tenga terminal asociada
    if(idTerminal == -1){
        return;
    }

    //-----Definicion variables-----
    int cantidadPaquetes;
    cantidadPaquetes = Pagina.sizePag;
    struct ip ip_origen;
    ip_origen.idRouter = idRouter;
    ip_origen.idTerminal = idTerminal;


    //-----Divide la pagina en paquetes-----
    //Crea los paquetes y los inicializa
    struct paquete arrayPaquetes[cantidadPaquetes];
    for (int i = 0; i < cantidadPaquetes; ++i) {
        arrayPaquetes[i].sizePag    = cantidadPaquetes;
        arrayPaquetes[i].ip_destino = Pagina.ip_destino;
        arrayPaquetes[i].ip_origen  = ip_origen;
        arrayPaquetes[i].numPaquete = i;
        arrayPaquetes[i].idPagina   = Pagina.idPagina;
    }

    //-----Coloco los paquetes en la cola propia-----
    colas_p[cantEnlaces].agregarArrayPaquetes( &arrayPaquetes[0], cantidadPaquetes);

}

/* \brief   Reordena los paquetes de todas las colas (incluida la cola propia),
 *          segun la regla de dijkstra.
 * */
void Router::ordenarColas()
{
    //TODO: hacer
}



//----------Otras Funciones----------//


/* \brief   Devuelve la cantidad de enlaces que tiene el router especificado. Esto lo hace
 *          analizando la matriz correspondiente al grafo.
 * \param   idRout: id del router del cual se quieren obtener los enlaces.
 * \param   matriz: matriz que representa el grafo del enlazamiento de los routers
 */
int getCantidadDeEnlaces(int idRout, int * matriz){
    int aux;
    int cantEnlaces = 0;
    for (int i = 0; i < cantidadRouters; ++i) {
        aux = matriz[i*cantidadRouters + idRout];      //Revisa todos los valores de la columna del router
        if (aux != INT_MAX && aux != 0){                //Cuenta como enlace si no es 0, ni infinito
            cantEnlaces++;
        }
    }
    return cantEnlaces;
}

/* \brief   Devuelve un array con los IDs de los routers con los cuales se enlaza el router
 *          especificado.
 * \param[out]  matrizEnlaces: Array con los IDs de los router enlazados
 * \param[in]   sizeMatrizEnlaces: Tamaño de la matriz ingresada en el parametro anterior
 * \param[in]   idRout: ID del router del cual se quieren obtener los enlaces
 * \param[in]   matriz: matriz que representa el grafo del enlazamiento de los routers
 * */
void getEnlaces(int * matrizEnlaces, int sizeMatrizEnlaces, int idRout, int * matriz)
{
    int aux;
    int indice = 0;
    int cantEnlaces = sizeMatrizEnlaces; //Obtengo la cantidad de enlaces
    int enlaces[cantEnlaces];
    for (int i = 0; i < cantidadRouters; ++i) {
        aux = matriz[i*cantidadRouters + idRout];      //Revisa todos los valores de la columna del router
        if (aux != INT_MAX && aux != 0){                //Cuenta como enlace si no es 0, ni infinito
            enlaces[indice] = i;
            indice++;
        }
    }

    //Copio la informacion a la matriz de salida
    for (int i = 0; i < cantEnlaces; ++i) {
        matrizEnlaces[i] = enlaces[i];
    }
    return;
}


/* \brief   Devuelve un array con los anchos de banda de los enlaces asociados al router especificado.
 * \param[out]  matrizBandWidth: Array con el ancho de banda de cada enlace
 * \param[in]   sizeMatrizBandWidth: Tamaño de la matriz ingresada en el parametro anterior
 * \param[in]   idRout: ID del router del cual se quieren obtener los enlaces
 * \param[in]   matriz: matriz que representa el grafo del enlazamiento de los routers
 * */
void getBandWidthEnlaces(int * matrizBandWidth, int sizeMatrizBandWidth, int idRout, int * matriz)
{
    int aux;
    int indice = 0;
    int cantEnlaces = sizeMatrizBandWidth;          //Obtengo la cantidad de enlaces
    int bandWidth[cantEnlaces];
    for (int i = 0; i < cantidadRouters; ++i) {
        aux = matriz[i*cantidadRouters + idRout];   //Revisa todos los valores de la columna del router
        if (aux != INT_MAX && aux != 0){            //Cuenta como enlace si no es 0, ni infinito
            bandWidth[indice] = aux;
            indice++;
        }
    }

    //Copio la informacion a la matriz de salida
    for (int i = 0; i < cantEnlaces ; ++i) {
        matrizBandWidth[i] = bandWidth[i];
    }
    return;
}


/* \brief   Devuelve el ID de la terminal asociada al router o -1 en caso de que no tenga.
 * \param   idRout: id del router del cual se quieren conocer la terminal.
 * \param   arrayTermi: Array de terminales. Cada elemento del array contiene en id del router que tiene terminal.
 *          Y la posicion del array corresponde con la ID de la terminal.
 */
int getIdTerminal(int idRout, int * arrayTermi)
{
    int aux;
    int cantEnlaces = 0;
    for (int i = 0; i < cantidadTerminales; ++i) {
        aux = arrayTermi[i];        //Revisa todos los valores del array de terminales
        if (aux == idRout){         //Si este router tiene terminal
            return i;                   //Retorna la id de la terminal
        }
    }
    return -1;                      //Si no tiene, retorna -1
}


/* \brief Obtiene el indice del array de colas que corresponde a la cola que apunta a router destino (rDest)
 * \param rDest: id del router del cual se quiere obtener la cola asociada
 */
int Router::getIndiceCola (int rDest)
{
    for (int i = 0; i < cantEnlaces+1 ; ++i) {
        if(rDest == colas_p[i].getRouterDestino()){ //Pregunta si el id ingresado por parametros es igual al que tiene alguna de las colas
            return i;                               //Retorna el indice de la cola
        }
    }

    return -1;  //Si no coincide con inguna retorna -1
}