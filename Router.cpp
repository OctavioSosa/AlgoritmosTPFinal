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
    //Cola colas[cantEnlaces+1];  //Una para cada enlace y una cola propia
    //colas_p = &colas[0];
    colas_p = (Cola*) calloc(cantEnlaces+1, sizeof(Cola));

    //Inicializo todas las colas
    for (int i = 0; i < cantEnlaces; ++i) {
        colas_p[i].setAll(idRouter, matrizEnlaces[i], matrizBandWidth[i]);
    }

    //Inicializo la cola propia
    colas_p[cantEnlaces].setAll(idRouter,idRouter,0);
}


/* \brief Hace lo mismo que el contructor. Se utiliza cuando se contruyo con el constructor vacio.
 */
void Router::setAll(int _idRouter, int _idTerminal, int _cantEnlaces, int * matrizEnlaces, int * matrizBandWidth)
{
    idRouter    = _idRouter;
    idTerminal  = _idTerminal;
    cantEnlaces = _cantEnlaces;

    //Crear colas
    //Cola colas[cantEnlaces+1];  //Una para cada enlace y una cola propia
    //colas_p = &colas[0];
    colas_p = (Cola*) calloc(cantEnlaces+1, sizeof(Cola));

    //Inicializo todas las colas
    for (int i = 0; i < cantEnlaces; ++i) {
        colas_p[i].setAll(idRouter, matrizEnlaces[i], matrizBandWidth[i]);
    }

    //Inicializo la cola propia
    colas_p[cantEnlaces].setAll(idRouter,idRouter,0);
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
    struct paquete auxPaq;
    for (int i = 0; i < cantidadPaquetes; ++i) {
        auxPaq = (paquete) arrayPaquetes[i];
        colas_p[cantEnlaces].agregarPaquete(auxPaq);
        //colas_p[cantEnlaces].agregarArrayPaquetes( &arrayPaquetes[0], cantidadPaquetes);
    }

}

/* \brief   Reordena los paquetes de todas las colas (incluida la cola propia),
 *          segun lo que se envie en arrayCami. Este debe cumplir la regla de dijkstra
 * */
void Router::reordenarColas(int * arrayCami)
{
    Cola auxCola( 0, 0, 0);
    int cantidadPaquetes = 0;
    paquete auxPaq;
    int routerDestinoFinal;
    int routerDestinoSiguiente;

    //----Reubicar de ser necesario lo que esta en todas las colas----

    //Pongo los paquetes de todas las colas en la cola auxiliar
    for (int i = 0; i < cantEnlaces+1; ++i) {
        //Calculo la cantidad de paquetes que estan en cada cola
        cantidadPaquetes = colas_p[i].sizeCola();

        if (cantidadPaquetes > 0) {    //solo actuo si la cola tiene paquetes

            //Creo un array de paquetes que los contenga
            paquete arrayPaq[cantidadPaquetes];

            //Cargo todos los paquetes al array
            colas_p[i].getArrayPaquetes(&arrayPaq[0], cantidadPaquetes);

            //Cargo todos los paquetes del array a la cola auxiliar
            auxCola.getArrayPaquetes(&arrayPaq[0], cantidadPaquetes);

            //Borro todos los paquetes de la cola[i]
            colas_p[i].borrarTodo();
        }
    }
    //Ahora ya tengo cargados todos los paquetes en una unica cola auxiliar


    //Reubico los paquetes en las colas correspondientes
    int sizeAuxCola = auxCola.sizeCola();


    for (int i = 0; i < sizeAuxCola && sizeAuxCola > 0; ++i)
    {
        auxCola.getPaquete(i, &auxPaq);                         //Obtengo el paquete de la cola
        routerDestinoFinal = auxPaq.ip_destino.idRouter;        //Obtengo el destino final del paquete
        routerDestinoSiguiente = arrayCami[routerDestinoFinal]; //Veo a que router tengo que enviar el paquete
        if( routerDestinoFinal == idRouter){            //Si el destino final del paquete es el propio router
            colas_p[cantEnlaces+1].agregarPaquete(auxPaq); //Lo coloco en la cola propia
        } else {        //Sino lo guardo en la cola correspondiente a ese router
            colas_p[routerDestinoSiguiente].agregarPaquete(auxPaq); //Lo coloco en la cola correspondiente a ese router
        }
    }

    //TODO:Ordeno cada cola para que esten listas para el envio
    /*for (int i = 0; i < cantEnlaces; ++i) {
        colas_p[i].ordenarCola();
    }*/
    //ordenarColas();
}



void Router::ordenarColas()
{
    for (int i = 0; i < cantEnlaces; ++i) {     //No ordeno la cola propia, no hace falta
        //colas_p[i].
    }
}

/* \brief   Comprueba si hay una pagina entera en la cola propia. Si es asi la arma y la devuelve por el
 *          parametro Pagina.
 * \param[out]  Pagina: retorna la pagina si habia alguna
 * \retunr  Retorna el tamaño de la pagina(un numero mayor a cero) en caso de que haya habido una pagina
 *          en la cola ó 0 en caso contrario
 *
 *  Aclaracion: si hay mas de una pagina entera en la cola, esta funcion lo ignora y devuelve solo una
 *  pagina, por lo que se deberia volver a llamar la funcion si retornó un numero mayor a cero
 * */
int Router::armarPaginasRecibidas(pag * Pagina)
{
    int sizeCola = colas_p[cantEnlaces+1].sizeCola();   //Cola propia
    paquete arrayPaq[sizeCola];

    int retorno;
    retorno = colas_p[cantEnlaces+1].getPaquetesPagina( &arrayPaq[0], idRouter);

    if(retorno == 0){
        return 0;
    }

    //Armamos la pagina
    Pagina->idPagina = arrayPaq[0].idPagina;
    Pagina->sizePag  = arrayPaq[0].sizePag;
    Pagina->ip_destino = arrayPaq[0].ip_destino;
    return retorno;
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

/* \brief Retorna el ID de su terminal asociada o -1 en caso de no tener terminal*/
int Router::getTerminalId()
{
    return idTerminal;
}


int Router::getCantidadEnlaces()
{
    return cantEnlaces;
}

int Router::getBandWidthCola(int idCola)
{
    return colas_p[idCola].getBandWidth();;
}

/* \brief   Retorna un array con los primeros sizeArray paquetes de la cola idCola.
 *          Si el sizeArray es igual al ancho de banda del enlace, entonces devuelve todos
 *          los paquetes que se tienen que enviar
 * \param[out]  arrayPaquetes: Es el array de paquetes que se retorna
 * \param[in]   sizeArray: Es el tamaño del array del parametro anterior
 * \param[in]   idCola: es el numero de la cola de la cual se quiere obtener los pauqetes
 */
void Router::getCola(paquete * arrayPaquetes, int sizeArray, int idCola)
{
    colas_p[idCola].getArrayPaquetes( arrayPaquetes, sizeArray);
}

/* \brief Envia el paquete recibido a la cola idCola
 * \param[in]   paq: paquete a enviar
 * \param[in]   idCola: es el numero de la cola a la cual se quiere enviar el pauqete
 * */
void Router::enviarPaqueteACola(paquete paq, int idCola)
{
    colas_p[idCola].agregarPaquete(paq);
}


/* \brief   Retorna el Tamaño de la cola idCola
 */
int Router::getSizeCola( int idCola)
{
    return colas_p[idCola].sizeCola();
}
