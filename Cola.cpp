//
// Created by octa on 29/6/21.
//
#include <list>
#include "Cola.h"
#include "global.h"
#include <stdio.h>
#include <cstdlib>


using namespace std;

/* \brief Constructor inicializa las variables privadas de la clase cola.
 *        El ancho de banda se designa aleatoriamente.
 */
Cola::Cola( int _routerOrigen, int _routerDestino, int _bandWidth )
{
    routerOrigen  = _routerOrigen;
    routerDestino = _routerDestino;
    bandWidth     = _bandWidth;         //Es la cantidad de paquetes que pueden pasar por ese enlace en un ciclo//aleatorio:(rand()%5)+1;
    //list<struct paq> cola;            //Ya esta creada en los atributos privados
}


/* \brief Hace lo mismo que el contructor. Se utiliza cuando se contruyo con el constructor vacio.
 */
void Cola::setAll( int _routerOrigen, int _routerDestino, int _bandWidth )
{
    routerOrigen  = _routerOrigen;
    routerDestino = _routerDestino;
    bandWidth     = _bandWidth;         //Es la cantidad de paquetes que pueden pasar por ese enlace en un ciclo//aleatorio:(rand()%5)+1;
    //list<struct paq> cola;            //Ya esta creada en los atributos privados
}


/* \brief Imprime todos los paquetes de la cola
 */
void Cola::print(){

    list<struct paquete>::iterator it;

    printf("IP DESTINO \t IP ORIGEN \t No PAQUETE \t ID PAG \t SIZE PAGINA\n");

    it = cola.begin();    //retorna un puntero al primer elemento

    for ( ; it != cola.end(); it++){
        printf("  %d.%d  \t  %d.%d  \t  %d  \t  %d  \t  %d  \n", it->ip_destino.idRouter, it->ip_destino.idTerminal, it->ip_origen.idRouter, it->ip_origen.idTerminal, it->numPaquete, it->idPagina, it->sizePag );
    }

}

/* \brief Agrega el paquete paq a la cola.
 * \param paq: paquete que se desea agregar.
 */
void Cola::agregarPaquete(struct paquete paq)
{
   cola.push_front(paq);   //Hacemos front por que debe consumir un poco menos de tiempo que back //igual esta clase debe tener punteros
}

/* \brief Agrega todos los paquetes, contenidos en un array, a la cola.
 * \param paq_q: puntero al primer elemento del array de paquetes.
 * \param sizeArray: cantidad de elementos del array de paquetes.
 */
void Cola::agregarArrayPaquetes(paquete * paq_p, int sizeArray)
{
    paquete paq;
    for (int i = 0; i < sizeArray; ++i) {
        paq.ip_origen.idRouter   = paq_p[i].ip_origen.idRouter;
        paq.ip_origen.idTerminal = paq_p[i].ip_origen.idTerminal;
        paq.ip_destino.idRouter  = paq_p[i].ip_destino.idRouter;
        paq.ip_destino.idTerminal  = paq_p[i].ip_destino.idTerminal;
        paq.numPaquete  = paq_p[i].numPaquete;
        paq.idPagina    = paq_p[i].idPagina;
        paq.sizePag     = paq_p[i].sizePag;
        //paq = paq_p[i];
        cola.push_front(paq);
        //paq_p++;
    }
}


/* \brief   Esta funcion devuelve el paquete correspondiente a la posicion indicePaquete. No elimina el paquete.
 * \param   indicePaqute: es un entero que indica la posicion del elemento (paquete) que se quiere obtener.
 * \param   paq: Es un puntero a un paquete, aquí se devolverá el paquete solicitado.
 * \return  Retorna 0 en caso de exito. -1 en caso contrario (por ejemplo si el índice es incorrecto)
 * */
int Cola::leerPaquete(int indicePaquete, struct paquete * paq_p)
{
    int cantidadElementos;
    list<struct paquete>::iterator it;
    cantidadElementos = cola.size();
    it = cola.begin();
    struct paquete paq;

    //Comprobacion de error de indice
    if(indicePaquete > cantidadElementos){
        return -1;
    }

    for (int i = 0; i < indicePaquete; ++i) {
        it++;
    }

    paq.ip_origen   = it->ip_origen;
    paq.ip_destino  = it->ip_destino;
    paq.numPaquete  = it->numPaquete;
    paq.idPagina    = it->idPagina;
    paq.sizePag     = it->sizePag;

    *paq_p = paq;
    //Comprobacion de error de asignacion
    if(paq_p == NULL){
        return -1;
    }

    return 0;
}


/* \brief   Esta funcion devuelve el paquete correspondiente a la posicion indicePaquete. Elimina el paquete.
 * \param   indicePaqute: es un entero que indica la posicion del elemento (paquete) que se quiere obtener.
 * \param   paq: Es un puntero a un paquete, aquí se devolverá el paquete solicitado.
 * \return  Retorna 0 en caso de exito. -1 en caso contrario (por ejemplo si el índice es incorrecto)
 * */
int Cola::getPaquete(int indicePaquete, struct paquete * paq_p)
{
    int cantidadElementos;
    list<struct paquete>::iterator it;
    cantidadElementos = cola.size();
    it = cola.begin();
    struct paquete paq;

    //Comprobacion de error de indice
    if(indicePaquete > cantidadElementos){
        return -1;
    }

    for (int i = 0; i < indicePaquete; ++i) {
        it++;
    }

    paq.ip_origen   = it->ip_origen;
    paq.ip_destino  = it->ip_destino;
    paq.numPaquete  = it->numPaquete;
    paq.idPagina    = it->idPagina;
    paq.sizePag     = it->sizePag;

    *paq_p = paq;

    //Comprobacion de error de asignacion
    if(paq_p == NULL){
        return -1;
    }

    it = cola.erase(it);    //Borra el paquete it, y devuelve el paquete siguiente que se vuelve a guardar en it

    return 0;
}


/* \brief   Esta funcion devuelve un array con los primeros "sizeArray" paquetes. Si sizeArray es mayor o igual
 *          a la cantidad de paquetes, devuelve todos los paquetes.
 * \param   paq_p: Array de paquetes que será devuelto y cargado con los paquetes.
 * \param   sizeArray: Tamaño del array ingresado en el parametro anterior
 * */
void Cola::getArrayPaquetes(paquete * paq_p, int sizeArray)
{
    paquete paqAux;

    //Comprueba cual es menor, si el size del Array o el size de la cola
    int min = cola.size();
    if (sizeArray < min){
        min = sizeArray;
    }

    for (int i = 0; i < min; ++i) {
        if(leerPaquete( i, &paqAux) == -1){} //Obtengo le paquete, si da error no hago nada
        paq_p[i] = paqAux;                   //pongo el paquete en el array
    }

    return;
}

/* \brief   Esta funcion devuelve todos los paquetes de una pagina cuyo destino es el router indicado.
 *          Solo devuelve los paquetes si están todos los que conforman la página.
 * \param[out]  arrayPaq: es el array de paquetes que se va a devolver con los paquetes de la página
 * \param[ir]   routDestino: El el router del cual se quiere ver si tiene una pagina para armar.
 * \return  Retorna la cantidad de elementos de la pagina, si esta se encontraba completa o 0 en caso de que no haya pagina
 *
 * Aclaracion: si hay mas de una pagina entera en la cola, esta funcion lo ignora y devuelve solo un array. Por lo que
 * se deberia volver a llamar la funcion si retorno un numero mayor a cero
 * */
int Cola::getPaquetesPagina( paquete * arrayPaq, int routDestino)
{
    int cantidadElementos;
    list<struct paquete>::iterator it;
    cantidadElementos = cola.size();
    it = cola.begin();

    int idPagina;
    int sizePagina;
    int indice;
    int indiceIt = 0;
    for (int i = 0; i < cantidadElementos; ++i) {   //Recorro todos los elementos
        if (it->ip_destino.idRouter == routDestino){    //Pregunto si el destino del paquete es el del router indicado
            idPagina   = it->idPagina;
            sizePagina = it->sizePag;
            paquete auxPaq[sizePagina]; //Creo un array para contener todos los paquetes de esa pagina

            indice = 0;
            //Cargo el primer elemento en el array
            auxPaq[indice] = *it;
            it++;
            indice++;

            //Cargo el resto de los elementos en el array
            for (int j = i+1; j < cantidadElementos ; ++j) {  //Recorro los paquetes siguientes a ver si pertenecen a la pagina
                if (it->idPagina == idPagina){  //Si el paquete pertenece a la pagina
                    auxPaq[indice] = *it;        //Lo guardo en el array
                    if (indice == sizePagina-1){  //Si ya cargo en el array todos los elementos de la pagina
                        //Retorna el array en param
                        for (int k = 0; k < sizePagina; ++k) {
                            arrayPaq[k] = auxPaq[k];
                        }
                        //borro todos los paquetes de la pagina
                        it = cola.begin();
                        int k = 0;
                        int flag = 0;
                        while (k < sizePagina) {
                           if (it->idPagina == idPagina) {
                               it = cola.erase(it); //Borro el paquete
                               k++;                 //cada vez que borro un paquete aumento k
                               flag = 1;
                           }
                           if (flag == 0) {  //solo hago it++ cuando no borre nada, porque si borre el siguiente elemento queda en la posicion en la que estoy
                               it++;               //Voy avanzando en la iteracion
                           }
                           flag = 0;
                        }

                        return indice;              //Retorna la cantidad de elementos del array en return
                    }
                    indice++;                   //Incremento el indice
                }
                it++;                       //Incremento el iterador
            }
        }
        indiceIt++; //Voy al elemento siguiente
        it = cola.begin();
        for (int j = 0; j < indiceIt; ++j) {
            it++;
        }
    }

    return 0;

    it = cola.erase(it);    //Borra el paquete it, y devuelve el paquete siguiente que se vuelve a guardar en it

    return 0;
}

/* \brief Devuelve un puntero al primer elemento de la lista
 *        No elimina el elemento
 */
void Cola::leerFront(struct paquete * paq)
{
    *paq = cola.front();
}

/* \brief Devuelve un puntero al ultimo elemento de la lista
 *        No elimina el elemento
 */
void Cola::leerBack(struct paquete * paq)
{
    *paq = cola.back();
}

/* \brief Elimina el primer elemento de la lista*/
void Cola::popFront()
{
    cola.pop_front();
}

/* \brief Borra todos los paquetes de la cola*/
void Cola::borrarTodo(){
    int sizeCola = cola.size();
    for (int i = 0; i < sizeCola; ++i) {
        cola.pop_front();
    }
}

/* \brief Borra los primeros n elementos de la cola*/
void Cola::borrarNElementos(int n)
{
    int minSize = cola.size();
    if (n < minSize){
        minSize = n;
    }
    for (int i = 0; i < minSize; ++i) {
        cola.pop_front();
    }
}

/* \brief Elimina el ultimo elemento de la lista*/
void Cola::popBack()
{
    cola.pop_back();
}

/* \brief Retorna la cantidad de elementos de la lista*/
int Cola::sizeCola()
{
    return cola.size();
}

/* \brief Setea la variable bandWidth (Ancho de banda)
 * \param bandW: entero que se quiere setear
 */
void Cola::setBandWidth(int bandW)
{
    bandWidth = bandW;
}

/* \brief retorna la variable bandWidth (Ancho de banda)*/
int Cola::getBandWidth()
{
    return bandWidth;
}


/* \brief retorna la variable routerDestino*/
int Cola::getRouterDestino()
{
   return routerDestino;
}


/* \brief retorna la variable routerOrigen
 * */
int Cola::getRouterOrigen()
{
    return routerOrigen;
}

/* \brief Ordena los elementos de la lista de manera intercalada, segun el id de pagina de cada elemento.
 *        El algoritmo utilizado es Bucket Sort (ó algoritmo de ordenamiento por casilleros)*/
void Cola::bucketSort()
{
    //Size
    int sizeCola = cola.size();
    if (sizeCola <= 2){     //Si hay menos de dos elementos, ya esta ordenada
        return;
    }
    //Lista
    list<struct paquete>::iterator it;
    list<struct paquete>::iterator it2;
    it = cola.begin();
    //Buckets
    int buckets[sizeCola][sizeCola] = {-1};
    int idPaginas[sizeCola] = {-1};
    int resultado[sizeCola];
    //Indices
    int indiceIdPag   = 0;
    int posicionIdPag;
    int indiceResultado;



    //int indiceBuckets = 0;
    int indicesBuckets[sizeCola] = {0};
    //Otros
    int auxIdPAg;
    int maxSizeBucket;
    paquete voidPaq;

    for (int i = 0; i < sizeCola; ++i) {
        //---Recorro cada elemento, veo el idPagina que tiene----
        auxIdPAg = it->idPagina; //Pongo el idPagina del elemento en el aux

        //Compruebo si el id pag ya esta en el array y me quedo con la posicion en la que está
        posicionIdPag = -1;
        for (int j = 0; idPaginas[j] == -1; ++j) {  //Recorro todos los id Paginas
            if (idPaginas[j] == auxIdPAg){
                posicionIdPag = j;
            }
        }
        //Si no está, lo coloco en el array
        if (posicionIdPag == -1){
            idPaginas[indiceIdPag] = auxIdPAg;
            posicionIdPag = indiceIdPag;
            indiceIdPag++;
        }


        //---Guardo el indice del elemento en el bucket correspondiente---
        buckets[posicionIdPag][indicesBuckets[posicionIdPag]] = i;  //Guardo el inicie en el bucket
        indicesBuckets[posicionIdPag] += 1;                         //Incremento el indice del bucket


        it++;
    }

    //---Acomodo todos los buckets intercalados
    //Obtengo la cantidad de elementos del bucket mas largo
    maxSizeBucket = 0;
    for (int i = 0; i < indiceIdPag; ++i) {
        if (indicesBuckets[i] > maxSizeBucket) {
            maxSizeBucket = indicesBuckets[i];
        }
    }
    maxSizeBucket--;


    //Cargo los valores en el array Resultado
    indiceResultado = 0;
    for (int i = 0; i < maxSizeBucket; ++i) {             //Desde 0 hasta la cantidad de elementos del bucket mas grande
        for (int j = 0; j <= indiceIdPag; ++j) {          //Desde 0 hasta la cantidad de idPaginas distintos
            if (buckets[j][i] >= 0) {     //si buckets[j][i] es distinto de -1
                resultado[indiceResultado] = buckets[j][i];     //Guardo el valor en el array
                indiceResultado++;
            }
        }
    }



    //---Acomodo la lista---
    //Copio todos los elementos al final, para no perder el orden de los indices
    it = cola.begin();  //Apunta al principio de la cola
    it2 = cola.end();
    for (int i = 0; i < sizeCola; ++i) {

    }
    
    //Borro todos los elementos del principio
}